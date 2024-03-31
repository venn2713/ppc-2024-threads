// Copyright 2024 Lesnikov Nikita
#pragma once

#include <string>
#include <vector>

#include "core/task/include/task.hpp"

class TestTaskSequential : public ppc::core::Task {
 public:
  explicit TestTaskSequential(std::shared_ptr<ppc::core::TaskData> taskData_) : Task(std::move(taskData_)) {}
  bool pre_processing() override;
  bool validation() override;
  bool run() override;
  bool post_processing() override;

  static std::vector<uint8_t> serializeInt32(uint32_t num);
  static deserializeInt32(uint8_t* data);

 private:
  static uint8_t& _get(std::vector<uint8_t>& v, int n, int x, int y);
  static bool _inBounds(int x, int y, int m, int n);
  static bool _notPrev(int x, int y, int prevX, int prevY);
  static bool _markObject(std::vector<uint8_t> v, 
      std::vector<uint8_t>& labelled, 
      std::vector<uint8_t>& checked, int m,
      int n, int x, int y, int prevX,
      int prevY, int label);
  static std::pair<std::vector<uint8_t>, int> _getLabelledImage(
      const std::vector<uint8_t>& v, int m, int n);

 private:
  std::vector<uint8_t> source;
  std::vector<uint8_t> result;
  uint32_t m = 0;
  uint32_t n = 0;
};
