// Copyright 2024 Veselov Mikhail
#include "seq/veselov_m_complex-matrx-mult-ccs/include/ops_seq.hpp"

#include <iostream>
#include <complex>
#include <random>
#include <vector>
#include <unordered_set>


bool SpgemmCSCComplexSeq::pre_processing() {
  internal_order_test();
  A = reinterpret_cast<sparse_matrix*>(taskData->inputs[0]);
  B = reinterpret_cast<sparse_matrix*>(taskData->inputs[1]);
  C = reinterpret_cast<sparse_matrix*>(taskData->outputs[0]);
  return true;
}

bool SpgemmCSCComplexSeq::validation() {
  internal_order_test();
  int A_col_num = reinterpret_cast<sparse_matrix*>(taskData->inputs[0])->col_num;
  int B_row_num = reinterpret_cast<sparse_matrix*>(taskData->inputs[1])->row_num;
  return (A_col_num == B_row_num);
}

bool SpgemmCSCComplexSeq::run() {
  internal_order_test();

  // символьный этап
  C->row_num = A->row_num;
  C->col_num = B->col_num;
  C->col_ptr.resize(C->col_num + 1);
  C->col_ptr[0] = 0;
  std::vector<int> present_elements(C->row_num);
  for (int b_col = 0; b_col < C->col_num; ++b_col) {
    for (int c_row = 0; c_row < C->row_num; ++c_row) {
      present_elements[c_row] = 0;
    }
    for (int b_idx = B->col_ptr[b_col]; b_idx < B->col_ptr[b_col + 1]; ++b_idx) {
      int b_row = B->rows[b_idx];
      for (int a_idx = A->col_ptr[b_row]; a_idx < A->col_ptr[b_row + 1]; ++a_idx) {
        present_elements[A->rows[a_idx]] = 1;
      }
    }
    int col_nonzero_count = 0;
    for (int c_row = 0; c_row < C->row_num; ++c_row) {
      col_nonzero_count += present_elements[c_row];
    }
    C->col_ptr[b_col + 1] = col_nonzero_count + C->col_ptr[b_col];
  }

  int total_nonzeros = C->col_ptr[C->col_num];
  C->nonzeros = total_nonzeros;
  C->rows.resize(total_nonzeros);
  C->values.resize(total_nonzeros);

  // численный этап
  std::complex<double> zero;
  std::complex<double> b_value;
  std::vector<std::complex<double>> accumulator;
  accumulator.reserve(C->row_num);
  for (int b_col = 0; b_col < C->col_num; ++b_col) {
    std::unordered_set<int> counted_rows;
    for (int b_idx = B->col_ptr[b_col]; b_idx < B->col_ptr[b_col + 1]; ++b_idx) {
      int b_row = B->rows[b_idx];
      for (int a_idx = A->col_ptr[b_row]; a_idx < A->col_ptr[b_row + 1]; ++a_idx) {
        int a_row = A->rows[a_idx];
          if (counted_rows.find(a_row) == counted_rows.end()) {
            accumulator[a_row] += A->values[a_idx] * B->values[b_idx];
            counted_rows.insert(a_row);
          }
      }
    }

    int c_pos = C->col_ptr[b_col];
    for (int c_row = 0; c_row < C->row_num; ++c_row) {
      if (present_elements[c_row] != 0) {
       C->rows[c_pos] = c_row;
        C->values[c_pos++] = accumulator[c_row];
      }
    }
  }

  return true;
}

bool SpgemmCSCComplexSeq::post_processing() {
  internal_order_test();
  return true;
}
