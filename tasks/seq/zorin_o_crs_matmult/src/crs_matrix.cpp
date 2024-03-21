// Copyright 2024 Zorin Oleg

#include "seq/zorin_o_crs_matmult/include/crs_matrix.hpp"

#include <cmath>

CRSMatrix::CRSMatrix(size_t n_rows, size_t n_cols) : n_rows(n_rows), n_cols(n_cols) {}

CRSMatrix::CRSMatrix(const double *matrix, size_t n_rows, size_t n_cols) : n_rows(n_rows), n_cols(n_cols) {
  for (size_t i = 0; i < n_rows; ++i) {
    row_ptr.push_back(values.size());
    for (size_t j = 0; j < n_cols; ++j) {
      double val = matrix[i * n_cols + j];
      if (std::abs(val) > 1e-8) {
        values.push_back(val);
        col_index.push_back(j);
      }
    }
  }
  row_ptr.push_back(values.size());
}
