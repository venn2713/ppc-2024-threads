// Copyright 2024 Isaev Dmitriy
#include "seq/isaev_d_sparse_mult_double_crs/include/ops_seq.hpp"

#include <thread>

bool SparseMultDoubleCRS::pre_processing() {
  internal_order_test();
  // Init value for input and output
  A = reinterpret_cast<SparseMatrix*>(taskData->inputs[0]);
  B = reinterpret_cast<SparseMatrix*>(taskData->inputs[1]);
  C = reinterpret_cast<SparseMatrix*>(taskData->outputs[0]);

  C->rows = A->rows;
  C->columns = B->columns;

  // Allocate memory for result
  // C->values.resize(C->rows * C->columns, 0.0);
  C->values.clear();
  C->column_indices.clear();
  C->row_pointers.resize(C->rows + 1, 0);
  return true;
}

bool SparseMultDoubleCRS::validation() {
  internal_order_test();
  A = reinterpret_cast<SparseMatrix*>(taskData->inputs[0]);
  B = reinterpret_cast<SparseMatrix*>(taskData->inputs[1]);
  C = reinterpret_cast<SparseMatrix*>(taskData->outputs[0]);
  // Check count elements of output
  return B->rows == A->columns;
}

bool SparseMultDoubleCRS::run() {
  internal_order_test();

  std::vector<std::vector<double>> temp(C->rows, std::vector<double>(C->columns, 0.0));
  for (int i = 0; i < A->rows; ++i) {
    for (int k = A->row_pointers[i]; k < A->row_pointers[i + 1]; ++k) {
      int j = A->column_indices[k];
      for (int l = B->row_pointers[j]; l < B->row_pointers[j + 1]; ++l) {
        int m = B->column_indices[l];
        temp[i][m] += A->values[k] * B->values[l];
      }
    }
  }

  int nnz = 0;
  for (int i = 0; i < C->rows; ++i) {
    C->row_pointers.push_back(nnz);
    for (int j = 0; j < C->columns; ++j) {
      if (temp[i][j] != 0.0) {
        C->values.push_back(temp[i][j]);
        C->column_indices.push_back(j);
        nnz++;
      }
    }
  }
  C->row_pointers.push_back(nnz);

  return true;
}

bool SparseMultDoubleCRS::post_processing() {
  internal_order_test();

  return true;
}
