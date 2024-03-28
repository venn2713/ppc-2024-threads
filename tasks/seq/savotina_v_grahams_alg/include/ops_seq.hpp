// Copyright 2024 Savotina Valeria
#pragma once

#include <vector>

#include "core/task/include/task.hpp"
#include "tasks/seq/savotina_v_grahams_alg/include/point.hpp"

class GrahamsAlgorithmSequential : public ppc::core::Task {
 public:
  explicit GrahamsAlgorithmSequential(
      std::shared_ptr<ppc::core::TaskData> taskData_)
      : Task(std::move(taskData_)) {}
  bool pre_processing() override;
  bool validation() override;
  bool run() override;
  bool post_processing() override;

 private:
  std::vector<Point> pointsArr, minConvexHull;
};
