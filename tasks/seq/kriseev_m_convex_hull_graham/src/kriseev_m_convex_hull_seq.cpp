// Copyright 2024 Kriseev Mikhail
#include "seq/kriseev_m_convex_hull_graham/include/kriseev_m_convex_hull_seq.hpp"

#include <algorithm>
#include <limits>

double angle(const KriseevMTaskSeq::Point &origin, const KriseevMTaskSeq::Point &point) {
  double dx = point.first - origin.first;
  double dy = point.second - origin.second;
  if (dx == 0.0 && dy == 0.0) {
    return 0.0;
  }
  // Calculating angle using algorithm from https://stackoverflow.com/a/14675998/14116050
  return (dy >= 0) ? (dx >= 0 ? dy / (dx + dy) : 1 - dx / (-dx + dy))
                   : (dx < 0 ? 2 - dy / (-dx - dy) : 3 + dx / (dx - dy));
}

bool checkOrientation(const KriseevMTaskSeq::Point &origin, const KriseevMTaskSeq::Point &a,
                      const KriseevMTaskSeq::Point &b) {
  double dxA = a.first - origin.first;
  double dyA = a.second - origin.second;
  double dxB = b.first - origin.first;
  double dyB = b.second - origin.second;
  // Using cross product to check orientation
  return dxA * dyB - dyA * dxB < 0;
}

bool KriseevMTaskSeq::ConvexHullTask::pre_processing() {
  if (taskData->inputs_count.at(0) != taskData->inputs_count.at(1)) {
    return false;
  }
  auto *pointsX = reinterpret_cast<double *>(taskData->inputs.at(0));
  auto *pointsY = reinterpret_cast<double *>(taskData->inputs.at(1));
  points = std::vector<std::pair<double, double>>();
  points.reserve(taskData->inputs_count[0]);
  for (size_t i = 0; i < taskData->inputs_count[0]; ++i) {
    points.emplace_back(pointsX[i], pointsY[i]);
  }

  return true;
}

bool KriseevMTaskSeq::ConvexHullTask::validation() {
  if (points.size() < 3) {
    return false;
  }
  for (uint32_t i = 0; i < points.size(); ++i) {
    if (points[i].first == std::numeric_limits<double>::quiet_NaN() ||
        points[i].second == std::numeric_limits<double>::quiet_NaN() ||
        points[i].first == std::numeric_limits<double>::infinity() ||
        points[i].second == std::numeric_limits<double>::infinity()) {
      return false;
    }
  }
  return true;
}

bool KriseevMTaskSeq::ConvexHullTask::run() {
  Point origin =
      *std::min_element(points.begin(), points.end(), [](auto &a, auto &b) -> bool { return a.second < b.second; });
  std::sort(points.begin(), points.end(), [origin](auto &a, auto &b) -> bool {
    double angleA = angle(origin, a);
    double angleB = angle(origin, b);
    if (angleA < angleB) {
      return true;
    }
    if (angleA > angleB) {
      return false;
    }
    double dxA = a.first - origin.first;
    double dyA = a.second - origin.second;
    double dxB = b.first - origin.first;
    double dyB = b.second - origin.second;
    // The further point must be first
    // so the others will be ignored
    return dxA * dxA + dyA * dyA > dxB * dxB + dyB * dyB;
  });
  std::vector<Point> hull;
  hull.reserve(points.size());
  hull.push_back(points[0]);
  hull.push_back(points[1]);
  hull.push_back(points[2]);

  for (uint32_t i = 3; i < points.size(); ++i) {
    while (hull.size() > 1 && !checkOrientation(hull.back(), *(hull.end() - 2), points[i])) {
      hull.pop_back();
    }
    hull.push_back(points[i]);
  }
  this->finalHull = hull;
  return true;
}

bool KriseevMTaskSeq::ConvexHullTask::post_processing() {
  auto *resultsX = reinterpret_cast<double *>(taskData->outputs[0]);
  auto *resultsY = reinterpret_cast<double *>(taskData->outputs[1]);
  for (size_t i = 0; i < finalHull.size(); ++i) {
    resultsX[i] = finalHull[i].first;
    resultsY[i] = finalHull[i].second;
  }
  taskData->outputs_count[0] = finalHull.size();
  taskData->outputs_count[1] = finalHull.size();
  return true;
}
