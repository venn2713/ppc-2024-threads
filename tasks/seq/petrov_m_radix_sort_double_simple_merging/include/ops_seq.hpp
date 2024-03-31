// Copyright 2024 Petrov Maksim

#pragma once
#include <random>
#include <string>
#include <vector>

#include "core/task/include/task.hpp"

class RadixSortDoubleSequential : public ppc::core::Task {
 public:
  explicit RadixSortDoubleSequential(std::shared_ptr<ppc::core::TaskData> taskData_) : Task(std::move(taskData_)) {}
  bool pre_processing() override;
  bool validation() override;
  bool run() override;
  bool post_processing() override;

 private:
  int data_size;
  std::vector<double> sort;
  void countSort(double *const in, double* out, int len, int exp);
  bool countSortSigns(double* in, double* out, int len);
  std::vector<double> radixSort(const std::vector<double>& data1);
};
