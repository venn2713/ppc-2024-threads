// Copyright 2024 Kriseev Mikhail
#include <gtest/gtest.h>

#include <random>
#include <vector>

#include "core/perf/include/perf.hpp"
#include "seq/kriseev_m_convex_hull_graham/include/kriseev_m_convex_hull_seq.hpp"

TEST(kriseev_m_convex_hull_graham_seq, test_pipeline_run) {
  const int count = 500000;
  // Create data
  std::vector<double> pX;
  std::vector<double> pY;
  std::mt19937 gen(1587443.055);
  std::uniform_real_distribution<> dis(-3.0, 5.0);
  for (int i = 0; i < count; ++i) {
    pX.emplace_back(dis(gen));
    pY.emplace_back(dis(gen));
  }

  std::vector<double> outX(pX.size());
  std::vector<double> outY(pY.size());

  // Create TaskData
  std::shared_ptr<ppc::core::TaskData> data = std::make_shared<ppc::core::TaskData>();
  data->inputs.emplace_back(reinterpret_cast<uint8_t *>(pX.data()));
  data->inputs_count.emplace_back(pX.size());
  data->inputs.emplace_back(reinterpret_cast<uint8_t *>(pY.data()));
  data->inputs_count.emplace_back(pY.size());

  data->outputs.emplace_back(reinterpret_cast<uint8_t *>(outX.data()));
  data->outputs_count.emplace_back(outX.size());
  data->outputs.emplace_back(reinterpret_cast<uint8_t *>(outY.data()));
  data->outputs_count.emplace_back(outY.size());

  // Create Task
  auto sequentialTask = std::make_shared<KriseevMTaskSeq::ConvexHullTask>(data);

  // Create Perf attributes
  auto perfAttr = std::make_shared<ppc::core::PerfAttr>();
  perfAttr->num_running = 10;
  const auto t0 = std::chrono::high_resolution_clock::now();
  perfAttr->current_timer = [&] {
    auto current_time_point = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(current_time_point - t0).count();
    return static_cast<double>(duration) * 1e-9;
  };

  // Create and init perf results
  auto perfResults = std::make_shared<ppc::core::PerfResults>();

  // Create Perf analyzer
  auto perfAnalyzer = std::make_shared<ppc::core::Perf>(sequentialTask);
  perfAnalyzer->pipeline_run(perfAttr, perfResults);
  ppc::core::Perf::print_perf_statistic(perfResults);
}

TEST(kriseev_m_convex_hull_graham_seq, test_task_run) {
  const int count = 500000;
  // Create data
  std::vector<double> pX;
  std::vector<double> pY;
  std::mt19937 gen(1587443.055);
  std::uniform_real_distribution<> dis(-3.0, 5.0);
  for (int i = 0; i < count; ++i) {
    pX.emplace_back(dis(gen));
    pY.emplace_back(dis(gen));
  }

  std::vector<double> outX(pX.size());
  std::vector<double> outY(pY.size());

  // Create TaskData
  std::shared_ptr<ppc::core::TaskData> data = std::make_shared<ppc::core::TaskData>();
  data->inputs.emplace_back(reinterpret_cast<uint8_t *>(pX.data()));
  data->inputs_count.emplace_back(pX.size());
  data->inputs.emplace_back(reinterpret_cast<uint8_t *>(pY.data()));
  data->inputs_count.emplace_back(pY.size());

  data->outputs.emplace_back(reinterpret_cast<uint8_t *>(outX.data()));
  data->outputs_count.emplace_back(outX.size());
  data->outputs.emplace_back(reinterpret_cast<uint8_t *>(outY.data()));
  data->outputs_count.emplace_back(outY.size());

  // Create Task
  auto sequentialTask = std::make_shared<KriseevMTaskSeq::ConvexHullTask>(data);

  // Create Perf attributes
  auto perfAttr = std::make_shared<ppc::core::PerfAttr>();
  perfAttr->num_running = 10;
  const auto t0 = std::chrono::high_resolution_clock::now();
  perfAttr->current_timer = [&] {
    auto current_time_point = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(current_time_point - t0).count();
    return static_cast<double>(duration) * 1e-9;
  };

  // Create and init perf results
  auto perfResults = std::make_shared<ppc::core::PerfResults>();

  // Create Perf analyzer
  auto perfAnalyzer = std::make_shared<ppc::core::Perf>(sequentialTask);
  perfAnalyzer->task_run(perfAttr, perfResults);
  ppc::core::Perf::print_perf_statistic(perfResults);
}
