//
// Created by Стёпа on 29.03.2024.
//

#pragma once
#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include "core/task/include/task.hpp"
namespace KashinDijkstraSeq {

class Dijkstra : public ppc::core::Task {
 public:
  explicit Dijkstra(std::shared_ptr<ppc::core::TaskData> taskData_) : Task(std::move(taskData_)) {}
  bool pre_processing() override;
  bool validation() override;
  bool run() override;
  bool post_processing() override;

 private:
  int* graph;
  std::vector<int> distance;
  int start{};
  int count{};
};
} // namespace KashinDijkstraSeq to
