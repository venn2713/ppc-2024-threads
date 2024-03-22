// Copyright 2023 Simonyan Suren
#pragma once

#include <string>
#include <vector>

#include "core/task/include/task.hpp"

class SparseMatrixMultiSequential : public ppc::core::Task {
 public:
  explicit SparseMatrixMultiSequential(std::shared_ptr<ppc::core::TaskData> taskData_) : Task(std::move(taskData_)) {}
  bool pre_processing() override;
  bool validation() override;
  bool run() override;
  bool post_processing() override;

 private:
  vector<double> values1;
  vector<int> rows1;
  vector<int> colPtr1;
  int numRows1{};
  int numCols1{};
  vector<double> values2;
  vector<int> rows2;
  vector<int> colPtr2;
  int numRows2{};
  int numCols2{};
  double* result;
};
