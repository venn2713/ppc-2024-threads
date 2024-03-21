// Copyright 2024 Zorin Oleg

#ifndef PARALLEL_PROGRAMMING_COURSE_TASKS_SEQ_ZORIN_O_CRS_MATMULT_INCLUDE_CRS_MATRIX_HPP_
#define PARALLEL_PROGRAMMING_COURSE_TASKS_SEQ_ZORIN_O_CRS_MATMULT_INCLUDE_CRS_MATRIX_HPP_

#include <vector>

struct CRSMatrix {
  std::vector<size_t> row_ptr;
  std::vector<size_t> col_index;
  std::vector<double> values;
  size_t n_rows;
  size_t n_cols;

  CRSMatrix(size_t n_rows, size_t n_cols);
  CRSMatrix(const double *matrix, size_t n_rows, size_t n_cols);
};

#endif  // PARALLEL_PROGRAMMING_COURSE_TASKS_SEQ_ZORIN_O_CRS_MATMULT_INCLUDE_CRS_MATRIX_HPP_
