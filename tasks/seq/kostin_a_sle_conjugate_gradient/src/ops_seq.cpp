// Copyright 2024 Kostin Artem
#include "seq/kostin_a_sle_conjugate_gradient/include/ops_seq.hpp"

#include <thread>

using namespace std::chrono_literals;

std::vector<double> dense_matrix_vector_multiply(const std::vector<double>& A, int n, const std::vector<double>& x) {
  std::vector<double> result(n, 0.0);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      result[i] += A[i * n + j] * x[j];
    }
  }
  return result;
}

double dot_product(const std::vector<double>& a, const std::vector<double>& b) {
  double result = 0.0;
  for (int i = 0; i < a.size(); ++i) {
    result += a[i] * b[i];
  }
  return result;
}

std::vector<double> conjugate_gradient(const std::vector<double>& A, int n, const std::vector<double>& b, double tolerance) {
  std::vector<double> x(n, 0.0);
  std::vector<double> r = b;
  std::vector<double> p = r;
  std::vector<double> r_prev = b;

  for (int k = 0; k < n; ++k) {
    std::vector<double> Ap = dense_matrix_vector_multiply(A, n, p);
    double alpha = dot_product(r, r) / dot_product(Ap, p);

    for (int i = 0; i < x.size(); ++i) {
      x[i] += alpha * p[i];
    }

    for (int i = 0; i < r.size(); ++i) {
      r[i] = r_prev[i] - alpha * Ap[i];
    }

    if (dot_product(r, r) < tolerance) {
      break;
    }

    double beta = dot_product(r, r) / dot_product(r_prev, r_prev);
    for (int i = 0; i < p.size(); ++i) {
      p[i] = r[i] + beta * p[i];
    }

    r_prev = r;
  }

  return x;
}

bool ConjugateGradientMethodSequential::pre_processing() {
  internal_order_test();
  // Init value for input and output
  A = std::vector<double> (taskData->inputs_count[0]);
  for (unsigned int i = 0; i < taskData->inputs_count[0]; i++) {
    A[i] = reinterpret_cast<double*>(taskData->inputs[0])[i];
  }
  b = std::vector<double> (taskData->inputs_count[1]);
  for (unsigned int i = 0; i < taskData->inputs_count[1]; i++) {
    b[i] = reinterpret_cast<double*>(taskData->inputs[1])[i];
  }
  size = *reinterpret_cast<int*>(taskData->inputs[2]);
  x = std::vector<double>(size, 0);
  return true;
}

bool ConjugateGradientMethodSequential::validation() {
  internal_order_test();
  // Check count elements of output
  return taskData->inputs_count[0] == taskData->inputs_count[1] * taskData->inputs_count[1] &&
         taskData->inputs_count[1] == taskData->outputs_count[0];
}

bool ConjugateGradientMethodSequential::run() {
  internal_order_test();
  x = conjugate_gradient(A, size, b, 1e-6);
  return true;
}

bool ConjugateGradientMethodSequential::post_processing() {
  internal_order_test();
  for (int i = 0; i < x.size(); i++) {
    reinterpret_cast<double*>(taskData->outputs[0])[i] = x[i];
  }
  return true;
}
