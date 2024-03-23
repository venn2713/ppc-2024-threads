// Copyright 2024 Kulaev Zhenya
#pragma once

#include <memory>
#include <random>
#include <string>
#include <utility>
#include <vector>

#include "core/task/include/task.hpp"

class TestTaskSequentialCannon : public ppc::core::Task {
 public:
  explicit TestTaskSequentialCannon(
      std::shared_ptr<ppc::core::TaskData> taskData_)
      : Task(std::move(taskData_)) {}
  bool pre_processing() override;
  bool validation() override;
  bool run() override;
  bool post_processing() override;

 private:
  std::vector<double> A;
  std::vector<double> B;
  std::vector<double> result;
  int n = 0, m = 0;
};

inline std::vector<double> getRandomMatrix(int rows, int cols) {
  std::random_device dev;
  std::mt19937 gen(dev());
  std::uniform_real_distribution<double> dis(1.0, 20.0);

  std::vector<double> matrix(rows * cols);

  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      matrix[i * cols + j] = dis(gen);
    }
  }

  return matrix;
}

inline std::vector<double> multiplyBlocks(const std::vector<double>& A,
                                          const std::vector<double>& B,
                                          int rows_A, int col_B) {
  int col_A = rows_A;
  std::vector<double> C(rows_A * col_B, 0.0);

  for (int i = 0; i < rows_A; ++i) {
    for (int j = 0; j < col_B; ++j) {
      for (int k = 0; k < col_A; ++k) {
        C[i * col_B + j] += A[i * col_A + k] * B[k * col_B + j];
      }
    }
  }
  return C;
}
