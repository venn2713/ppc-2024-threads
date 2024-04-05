// Copyright 2024 Novostroev Ivan
#include <gtest/gtest.h>

#include <vector>

#include "seq/novostroev_i_int_sort_with_batcher_merge/include/ops_seq.hpp"

TEST(novostroev_i_batcher_merge_seq, Vector20) {
  std::vector<int> vector = randomVector(20);
  std::vector<int> result(vector.size(), 0);
  std::shared_ptr<ppc::core::TaskData> dataSeq = std::make_shared<ppc::core::TaskData>();

  dataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(vector.data()));
  dataSeq->inputs_count.emplace_back(vector.size());
  dataSeq->outputs.emplace_back(reinterpret_cast<uint8_t *>(result.data()));
  dataSeq->outputs_count.emplace_back(result.size());

  BatcherMergeSeq testBatcherMergeSeq(dataSeq);
  ASSERT_EQ(testBatcherMergeSeq.validation(), true);

  testBatcherMergeSeq.preProcessing();
  testBatcherMergeSeq.run();
  testBatcherMergeSeq.postProcessing();

  ASSERT_TRUE(std::is_sorted(result.begin(), result.end()));
}

TEST(novostroev_i_batcher_merge_seq, Vector40) {
  std::vector<int> vector = randomVector(40);
  std::vector<int> result(vector.size(), 0);
  std::shared_ptr<ppc::core::TaskData> dataSeq = std::make_shared<ppc::core::TaskData>();

  dataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(vector.data()));
  dataSeq->inputs_count.emplace_back(vector.size());
  dataSeq->outputs.emplace_back(reinterpret_cast<uint8_t *>(result.data()));
  dataSeq->outputs_count.emplace_back(result.size());

  BatcherMergeSeq testBatcherMergeSeq(dataSeq);

  ASSERT_EQ(testBatcherMergeSeq.validation(), true);

  testBatcherMergeSeq.preProcessing();
  testBatcherMergeSeq.run();
  testBatcherMergeSeq.postProcessing();

  ASSERT_TRUE(std::is_sorted(result.begin(), result.end()));
}

TEST(novostroev_i_batcher_merge_seq, Vector60) {
  std::vector<int> vector = randomVector(60);
  std::vector<int> result(vector.size(), 0);
  std::shared_ptr<ppc::core::TaskData> dataSeq = std::make_shared<ppc::core::TaskData>();

  dataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(vector.data()));
  dataSeq->inputs_count.emplace_back(vector.size());
  dataSeq->outputs.emplace_back(reinterpret_cast<uint8_t *>(result.data()));
  dataSeq->outputs_count.emplace_back(result.size());

  BatcherMergeSeq testBatcherMergeSeq(dataSeq);

  ASSERT_EQ(testBatcherMergeSeq.validation(), true);

  testBatcherMergeSeq.preProcessing();
  testBatcherMergeSeq.run();
  testBatcherMergeSeq.postProcessing();

  ASSERT_TRUE(std::is_sorted(result.begin(), result.end()));
}

TEST(novostroev_i_batcher_merge_seq, Vector80) {
  std::vector<int> vector = randomVector(80);
  std::vector<int> result(vector.size(), 0);
  std::shared_ptr<ppc::core::TaskData> dataSeq = std::make_shared<ppc::core::TaskData>();

  dataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(vector.data()));
  dataSeq->inputs_count.emplace_back(vector.size());
  dataSeq->outputs.emplace_back(reinterpret_cast<uint8_t *>(result.data()));
  dataSeq->outputs_count.emplace_back(result.size());

  BatcherMergeSeq testBatcherMergeSeq(dataSeq);

  ASSERT_EQ(testBatcherMergeSeq.validation(), true);

  testBatcherMergeSeq.preProcessing();
  testBatcherMergeSeq.run();
  testBatcherMergeSeq.postProcessing();

  ASSERT_TRUE(std::is_sorted(result.begin(), result.end()));
}

TEST(novostroev_i_batcher_merge_seq, Vector100) {
  std::vector<int> vector = randomVector(100);
  std::vector<int> result(vector.size(), 0);
  std::shared_ptr<ppc::core::TaskData> dataSeq = std::make_shared<ppc::core::TaskData>();

  dataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(vector.data()));
  dataSeq->inputs_count.emplace_back(vector.size());
  dataSeq->outputs.emplace_back(reinterpret_cast<uint8_t *>(result.data()));
  dataSeq->outputs_count.emplace_back(result.size());

  BatcherMergeSeq testBatcherMergeSeq(dataSeq);

  ASSERT_EQ(testBatcherMergeSeq.validation(), true);

  testBatcherMergeSeq.preProcessing();
  testBatcherMergeSeq.run();
  testBatcherMergeSeq.postProcessing();

  ASSERT_TRUE(std::is_sorted(result.begin(), result.end()));
}
