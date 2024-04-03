// Copyright 2024 Veselov Mikhail
#pragma once

#include <complex>
#include <random>
#include <vector>

#include "core/task/include/task.hpp"

struct sparse_matrix {
  int row_num, col_num;
  int nonzeros;
  std::vector<int> col_ptr;
  std::vector<int> rows;
  std::vector<std::complex<double>> values;

  sparse_matrix(int row_num_ = 0, int col_num_ = 0, int nonzeros_ = 0)
      : row_num(row_num_),
        col_num(col_num_),
        nonzeros(nonzeros_),
        col_ptr(row_num + 1),
        rows(nonzeros),
        values(nonzeros) {}
};

class SpgemmCSCComplexSeq : public ppc::core::Task {
 public:
  explicit SpgemmCSCComplexSeq(std::shared_ptr<ppc::core::TaskData> taskData_) : Task(std::move(taskData_)) {}
  bool pre_processing() override;
  bool validation() override;
  bool run() override;
  bool post_processing() override;

 private:
  sparse_matrix *A, *B, *C;
};
