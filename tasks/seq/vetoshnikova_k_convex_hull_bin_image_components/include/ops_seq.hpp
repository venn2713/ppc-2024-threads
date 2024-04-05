// Copyright 2024 Vetoshnikova Ekaterina
#pragma once

#include <algorithm>
#include <cmath>
#include <functional>
#include <iostream>
#include <map>
#include <queue>
#include <stack>
#include <string>
#include <utility>
#include <vector>

#include "core/task/include/task.hpp"

void mark_component(std::vector<int>* image, int height, int width, int yStart, int xStart, int label);
std::vector<int> remove_extra_points(const std::vector<int>& image, int width, int height, int label);
std::vector<int> find_components(const std::vector<std::vector<int>>& image, int width, int height);
int count_components(const std::vector<int>& image);
int count_points_component(const std::vector<int>& image);
void Sort(std::vector<int>* points, int xMin, int yMin);
std::vector<int> Algorithm_Graham(std::vector<int> points);

class TaskSequential : public ppc::core::Task {
 public:
  explicit TaskSequential(std::shared_ptr<ppc::core::TaskData> taskData_) : Task(std::move(taskData_)) {}
  bool pre_processing() override;
  bool validation() override;
  bool run() override;
  bool post_processing() override;

 private:
  std::vector<std::vector<int>>* image_{};
  std::vector<std::vector<int>> image;
  std::vector<int> hull{};
  int w, h;
};
