// Copyright 2024 Savotina Valeria
#include "seq/savotina_v_grahams_alg/include/point.hpp"

Point::Point() {
  x = 0;
  y = 0;
}

Point::Point(double X, double Y) {
  x = X;
  y = Y;
}

Point::Point(const Point& p2) {
  x = p2.x;
  y = p2.y;
}

Point& Point::operator=(const Point& p2) {
  if (this == &p2) return *this;
  x = p2.x;
  y = p2.y;
  return *this;
}

bool Point::operator==(const Point& p2) const {
  bool res = 0;
  if (x == p2.x && y == p2.y) res = 1;
  return res;
}

double Point::Distance(const Point& p) { return sqrt((p.x - x) * (p.x - x) + (p.y - y) * (p.y - y)); }

void Point::Replace(Point& p2) {
  Point tmp = (*this);
  (*this) = p2;
  p2 = tmp;
}

int Point::Compare(const Point& pivot, const Point P) {
  int res = 0;  // ==
  double x1 = pivot.x - x, y1 = pivot.y - y, x2 = P.x - pivot.x, y2 = P.y - pivot.y;
  double val = x1 * y2 - y1 * x2;

  if (val > 0)
    res = 1;  // 2 upper 1 | 2 > 1
  else if (val < 0)
    res = -1;  // 2 downer 1 | 2 < 1
  else {
    float dist1 = (*this).Distance(pivot), dist2 = (*this).Distance(P);

    if (!(!dist1 && !dist2)) {
      if (dist2 > dist1)
        res = 2;  // 2 > 1
      else if (dist2 < dist1)
        res = -2;  // 2 < 1
    }
  }

  return res;
}
