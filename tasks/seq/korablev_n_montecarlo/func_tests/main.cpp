// Copyright 2023 Korablev Nikita
#include <gtest/gtest.h>

#include <vector>

#include "seq/korablev_n_montecarlo/include/ops_seq.hpp"
#define ESTIMATE 0.01

TEST(SeqMC, Test_sin) {
  double res = 8;

  // Create data
  std::vector<double> in1 = {0, 2};
  std::vector<double> in2 = {0, 2, 3};
  std::vector<double> out(1, res);

  // Create TaskData
  std::shared_ptr<ppc::core::TaskData> taskDataSeq = std::make_shared<ppc::core::TaskData>();
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(in1.data()));
  taskDataSeq->inputs_count.emplace_back(in1.size());
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(in2.data()));
  taskDataSeq->inputs_count.emplace_back(in2.size());

  taskDataSeq->outputs.emplace_back(reinterpret_cast<uint8_t *>(out.data()));
  taskDataSeq->outputs_count.emplace_back(out.size());

  // Create Task
  MonteCarloSequential testTaskSequential(taskDataSeq);
  ASSERT_EQ(testTaskSequential.validation(), true);
  testTaskSequential.pre_processing();
  testTaskSequential.run();
  testTaskSequential.post_processing();
  ASSERT_LT(std::abs(res - out[0]), ESTIMATE);
}
//
//TEST(Sequential, Test_cos) {
//  // Create data
//  std::vector<double> in = {-10, -1.5, 1};
//  std::vector<double> out(1, -1.54152);
//
//  // Create TaskData
//  std::shared_ptr<ppc::core::TaskData> taskDataSeq = std::make_shared<ppc::core::TaskData>();
//  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(in.data()));
//  taskDataSeq->inputs_count.emplace_back(in.size());
//  taskDataSeq->outputs.emplace_back(reinterpret_cast<uint8_t *>(out.data()));
//  taskDataSeq->outputs_count.emplace_back(out.size());
//
//  // Create Task
//  MonteCarloSequential testTaskSequential(taskDataSeq);
//  ASSERT_EQ(testTaskSequential.validation(), true);
//  testTaskSequential.pre_processing();
//  testTaskSequential.run();
//  testTaskSequential.post_processing();
//  ASSERT_LT(out[0], ESTIMATE);
//}
//
//TEST(Sequential, Test_two_sc) {
//  // Create data
//  std::vector<double> in = {-3, 4, 2};
//  std::vector<double> out(1, 0.552835);
//
//  // Create TaskData
//  std::shared_ptr<ppc::core::TaskData> taskDataSeq = std::make_shared<ppc::core::TaskData>();
//  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(in.data()));
//  taskDataSeq->inputs_count.emplace_back(in.size());
//  taskDataSeq->outputs.emplace_back(reinterpret_cast<uint8_t *>(out.data()));
//  taskDataSeq->outputs_count.emplace_back(out.size());
//
//  // Create Task
//  MonteCarloSequential testTaskSequential(taskDataSeq);
//  ASSERT_EQ(testTaskSequential.validation(), true);
//  testTaskSequential.pre_processing();
//  testTaskSequential.run();
//  testTaskSequential.post_processing();
//  ASSERT_LT(out[0], ESTIMATE);
//}