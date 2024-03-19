// Copyright 2023 Korablev Nikita
#pragma once

#include <string>
#include <vector>

#include "core/task/include/task.hpp"

struct Funs {
  enum class F { SIN, COS, TWO_SC };

  double fsin(double x);
  double fcos(double x);
  double f_two_sc(double x);
  F cur_fun;

  double curFun(double x);
  void setCurFun(int i);
};

class MonteCarloSequential : public ppc::core::Task {
 public:
  explicit MonteCarloSequential(std::shared_ptr<ppc::core::TaskData> taskData_) : Task(std::move(taskData_)) {}
  bool pre_processing() override;
  bool validation() override;
  bool run() override;
  bool post_processing() override;

 private:
  double a{}, b{};
  int N{};
  double res{};

  Funs function{};
};