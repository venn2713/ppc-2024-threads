// Copyright 2024 Savotina Valeria
#pragma once

#include <cmath>

struct Point {
  double x;
  double y;

  Point();
  Point(double X, double Y);

  Point& operator=(const Point& p2);
  bool operator==(const Point& p2);

  double Distance(const Point& p);
  void Replace(Point& p2);
  int Compare(const Point& pivot, const Point P);
};
