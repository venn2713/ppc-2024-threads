// Copyright 2024 Kostin Artem
#pragma once

#include <string>
#include <vector>

#include "core/task/include/task.hpp"

class ConjugateGradientMethodSequential : public ppc::core::Task {
 public:
  explicit ConjugateGradientMethodSequential(std::shared_ptr<ppc::core::TaskData> taskData_) : Task(std::move(taskData_)) {}
  bool pre_processing() override;
  bool validation() override;
  bool run() override;
  bool post_processing() override;

 private:
  std::vector<double> A;
  int size = 0;
  std::vector<double> b;
  std::vector<double> x;
};
