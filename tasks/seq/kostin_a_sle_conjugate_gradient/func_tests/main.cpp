// Copyright 2024 Kostin Artem
#include <gtest/gtest.h>

#include <vector>

#include "seq/kostin_a_sle_conjugate_gradient/include/ops_seq.hpp"

TEST(ConjugateGradientMethodSequential, Test_SLE_size_2) {
  int size = 2;

  // Create data
  std::vector<double> in_A = {2.0, 1.0, 1.0, 2.0};
  std::vector<double> in_b = {1.0, 3.0};
  std::vector<double> out(size, 0.0);
  std::vector<double> correct_answer = {-0.33333, 1.66666};

  // Create TaskData
  std::shared_ptr<ppc::core::TaskData> taskDataSeq = std::make_shared<ppc::core::TaskData>();
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(in_A.data()));
  taskDataSeq->inputs_count.emplace_back(in_A.size());
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(in_b.data()));
  taskDataSeq->inputs_count.emplace_back(in_b.size());
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(&size));
  taskDataSeq->outputs.emplace_back(reinterpret_cast<uint8_t *>(out.data()));
  taskDataSeq->outputs_count.emplace_back(out.size());

  // Create Task
  ConjugateGradientMethodSequential testTaskSequential(taskDataSeq);
  ASSERT_EQ(testTaskSequential.validation(), true);
  testTaskSequential.pre_processing();
  testTaskSequential.run();
  testTaskSequential.post_processing();
  for (int i = 0; i < out.size(); i++) {
    ASSERT_LE(correct_answer[i] - out[i], 0.0001);
  }
}

TEST(ConjugateGradientMethodSequential, Test_SLE_size_3) {
  int size = 2;

  // Create data
  std::vector<double> in_A = {2.0, 1.0, 1.0, 2.0};
  std::vector<double> in_b = {1.0, 3.0};
  std::vector<double> out(size, 0.0);
  std::vector<double> correct_answer = {-0.33333, 1.66666};

  // Create TaskData
  std::shared_ptr<ppc::core::TaskData> taskDataSeq = std::make_shared<ppc::core::TaskData>();
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(in_A.data()));
  taskDataSeq->inputs_count.emplace_back(in_A.size());
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(in_b.data()));
  taskDataSeq->inputs_count.emplace_back(in_b.size());
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(&size));
  taskDataSeq->outputs.emplace_back(reinterpret_cast<uint8_t *>(out.data()));
  taskDataSeq->outputs_count.emplace_back(out.size());

  // Create Task
  ConjugateGradientMethodSequential testTaskSequential(taskDataSeq);
  ASSERT_EQ(testTaskSequential.validation(), true);
  testTaskSequential.pre_processing();
  testTaskSequential.run();
  testTaskSequential.post_processing();
  for (int i = 0; i < out.size(); i++) {
    ASSERT_LE(correct_answer[i] - out[i], 0.0001);
  }
}

TEST(ConjugateGradientMethodSequential, Test_SLE_size_4) {
  int size = 2;

  // Create data
  std::vector<double> in_A = {2.0, 1.0, 1.0, 2.0};
  std::vector<double> in_b = {1.0, 3.0};
  std::vector<double> out(size, 0.0);
  std::vector<double> correct_answer = {-0.33333, 1.66666};

  // Create TaskData
  std::shared_ptr<ppc::core::TaskData> taskDataSeq = std::make_shared<ppc::core::TaskData>();
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(in_A.data()));
  taskDataSeq->inputs_count.emplace_back(in_A.size());
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(in_b.data()));
  taskDataSeq->inputs_count.emplace_back(in_b.size());
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(&size));
  taskDataSeq->outputs.emplace_back(reinterpret_cast<uint8_t *>(out.data()));
  taskDataSeq->outputs_count.emplace_back(out.size());

  // Create Task
  ConjugateGradientMethodSequential testTaskSequential(taskDataSeq);
  ASSERT_EQ(testTaskSequential.validation(), true);
  testTaskSequential.pre_processing();
  testTaskSequential.run();
  testTaskSequential.post_processing();
  for (int i = 0; i < out.size(); i++) {
    ASSERT_LE(correct_answer[i] - out[i], 0.0001);
  }
}

TEST(ConjugateGradientMethodSequential, Test_SLE_size_5) {
  int size = 2;

  // Create data
  std::vector<double> in_A = {2.0, 1.0, 1.0, 2.0};
  std::vector<double> in_b = {1.0, 3.0};
  std::vector<double> out(size, 0.0);
  std::vector<double> correct_answer = {-0.33333, 1.66666};

  // Create TaskData
  std::shared_ptr<ppc::core::TaskData> taskDataSeq = std::make_shared<ppc::core::TaskData>();
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(in_A.data()));
  taskDataSeq->inputs_count.emplace_back(in_A.size());
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(in_b.data()));
  taskDataSeq->inputs_count.emplace_back(in_b.size());
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(&size));
  taskDataSeq->outputs.emplace_back(reinterpret_cast<uint8_t *>(out.data()));
  taskDataSeq->outputs_count.emplace_back(out.size());

  // Create Task
  ConjugateGradientMethodSequential testTaskSequential(taskDataSeq);
  ASSERT_EQ(testTaskSequential.validation(), true);
  testTaskSequential.pre_processing();
  testTaskSequential.run();
  testTaskSequential.post_processing();
  for (int i = 0; i < out.size(); i++) {
    ASSERT_LE(correct_answer[i] - out[i], 0.0001);
  }
}

TEST(ConjugateGradientMethodSequential, Test_SLE_size_6) {
  int size = 2;

  // Create data
  std::vector<double> in_A = {2.0, 1.0, 1.0, 2.0};
  std::vector<double> in_b = {1.0, 3.0};
  std::vector<double> out(size, 0.0);
  std::vector<double> correct_answer = {-0.33333, 1.66666};

  // Create TaskData
  std::shared_ptr<ppc::core::TaskData> taskDataSeq = std::make_shared<ppc::core::TaskData>();
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(in_A.data()));
  taskDataSeq->inputs_count.emplace_back(in_A.size());
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(in_b.data()));
  taskDataSeq->inputs_count.emplace_back(in_b.size());
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(&size));
  taskDataSeq->outputs.emplace_back(reinterpret_cast<uint8_t *>(out.data()));
  taskDataSeq->outputs_count.emplace_back(out.size());

  // Create Task
  ConjugateGradientMethodSequential testTaskSequential(taskDataSeq);
  ASSERT_EQ(testTaskSequential.validation(), true);
  testTaskSequential.pre_processing();
  testTaskSequential.run();
  testTaskSequential.post_processing();
  for (int i = 0; i < out.size(); i++) {
    ASSERT_LE(correct_answer[i] - out[i], 0.0001);
  }
}
