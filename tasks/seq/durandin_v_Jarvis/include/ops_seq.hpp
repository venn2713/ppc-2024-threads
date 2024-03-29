// Copyright 2024 Durandin Vladimir
#pragma once

#include <string>
#include <vector>

#include "core/task/include/task.hpp"

namespace Jarvis {
struct Point2d {
  double x, y;

  bool operator==(const Point2d& other) const { return x == other.x && y == other.y; }
};

// // Finds the polar angle of point Q relative to point P
// double PolarAngle(Point2d P, Point2d Q);

// // Finds the point with the maximum polar angle
// Point2d FindNextPoint(std::vector<Point2d>& points, Point2d P);

// // Jarvis algorithm
// std::vector<Point2d> JarvisAlg(std::vector<Point2d>& points);

std::vector<Point2d> convexHull(const std::vector<Point2d>& points);

class JarvisTestTaskSequential : public ppc::core::Task {
 public:
  explicit JarvisTestTaskSequential(std::shared_ptr<ppc::core::TaskData> taskData_) : Task(std::move(taskData_)) {}
  bool pre_processing() override;
  bool validation() override;
  bool run() override;
  bool post_processing() override;

 private:
  uint32_t points_count{};
  std::vector<Point2d> points{}, convex_hull{};
  // std::shared_ptr<Point2d> ptr_points{};
};
}  // namespace Jarvis
