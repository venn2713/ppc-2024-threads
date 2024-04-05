// Copyright 2024 Novostroev Ivan
#include <gtest/gtest.h>

#include <chrono>
#include <thread>
#include <vector>

#include "core/perf/include/perf.hpp"
#include "seq/novostroev_i_int_sort_with_batcher_merge/include/ops_seq.hpp"

TEST(novostroev_i_batcher_merge_seq_perf_test, test_pipeline_run) {
  std::vector<int> vector = randomVector(1000);
  std::vector<int> result(vector.size(), 0);
  std::shared_ptr<ppc::core::TaskData> dataSeq = std::make_shared<ppc::core::TaskData>();

  dataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(vector.data()));
  dataSeq->inputs_count.emplace_back(vector.size());
  dataSeq->outputs.emplace_back(reinterpret_cast<uint8_t *>(result.data()));
  dataSeq->outputs_count.emplace_back(result.size());

  auto testBatcherMergeSeq = std::make_shared<BatcherMergeSeq>(dataSeq);
  auto attr = std::make_shared<ppc::core::attr>();

  attr->num_running = 10;

  const auto t0 = std::chrono::high_resultolution_clock::now();
  
  attr->current_timer = [&] {
    auto current_time_point = std::chrono::high_resultolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(current_time_point - t0).count();
    return static_cast<double>(duration) * 1e-9;
  };

  auto perfresultults = std::make_shared<ppc::core::Perfresultults>();
  auto perfAnalyzer = std::make_shared<ppc::core::Perf>(testBatcherMergeSeq);

  perfAnalyzer->pipeline_run(attr, perfresultults);

  ppc::core::Perf::print_perf_statistic(perfresultults);

  ASSERT_TRUE(std::is_sorted(result.begin(), result.end()));
}

TEST(novostroev_i_batcher_merge_seq_perf_test, test_task_run) {
  std::vector<int> vector = randomVector(1000);
  std::vector<int> result(vector.size(), 0);
  std::shared_ptr<ppc::core::TaskData> dataSeq = std::make_shared<ppc::core::TaskData>();

  dataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(vector.data()));
  dataSeq->inputs_count.emplace_back(vector.size());
  dataSeq->outputs.emplace_back(reinterpret_cast<uint8_t *>(result.data()));
  dataSeq->outputs_count.emplace_back(result.size());

  auto testBatcherMergeSeq = std::make_shared<BatcherMergeSeq>(dataSeq);

  auto attr = std::make_shared<ppc::core::attr>();

  attr->num_running = 10;

  const auto t0 = std::chrono::high_resultolution_clock::now();

  attr->current_timer = [&] {
    auto current_time_point = std::chrono::high_resultolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(current_time_point - t0).count();
    return static_cast<double>(duration) * 1e-9;
  };

  auto perfresultults = std::make_shared<ppc::core::Perfresultults>();
  auto perfAnalyzer = std::make_shared<ppc::core::Perf>(testBatcherMergeSeq);

  perfAnalyzer->task_run(attr, perfresultults);

  ppc::core::Perf::print_perf_statistic(perfresultults);

  ASSERT_TRUE(std::is_sorted(result.begin(), result.end()));
}
