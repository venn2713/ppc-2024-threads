// Copyright 2024 Vetoshnikova Ekaterina
#include <gtest/gtest.h>

#include <vector>

#include "seq/vetoshnikova_k_convex_hull_bin_image_components/include/ops_seq.hpp"

TEST(vetoshnikova_k_hull_bin_image_seq, Test1) {
  int w = 5;
  int h = 5;

  // Create data
  std::vector<int> out(50);
  std::vector<std::vector<int>> in(
      {{0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 1, 1, 0, 0}, {0, 1, 1, 0, 0}, {0, 0, 0, 0, 0}});

  std::vector<int> hullTrue = {1, 2, 2, 2, 2, 3, 1, 3, -1};

  // Create TaskData
  std::shared_ptr<ppc::core::TaskData> taskDataSeq = std::make_shared<ppc::core::TaskData>();
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t*>(&in));
  taskDataSeq->inputs_count.emplace_back(w);
  taskDataSeq->inputs_count.emplace_back(h);
  taskDataSeq->outputs.emplace_back(reinterpret_cast<uint8_t*>(out.data()));

  // Create Task
  TaskSequential testTaskSequential(taskDataSeq);
  ASSERT_EQ(testTaskSequential.validation(), true);
  testTaskSequential.pre_processing();
  testTaskSequential.run();
  testTaskSequential.post_processing();
  for (size_t i = 0; i < hullTrue.size(); i++) {
    ASSERT_EQ(hullTrue[i], out[i]);
  }
}

TEST(vetoshnikova_k_hull_bin_image_seq, Test2) {
  int w = 7;
  int h = 7;

  // Create data
  std::vector<int> out(50);
  std::vector<std::vector<int>> in({{0, 0, 0, 0, 0, 0, 0},
                                    {0, 1, 1, 0, 0, 0, 0},
                                    {0, 1, 1, 0, 0, 0, 0},
                                    {0, 0, 1, 0, 0, 0, 0},
                                    {0, 0, 0, 0, 0, 0, 0},
                                    {0, 0, 0, 0, 0, 0, 0},
                                    {0, 0, 0, 0, 0, 0, 0}});

  std::vector<int> hullTrue = {1, 1, 2, 1, 2, 3, 1, 2, -1};

  // Create TaskData
  std::shared_ptr<ppc::core::TaskData> taskDataSeq = std::make_shared<ppc::core::TaskData>();
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t*>(&in));
  taskDataSeq->inputs_count.emplace_back(w);
  taskDataSeq->inputs_count.emplace_back(h);
  taskDataSeq->outputs.emplace_back(reinterpret_cast<uint8_t*>(out.data()));

  // Create Task
  TaskSequential testTaskSequential(taskDataSeq);
  ASSERT_EQ(testTaskSequential.validation(), true);
  testTaskSequential.pre_processing();
  testTaskSequential.run();
  testTaskSequential.post_processing();
  for (size_t i = 0; i < hullTrue.size(); i++) {
    ASSERT_EQ(hullTrue[i], out[i]);
  }
}

TEST(vetoshnikova_k_hull_bin_image_seq, Test3) {
  int w = 7;
  int h = 6;

  // Create data
  std::vector<int> out(50);
  std::vector<std::vector<int>> in({{0, 0, 1, 0, 0, 0, 0},
                                    {0, 0, 1, 1, 0, 0, 0},
                                    {0, 0, 1, 0, 0, 0, 0},
                                    {0, 0, 0, 0, 0, 0, 0},
                                    {0, 0, 0, 0, 0, 1, 1},
                                    {0, 0, 0, 0, 0, 1, 1}});

  std::vector<int> hullTrue = {2, 0, 3, 1, 2, 2, -1, 5, 4, 6, 4, 6, 5, 5, 5, -1};

  // Create TaskData
  std::shared_ptr<ppc::core::TaskData> taskDataSeq = std::make_shared<ppc::core::TaskData>();
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t*>(&in));
  taskDataSeq->inputs_count.emplace_back(w);
  taskDataSeq->inputs_count.emplace_back(h);
  taskDataSeq->outputs.emplace_back(reinterpret_cast<uint8_t*>(out.data()));

  // Create Task
  TaskSequential testTaskSequential(taskDataSeq);
  ASSERT_EQ(testTaskSequential.validation(), true);
  testTaskSequential.pre_processing();
  testTaskSequential.run();
  testTaskSequential.post_processing();
  for (size_t i = 0; i < hullTrue.size(); i++) {
    ASSERT_EQ(hullTrue[i], out[i]);
  }
}
TEST(vetoshnikova_k_hull_bin_image_seq, Test4) {
  int w = 7;
  int h = 7;

  // Create data
  std::vector<int> out(50);
  std::vector<std::vector<int>> in({{0, 0, 0, 0, 0, 0, 0},
                                    {0, 0, 0, 1, 0, 0, 0},
                                    {0, 0, 0, 0, 1, 0, 0},
                                    {0, 0, 0, 0, 0, 1, 0},
                                    {0, 0, 0, 0, 1, 0, 0},
                                    {0, 0, 0, 1, 0, 0, 0},
                                    {0, 0, 0, 0, 0, 0, 0}});

  std::vector<int> hullTrue = {3, 1, 5, 3, 3, 5, -1};

  // Create TaskData
  std::shared_ptr<ppc::core::TaskData> taskDataSeq = std::make_shared<ppc::core::TaskData>();
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t*>(&in));
  taskDataSeq->inputs_count.emplace_back(w);
  taskDataSeq->inputs_count.emplace_back(h);
  taskDataSeq->outputs.emplace_back(reinterpret_cast<uint8_t*>(out.data()));

  // Create Task
  TaskSequential testTaskSequential(taskDataSeq);
  ASSERT_EQ(testTaskSequential.validation(), true);
  testTaskSequential.pre_processing();
  testTaskSequential.run();
  testTaskSequential.post_processing();
  for (size_t i = 0; i < hullTrue.size(); i++) {
    ASSERT_EQ(hullTrue[i], out[i]);
  }
}

TEST(vetoshnikova_k_hull_bin_image_seq, Test5) {
  int w = 5;
  int h = 8;

  // Create data
  std::vector<int> out(50);
  std::vector<std::vector<int>> in({{0, 0, 0, 0, 0},
                                    {0, 0, 0, 1, 0},
                                    {0, 0, 1, 1, 1},
                                    {0, 0, 0, 0, 0},
                                    {0, 0, 0, 0, 0},
                                    {0, 0, 0, 0, 0},
                                    {1, 1, 0, 0, 0},
                                    {1, 1, 0, 0, 0}});

  std::vector<int> hullTrue = {2, 2, 3, 1, 4, 2, -1, 0, 6, 1, 6, 1, 7, 0, 7, -1};

  // Create TaskData
  std::shared_ptr<ppc::core::TaskData> taskDataSeq = std::make_shared<ppc::core::TaskData>();
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t*>(&in));
  taskDataSeq->inputs_count.emplace_back(w);
  taskDataSeq->inputs_count.emplace_back(h);
  taskDataSeq->outputs.emplace_back(reinterpret_cast<uint8_t*>(out.data()));

  // Create Task
  TaskSequential testTaskSequential(taskDataSeq);
  ASSERT_EQ(testTaskSequential.validation(), true);
  testTaskSequential.pre_processing();
  testTaskSequential.run();
  testTaskSequential.post_processing();
  for (size_t i = 0; i < hullTrue.size(); i++) {
    ASSERT_EQ(hullTrue[i], out[i]);
  }
}
