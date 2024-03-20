// Copyright 2024 Korablev Nikita
#include "seq/korablev_n_montecarlo/include/ops_seq.hpp"

#include <cmath>
#include <thread>

using namespace std::chrono_literals;

double Funs::flin(double x, double y) { return x + y; }
double Funs::fsinxPsiny(double x, double y) { return sin(x) + sin(y); }
double Funs::fcosxPcosy(double x, double y) { return cos(x) + cos(y); }
double Funs::fsinxMcosy(double x, double y) { return 2 * sin(x) * cos(y); }

double Funs::curFun(double x, double y) {
  switch (cur_fun) {
    case F::SINPSIN:
      return fsinxPsiny(x, y);
    case F::COSPCOS:
      return fcosxPcosy(x, y);
    case F::SINMCOS:
      return fsinxMcosy(x, y);
    case F::LIN:
      return flin(x, y);;
  }
  return 0;
};

void Funs::setCurFun(int i) {
  switch (i) {
    case 0:
      cur_fun = F::SINPSIN;
      break;
    case 1:
      cur_fun = F::COSPCOS;
      break;
    case 2:
      cur_fun = F::SINMCOS;
      break;
    case 3:
      cur_fun = F::LIN;
      break;
    default:
      cur_fun = F::SINPSIN;
      break;
  }
};

bool MonteCarloSequential::pre_processing() {
  internal_order_test();
  // Init value for input and output
  Int1[0] = reinterpret_cast<double*>(taskData->inputs[0])[0];
  Int1[1] = reinterpret_cast<double*>(taskData->inputs[0])[1];
  Int2[0] = reinterpret_cast<double*>(taskData->inputs[1])[0];
  Int2[1] = reinterpret_cast<double*>(taskData->inputs[1])[1];

  auto ind = reinterpret_cast<double*>(taskData->inputs[1])[2];
  function.setCurFun(static_cast<int>(ind));
  N = 1000;

  res = 0.0;
  return true;
}

bool MonteCarloSequential::validation() {
  internal_order_test();
  // Check count elements of output
  return taskData->inputs_count[0] == 2 &&
         taskData->outputs_count[0] == 1;
}

bool MonteCarloSequential::run() {
  internal_order_test();

  double h1 = (Int1[1] - Int1[0]) / static_cast<double>(N);
  double h2 = (Int2[1] - Int2[0]) / static_cast<double>(N);

  int i, j;
  for (j = 0; j < N; ++j) {
    double y = Int2[0] + h2 * j;
    double sum = 0;
    for (i = 0; i < N; ++i) {
      double x = Int1[0] + h1 * i;
      sum += function.curFun(x, y);
    }
    res += sum * h1;
  }
  res *= h2;
  std::cout << res << std::endl;

  std::this_thread::sleep_for(20ms);
  return true;
}

bool MonteCarloSequential::post_processing() {
  internal_order_test();
  double real_var = reinterpret_cast<double*>(taskData->outputs[0])[0];
  std::cout << "real_var: " << real_var << std::endl;
  std::cout << "res: " << res << std::endl;
  std::cout << "out: " << real_var - res << std::endl;

  reinterpret_cast<double*>(taskData->outputs[0])[0] = res;
  return true;
}
