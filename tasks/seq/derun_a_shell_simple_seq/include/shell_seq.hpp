// Copyright 2024 Andrey Derun
#pragma once

#include <string>
#include <vector>

#include "core/task/include/task.hpp"

class ShellSequential : public ppc::core::Task {
 public:
  explicit ShellSequential(std::shared_ptr<ppc::core::TaskData> taskData_) : Task(std::move(taskData_)) {}
  bool pre_processing() override;
  bool validation() override;
  bool run() override;
  bool post_processing() override;

 private:
  int input_{}, res{};
};
