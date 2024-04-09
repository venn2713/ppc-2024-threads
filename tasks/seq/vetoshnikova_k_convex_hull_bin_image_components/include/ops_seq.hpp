// Copyright 2024 Vetoshnikova Ekaterina
#pragma once

#include <algorithm>
#include <cmath>
#include <functional>
#include <iostream>
#include <map>
#include <stack>
#include <string>
#include <utility>
#include <vector>

#include "core/task/include/task.hpp"

void markComponents(std::vector<int>* image, int w, int h, int startY, int startX, int label);
std::vector<int> removePoints(const std::vector<int>& image, int w, int h, int label);
std::vector<int> findComponents(const std::vector<std::vector<int>>& image, int w, int h);
int countComponents(const std::vector<int>& image);
int countPointsComponent(const std::vector<int>& image);
void Sort(std::vector<int>* component, int minX, int minY);
std::vector<int> AlgorithmGraham(std::vector<int> component);

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
