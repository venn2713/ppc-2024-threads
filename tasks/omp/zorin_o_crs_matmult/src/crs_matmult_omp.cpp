// Copyright 2024 Zorin Oleg
#include "omp/zorin_o_crs_matmult/include/crs_matmult_omp.hpp"

bool CRSMatMult::validation() {
  internal_order_test();

  return taskData->inputs_count[1] == taskData->inputs_count[2] &&
         taskData->outputs_count[0] == taskData->inputs_count[0] &&
         taskData->outputs_count[1] == taskData->inputs_count[3];
}

bool CRSMatMult::pre_processing() {
  internal_order_test();

  A = std::make_unique<CRSMatrix>(reinterpret_cast<double*>(taskData->inputs[0]), taskData->inputs_count[0],
                                  taskData->inputs_count[1]);
  B = std::make_unique<CRSMatrix>(reinterpret_cast<double*>(taskData->inputs[1]), taskData->inputs_count[2],
                                  taskData->inputs_count[3]);
  C = std::make_unique<CRSMatrix>(taskData->outputs_count[0], taskData->outputs_count[1]);

  return true;
}

bool CRSMatMult::run() {
  internal_order_test();
  std::vector<std::vector<double>> all_value(A->n_rows);
  std::vector<std::vector<std::size_t>> all_col_index(A->n_rows);

#pragma omp parallel for default(none) shared(all_value, all_col_index) schedule(static)
  for (int row_i = 0; row_i < A->n_rows; ++row_i) {
    std::vector<double> local_row(C->n_cols);
    for (std::size_t i = A->row_ptr[row_i]; i < A->row_ptr[row_i + 1]; ++i) {
      const std::size_t& col_i = A->col_index[i];
      const double& val = A->values[i];

      for (std::size_t j = B->row_ptr[col_i]; j < B->row_ptr[col_i + 1]; ++j) {
        local_row[B->col_index[j]] += val * B->values[j];
      }
    }

    for (std::size_t i = 0; i < local_row.size(); ++i) {
      double& val = local_row[i];
      if (std::abs(val) > EPS) {
        all_col_index[row_i].emplace_back(i);
        all_value[row_i].emplace_back(val);
        val = 0.0;
      }
    }
  }

  for (std::size_t i = 0; i < C->n_rows; ++i) {
    C->row_ptr.emplace_back(C->values.size());
    C->col_index.insert(C->col_index.cend(), all_col_index[i].begin(), all_col_index[i].end());
    C->values.insert(C->values.cend(), all_value[i].begin(), all_value[i].end());
  }
  C->row_ptr.emplace_back(C->values.size());

  return true;
}

bool CRSMatMult::post_processing() {
  internal_order_test();

  auto* out_ptr = reinterpret_cast<double*>(taskData->outputs[0]);
  for (std::size_t i = 0; i < C->n_rows; ++i) {
    for (std::size_t j = C->row_ptr[i]; j < C->row_ptr[i + 1]; ++j) {
      out_ptr[i * C->n_cols + C->col_index[j]] = C->values[j];
    }
  }

  return true;
}
