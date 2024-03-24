// Copyright 2024 Kulaev Zhenya
#include "seq/kulaev_e_block_cannons/include/ops_seq.hpp"

#include <algorithm>
#include <iostream>
#include <random>
#include <vector>

bool TestTaskSequentialCannon::pre_processing() {
  internal_order_test();
  // Init value for input and output

  A = std::vector<double>(taskData->inputs_count[0]);
  B = std::vector<double>(taskData->inputs_count[1]);

  n = *reinterpret_cast<int*>(taskData->inputs[2]);
  m = *reinterpret_cast<int*>(taskData->inputs[3]);

  auto* tmp_ptr_A = reinterpret_cast<double*>(taskData->inputs[0]);
  for (unsigned i = 0; i < taskData->inputs_count[0]; i++) {
    A[i] = tmp_ptr_A[i];
  }

  auto* tmp_ptr_B = reinterpret_cast<double*>(taskData->inputs[1]);
  for (unsigned i = 0; i < taskData->inputs_count[1]; i++) {
    B[i] = tmp_ptr_B[i];
  }
  return true;
}

bool TestTaskSequentialCannon::validation() {
  internal_order_test();
  // Check count elements of output
  return taskData->inputs_count[0] == taskData->inputs_count[1] &&
         taskData->inputs_count[0] == taskData->outputs_count[0] &&
         taskData->inputs_count[1] == taskData->outputs_count[0];
}

bool TestTaskSequentialCannon::run() {
  internal_order_test();
  result = cannonMatrixMultiplication(A, B, n, m);
  return true;
}

bool TestTaskSequentialCannon::post_processing() {
  internal_order_test();
  std::copy(result.begin(), result.end(), reinterpret_cast<double*>(taskData->outputs[0]));
  return true;
}
