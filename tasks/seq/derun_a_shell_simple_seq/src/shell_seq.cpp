// Copyright 2024 Andrey Derun
#include "seq/example/include/shell_seq.hpp"

#include <thread>

using namespace std::chrono_literals;

bool ShellSequential::pre_processing() {
  internal_order_test();
  // Init value for input and output
  input_ = reinterpret_cast<int*>(taskData->inputs[0])[0];
  res = 0;
  return true;
}

bool ShellSequential::validation() {
  internal_order_test();
  // Check count elements of output
  return taskData->inputs_count[0] == 1 && taskData->outputs_count[0] == 1;
}

bool ShellSequential::run() {
  internal_order_test();
  for (int i = 0; i < input_; i++) {
    res++;
  }
  std::this_thread::sleep_for(20ms);
  return true;
}

bool ShellSequential::post_processing() {
  internal_order_test();
  reinterpret_cast<int*>(taskData->outputs[0])[0] = res;
  return true;
}
