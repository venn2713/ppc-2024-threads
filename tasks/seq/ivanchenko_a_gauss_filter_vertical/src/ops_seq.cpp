// Copyright 2024 Ivanchenko Aleksei
#include "seq/ivanchenko_a_gauss_filter_vertical/include/ops_seq.hpp"

#include <thread>

using namespace std::chrono_literals;

bool GaussFilterSequential::pre_processing() {
  internal_order_test();
  // Init value for input and output
  input = taskData->inputs[0];
  output = taskData->outputs[0];
  width = taskData->inputs_count[0];
  height = taskData->inputs_count[1];
  for(size_t i = 0; i < width*height*3; i+=3) {
    Color color(input[i], input[i + 1], input[i + 2]);
    image.push_back(color);
  }
  return true;
}

bool GaussFilterSequential::validation() {
  internal_order_test();
  // Check count elements of output
  return taskData->inputs_count[0] >= 3 && taskData->inputs_count[1] >= 3 &&
  taskData->outputs_count[0] == taskData->inputs_count[0] &&
  taskData->outputs_count[1] == taskData->inputs_count[1];
}

bool GaussFilterSequential::run() {
  internal_order_test();
  std::this_thread::sleep_for(30ms);
  return true;
}

bool GaussFilterSequential::post_processing() {
  internal_order_test();
  for(size_t j = 0; j < width*height; j++) {
    size_t i = 3*j;
    output[i] = image[j].R;
    output[i + 1] = image[j].G;
    output[i + 2] = image[j].B; 
  }
  return true;
}
