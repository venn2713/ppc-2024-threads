// Copyright 2024 Novostroev Ivan

#include "seq/novostroev_i_int_sort_with_batcher_merge/include/ops_seq.hpp"

using namespace std::chrono_literals;

void fillMissing(std::vector<int> &result, std::vector<int> part1, std::vector<int> part2, size_t i, size_t j,
                 size_t k) {
  if (j >= part1.size()) {
    for (size_t l = k; l < part2.size(); l += 2) {
      result[i] = part2[l];
      i++;
    }
  } else {
    for (size_t l = j; l < part1.size(); l += 2) {
      result[i] = part1[l];
      i++;
    }
  }
}

void fillResult(std::vector<int> &result, std::vector<int> part1, std::vector<int> part2, size_t &i, size_t &j,
                size_t &k) {
  for (i = 0; (j < part1.size()) && (k < part2.size()); i++) {
    if (part1[j] <= part2[k]) {
      result[i] = part1[j];
      j += 2;
    } else {
      result[i] = part2[k];
      k += 2;
    }
  }
}

std::vector<int> merge(std::vector<int> vectorFirst, std::vector<int> vectorSecond) {
  std::vector<int> result(vectorFirst.size() + vectorSecond.size());
  size_t i = 0, j = 0, k = 0;

  for (i = 0, j = 0, k = 0; (j < vectorFirst.size()) && (k < vectorSecond.size()); i += 2, j++, k++) {
    result[i] = vectorFirst[j];
    result[i + 1] = vectorSecond[k];
  }

  for (i = 0; i < result.size() - 1; i++) {
    if (result[i] > result[i + 1]) {
      std::swap(result[i], result[i + 1]);
    }
  }

  return result;
}

std::vector<int> even(const std::vector<int> &part1, const std::vector<int> &part2) {
  std::vector<int> result(part1.size() / 2 + part2.size() / 2 + part1.size() % 2 + part2.size() % 2);
  size_t i = 0, j = 0, k = 0;

  fillResult(result, part1, part2, i, j, k);
  fillMissing(result, part1, part2, i, j, k);

  return result;
}

std::vector<int> odd(const std::vector<int> &part1, const std::vector<int> &part2) {
  std::vector<int> result(part1.size() / 2 + part2.size() / 2);
  size_t i = 0, j = 1, k = 1;

  fillResult(result, part1, part2, i, j, k);
  fillMissing(result, part1, part2, i, j, k);

  return result;
}

std::vector<int> batcherSort(const std::vector<int> &part1, const std::vector<int> &part2) {
  std::vector<int> evenVector = even(part1, part2);
  std::vector<int> oddVector = odd(part1, part2);

  return merge(evenVector, oddVector);
}

bool BatcherMergeSeq::run() {
  internal_order_test();
  result = batcherSort(part1, part2);
  std::this_thread::sleep_for(20ms);
  return true;
}

bool BatcherMergeSeq::validation() {
  internal_order_test();
  return std::is_sorted(part1.begin(), part1.end()) && std::is_sorted(part2.begin(), part2.end());
}

bool BatcherMergeSeq::preProcessing() {
  internal_order_test();
  vector = std::vector<int>(taskData->inputs_count[0]);

  auto *tmp_ptr_A = reinterpret_cast<int *>(taskData->inputs[0]);
  for (unsigned i = 0; i < taskData->inputs_count[0]; i++) {
    vector[i] = tmp_ptr_A[i];
  }

  part1.resize(vector.size() / 2);
  part2.resize(vector.size() / 2);

  for (size_t i = 0; i < (vector.size() / 2); i++) {
    part1[i] = vector[i];
    part2[i] = vector[(vector.size() / 2) + i];
  }

  std::sort(part1.begin(), part1.end());
  std::sort(part2.begin(), part2.end());

  return true;
}

bool BatcherMergeSeq::postProcessing() {
  internal_order_test();
  std::copy(result.begin(), result.end(), reinterpret_cast<int *>(taskData->outputs[0]));
  return true;
}
