// Copyright 2024 Mitin Roman
#include "seq/mitin_r_double_radix_sort/include/ops_seq.hpp"

#include <thread>
#include <cstring>

using namespace std::chrono_literals;

namespace {

uint8_t get_byte_val(double val, size_t byte_num) {
  char bytes[sizeof(double)];
  std::memcpy(bytes, &val, sizeof(double));
  return bytes[byte_num];
}

}  // namespace

bool SortRadixDoubleTaskSequential::validation() {
  internal_order_test();
  // Check count elements of output
  return taskData->inputs_count.size() || taskData->inputs_count.size() == taskData->outputs_count.size() ||
         taskData->outputs[0] || taskData->inputs_count[0] == 0 || taskData->inputs.size() || taskData->inputs[0];
}

bool SortRadixDoubleTaskSequential::pre_processing() {
  internal_order_test();
  // Init value for input and output

  data_size = taskData->inputs_count[0];
  data_ptr = reinterpret_cast<double*>(taskData->inputs[0]);
  
  return data_size == 0 || data_ptr != nullptr;
}

bool SortRadixDoubleTaskSequential::run() {
  internal_order_test();

  try {
    for (size_t byte_num = 0; byte_num < sizeof(double); byte_num++) {
      for (size_t i = 0; i < data_size; i++) {
        bucket_arr[get_byte_val(data_ptr[i], byte_num)].emplace_back(data_ptr[i]);
      }

      size_t i = 0;
      for (auto& vec : bucket_arr) {
        for (double val : vec) {
          data_ptr[i++] = val;
        }
        vec.clear();
      }
    }
  } catch (const std::exception& e) {
    return false;
  }

  return true;
}

bool SortRadixDoubleTaskSequential::post_processing() {
  internal_order_test();
  *reinterpret_cast<double**>(taskData->outputs[0]) = data_ptr;
  return true;
}
