// Copyright 2024 Durandin Vladimir
#include <thread>

#include "seq/durandin_v_Jarvis/include/ops_seq.hpp"

double Jarvis::PolarAngle(Jarvis::Point2d P, Jarvis::Point2d Q) {
  double dx = Q.x - P.x;
  double dy = Q.y - P.y;
  return atan2(dy, dx);
}

Jarvis::Point2d Jarvis::FindNextPoint(std::vector<Jarvis::Point2d>& points, Jarvis::Point2d P) {
  Jarvis::Point2d next = points[0];
  double max_angle = Jarvis::PolarAngle(P, points[0]);
  for (size_t i = 1; i < points.size(); ++i) {
    double angle = Jarvis::PolarAngle(P, points[i]);
    if (angle > max_angle) {
      max_angle = angle;
      next = points[i];
    }
  }
  return next;
}

std::vector<Jarvis::Point2d> Jarvis::JarvisAlg(std::vector<Jarvis::Point2d>& points) {
  // Находим стартовую точку
  Jarvis::Point2d P = points[0];
  for (size_t i = 1; i < points.size(); ++i) {
    if (points[i].x < P.x || (points[i].x == P.x && points[i].y > P.y)) {
      P = points[i];
    }
  }

  // Инициализация оболочки
  std::vector<Jarvis::Point2d> hull;
  hull.push_back(P);

  // Поиск вершин оболочки
  while (true) {
    Jarvis::Point2d next = FindNextPoint(points, P);
    if (next == hull[0]) {
      break;
    }
    hull.push_back(next);
    P = next;
  }
  return hull;
}

bool Jarvis::JarvisTestTaskSequential::pre_processing() { 
  internal_order_test();
  try
  {
    points_count = taskData->inputs_count[0];
    ptr_points = std::make_shared<Jarvis::Point2d>(*reinterpret_cast<Jarvis::Point2d*>(taskData->inputs[0]));
    Jarvis::Point2d* raw_ptr = ptr_points.get();
    for(uint32_t i = 0; i < points_count; ++i)
    {
      points[i] = raw_ptr[i];
    }
  }
  catch(const std::exception& e)
  {
    std::cerr << e.what() << '\n';
    return false;
  }
  return true; 
}

bool Jarvis::JarvisTestTaskSequential::validation() { 
  internal_order_test();
  return (taskData->inputs_count[0] >= 0) && (taskData->inputs[0] != nullptr);
}

bool Jarvis::JarvisTestTaskSequential::run() { 
  internal_order_test();
  try
  {
    convex_hull = Jarvis::JarvisAlg(points);
  }
  catch(const std::exception& e)
  {
    std::cerr << e.what() << '\n';
    return false;
  }
  return true;
}

bool Jarvis::JarvisTestTaskSequential::post_processing() { 
  internal_order_test();
  try
  {
    std::shared_ptr<Jarvis::Point2d> convex_hull_data = std::make_shared<Jarvis::Point2d>(*reinterpret_cast<Jarvis::Point2d*>(taskData->outputs[0]));
    // Jarvis::Point2d* convex_hull_data = reinterpret_cast<Jarvis::Point2d*>(taskData->outputs[0]);
    convex_hull_data = std::make_shared<Jarvis::Point2d>(convex_hull[0]);
  }
  catch(const std::exception& e)
  {
    std::cerr << e.what() << '\n';
    return false;
  }
  return true;
 }
