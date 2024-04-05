// Copyright 2024 Ivan Novostroev
#pragma once

#include <algorithm>
#include <chrono>
#include <random>
#include <string>
#include <thread>
#include <vector>

#include "core/task/include/task.hpp"

class BatcherMergeSeq : public ppc::core::Task {
 private:
  std::vector<int> vector, result, part1, part2;

 public:
  explicit BatcherMergeSeq(std::shared_ptr<ppc::core::TaskData> taskData_) : Task(std::move(taskData_)) {}
  bool run() override;
  bool validation() override;
  bool pre_processing() override;
  bool post_processing() override;
};

inline std::vector<int> randomVector(int size) {
  std::random_device rd;
  std::uniform_int_distribution<int> unif(0, 1000000);
  std::vector<int> vector(size);
  for (int i = 0; i < size; i++) {
    vector[i] = unif(rd);
  }

  return vector;
}
