// Copyright 2024 Sadikov Damir
#pragma once

#include <string>
#include <vector>
#include <complex>

#include "core/task/include/task.hpp"

struct matrix_CRS {
  int n, m;
  std::vector<int> row_id;
  std::vector<int> col;
  std::vector<std::complex<float>> value;
};

class CRSComplexMult_Sequential : public ppc::core::Task {
 public:
  explicit CRSComplexMult_Sequential(std::shared_ptr<ppc::core::TaskData> taskData_) : Task(std::move(taskData_)) {}
  bool validation() override;
  bool pre_processing() override;
  bool run() override;
  bool post_processing() override;

 private:
  int input_{}, res{};
  //matrix_CRS *A, *B, *C;
};
