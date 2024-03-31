// Copyright 2024 Smirnov Leonid
#pragma once

#include <string>
#include <vector>
#include <utility>
#include <memory>
#include "core/task/include/task.hpp"

class RadixSortSequential : public ppc::core::Task {
 public:
  explicit RadixSortSequential(std::shared_ptr<ppc::core::TaskData>
  taskData_) : Task(std::move(taskData_)) {}
  bool validation() override;
  bool pre_processing() override;
  bool run() override;
  bool post_processing() override;

 private:
  std::vector<int> work_vector;
};
