// Copyright 2024 Lesnikov Nikita
#include "seq/lesnikov_nikita_binary_labelling/include/ops_seq.hpp"

#include <thread>

using namespace std::chrono_literals;

bool TestTaskSequential::pre_processing() {
  internal_order_test();
  try {
    source.resize(taskData->inputs_count[0]);
    memcpy(source.data(), taskData->inputs[0], taskData->inputs_count[0]);
    m = deserializeInt32(taskData->inputs[1]);
    n = deserializeInt32(taskData->inputs[2]);
  } catch (...) {
    return false;
  }

  return true;
}

bool TestTaskSequential::validation() {
  internal_order_test();

  return taskData->inputs_count.size() == 3 
      && taskData->outputs_count.size() == 2
      && taskData->inputs_count[1] == 4 
      && taskData->inputs_count[2] == 4;
}

bool TestTaskSequential::run() {
  internal_order_test();

  auto res = _getLabelledImage(source, m, n);
  
  return true;
}

bool TestTaskSequential::post_processing() {
  internal_order_test();

  try {
    taskData->outputs[0] = new uint8_t[result.size()];
    memcpy(taskData->outputs[0], result.data(), result.size());
  } catch (...) {
    return false;
  }
 
  return true;
}

std::vector<uint8_t> TestTaskSequential::serializeInt32(uint32_t num) { 
  std::vector<uint8_t> result;
  for (int i = 3; i >= 0; i--) {
    result.push_back(static_cast<uint8_t>(((num << (3 - i)) >> (3 - i)) >> i));
  }
  return result;
}

uint32_t TestTaskSequential::deserializeInt32(uint8_t* data) {
  uint32_t res;
  for (int i = 3; i >= 0; i--) {
    res += static_cast<uint32_t>(data[i]) << i * 8;
  }
}

uint8_t& TestTaskSequential::_get(std::vector<uint8_t>& v, int n, int x, int y) { return v[x * n + y]; }

bool TestTaskSequential::_inBounds(int x, int y, int m, int n) { return x >= 0 && x < m && y >= 0 && y < n; }

bool TestTaskSequential::_notPrev(int x, int y, int prevX, int prevY) { return x != prevX && y != prevY; }

bool TestTaskSequential::_markObject(std::vector<uint8_t> v, std::vector<uint8_t>& labelled, 
    std::vector<uint8_t>& checked, int m, int n,
    int x, int y, int prevX, int prevY, int label) {
  if (_get(checked, n, x, y)) {
    return false;
  }
  _get(checked, n, x, y) = 1;

  if (_get(v, n, x, y)) {
    _get(labelled, n, x, y) = label;
  } else {
    return false;
  }

  if (_inBounds(x - 1, y, m, n) && _notPrev(x - 1, y, prevX, prevY)) {
    _markObject(v, labelled, checked, m, n, x - 1, y, x, y, label);
  }
  if (_inBounds(x + 1, y, m, n) && _notPrev(x + 1, y, prevX, prevY)) {
    _markObject(v, labelled, checked, m, n, x + 1, y, x, y, label);
  }
  if (_inBounds(x, y - 1, m, n) && _notPrev(x, y - 1, prevX, prevY)) {
    _markObject(v, labelled, checked, m, n, x, y - 1, x, y, label);
  }
  if (_inBounds(x, y + 1, m, n) && _notPrev(x, y + 1, prevX, prevY)) {
    _markObject(v, labelled, checked, m, n, x, y + 1, x, y, label);
  }

  return true;
}

std::pair<std::vector<uint8_t>, int> TestTaskSequential::_getLabelledImage(const std::vector<uint8_t>& v, int m,
                                                                           int n) {
  std::vector<uint8_t> labelled(v.size());
  std::vector<uint8_t> checked(v.size());
  int label = 1;

  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      if (!_get(labelled, n, i, j)) {
        label += static_cast<int>(_markObject(v, labelled, checked, m, n, i, j, -1, -1, label));
      }
    }
  }

  return std::make_pair(labelled, label);
}