// Copyright 2024 Korablev Nikita
#include "seq/korablev_n_montecarlo/include/ops_seq.hpp"

#include <cmath>
#include <thread>

using namespace std::chrono_literals;

double Funs::fsin(double x) { return sin(x); }
double Funs::fcos(double x) { return cos(x); }
double Funs::f_two_sc(double x) { return 2*sin(x)*cos(x); }

double Funs::curFun(double x) {
  switch (cur_fun) {
    case F::SIN:
      return fsin(x);
    case F::COS:
      return fcos(x);
    case F::TWO_SC:
      return f_two_sc(x);
  }
  return 0;
};

void Funs::setCurFun(int i) {
  switch (i) {
    case 0:
      cur_fun = F::SIN;
      break;
    case 1:
      cur_fun = F::COS;
      break;
    case 2:
      cur_fun = F::TWO_SC;
      break;
    default:
      cur_fun = F::SIN;
      break;
  }
};

bool MonteCarloSequential::pre_processing() {
  internal_order_test();
  // Init value for input and output
  a = reinterpret_cast<double*>(taskData->inputs[0])[0];
  b = reinterpret_cast<double*>(taskData->inputs[0])[1];
  auto ind = reinterpret_cast<double*>(taskData->inputs[0])[2];
  function.setCurFun(static_cast<int>(ind));
  N = 100000;

  res = 0.0;
  return true;
}

bool MonteCarloSequential::validation() {
  internal_order_test();
  // Check count elements of output
  return taskData->inputs_count[0] == 3 && taskData->outputs_count[0] == 1;
}

bool MonteCarloSequential::run() {
  internal_order_test();

  double h = (b - a) / static_cast<double>(N);
  for (int i = 0; i < N; ++i) {
    res += function.curFun(a + h*i);
  }
  res = h*res;

  std::this_thread::sleep_for(20ms);
  return true;
}

bool MonteCarloSequential::post_processing() {
  internal_order_test();
  double real_var = reinterpret_cast<double*>(taskData->outputs[0])[0];
  reinterpret_cast<double*>(taskData->outputs[0])[0] = std::abs(real_var - res);
  return true;
}
