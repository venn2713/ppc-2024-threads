// Copyright 2024 Kozlov Mikhail
#pragma once

#include <cmath>
#include <memory>
#include <utility>
#include <vector>
#include <functional>

#include "core/task/include/task.hpp"

typedef double(*FUNC) (double, double) ;


double xy(double x, double y);
double siny(double x, double y);
double linear(double x, double y);
double expx(double x, double y);
double expy(double x, double y);

class KozlovTaskSequential : public ppc::core::Task {
 public:
  explicit KozlovTaskSequential(std::shared_ptr<ppc::core::TaskData> taskData_) : Task(std::move(taskData_)) {}
  bool pre_processing() override;
  bool validation() override;
  bool run() override;
  bool post_processing() override;

 private:
  FUNC f{};
  double x1{}, x2{}, y1{}, y2{};
  uint64_t n;
  uint64_t m;
  double res;
};