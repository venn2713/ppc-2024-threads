// Copyright 2024 Durandin Vladimir
#include <thread>

#include "seq/durandin_v_Jarvis/include/ops_seq.hpp"

// Функция для построения выпуклой оболочки методом Джарвиса
std::vector<Jarvis::Point2d> Jarvis::convexHull(const std::vector<Jarvis::Point2d>& points)
{
    size_t n = points.size();
    if (n < 3) return std::vector<Jarvis::Point2d>{}; // Нужно минимум 3 точки

    // Функция для определения ориентации трёх точек
    auto orientation = [](Jarvis::Point2d p, Jarvis::Point2d q, Jarvis::Point2d r)
    {
      double val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
      if (val == 0.0) return 0;  // Коллинеарные
        return (val > 0.0) ? 1 : 2; // По часовой стрелке или против
    };

    // Найдем самую левую нижнюю точку
    size_t leftmost = 0;
    for (size_t i = 1; i < n; ++i) {
        if (points[i].x < points[leftmost].x)
            leftmost = i;
        else if (points[i].x == points[leftmost].x && points[i].y < points[leftmost].y)
            leftmost = i;
    }

    // Начнем обход с самой левой нижней точки
    size_t current = leftmost, next;
    std::vector<Jarvis::Point2d> hull;

    do {
        hull.push_back(points[current]);
        next = (current + 1) % n;
        for (size_t i = 0; i < n; ++i) {
            if (orientation(points[current], points[i], points[next]) == 2)
                next = i;
        }
        current = next;
    } while (current != leftmost);

    // Выводим вершины выпуклой оболочки
    return hull;
}






bool Jarvis::JarvisTestTaskSequential::pre_processing() { 
  internal_order_test();
  try
  {
    points_count = taskData->inputs_count[0];
    points.resize(points_count);
    Jarvis::Point2d *ptr_points = reinterpret_cast<Jarvis::Point2d*>(taskData->inputs[0]);
    std::memcpy(points.data(), ptr_points, points_count * sizeof(Jarvis::Point2d));
    // ptr_points = std::make_shared<Jarvis::Point2d>(*reinterpret_cast<Jarvis::Point2d*>(taskData->inputs[0]));
    // Jarvis::Point2d* raw_ptr = ptr_points.get();
    // std::memcpy(points.data(), raw_ptr, points_count);
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
    convex_hull = convexHull(points);
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
    Jarvis::Point2d* output_ptr = reinterpret_cast<Jarvis::Point2d*>(taskData->outputs[0]);
    std::memcpy(output_ptr, convex_hull.data(), convex_hull.size() * sizeof(Jarvis::Point2d));
  }
  catch(const std::exception& e)
  {
    std::cerr << e.what() << '\n';
    return false;
  }
  return true;
 }
