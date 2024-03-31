// Copyright 2024 Zawadowski Jan

#include "core/perf/include/perf.hpp"
#include "seq/zawadowski_j_linear_filtering_block/include/linear_filtering_block.hpp"

TEST(zawadowski_j_linear_filtering_block, test_pipeline_run) {
    // Create data
    uint16_t width = 999,
             height = 999;
    std::vector<uint8_t> image(width * height),
                         result(width * height),
                         sample(width * height);

    // Create TaskData
    std::shared_ptr<ppc::core::TaskData> taskDataSeq =
        std::make_shared<ppc::core::TaskData>();
    taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t*>(image.data()));
    taskDataSeq->inputs_count.emplace_back(width);
    taskDataSeq->inputs_count.emplace_back(height);
    taskDataSeq->outputs.
        emplace_back(reinterpret_cast<uint8_t*>(result.data()));
    taskDataSeq->outputs_count.emplace_back(width);
    taskDataSeq->outputs_count.emplace_back(height);

    // Create Task
    std::shared_ptr<LinearFiltering> testTaskSequential =
        std::make_shared<LinearFiltering>(taskDataSeq);

    // Create Perf attributes
    std::shared_ptr<ppc::core::PerfAttr> perfAttr =
        std::make_shared<ppc::core::PerfAttr>();
    perfAttr->num_running = 10;
    const std::chrono::steady_clock::time_point t0 =
        std::chrono::high_resolution_clock::now();
    perfAttr->current_timer = [&] {
        std::chrono::steady_clock::time_point current_time_point =
            std::chrono::high_resolution_clock::now();
        int64_t duration = std::chrono::duration_cast<std::chrono::nanoseconds>
            (current_time_point - t0).count();
        return static_cast<double>(duration) * 1e-9;
    };

    // Create and init perf results
    std::shared_ptr<ppc::core::PerfResults> perfResults =
        std::make_shared<ppc::core::PerfResults>();

    // Create Perf analyzer
    std::shared_ptr<ppc::core::Perf> perfAnalyzer =
        std::make_shared<ppc::core::Perf>(testTaskSequential);
    perfAnalyzer->pipeline_run(perfAttr, perfResults);
    ppc::core::Perf::print_perf_statistic(perfResults);
    ASSERT_EQ(result, sample);
}

TEST(zawadowski_j_linear_filtering_block, test_task_run) {
    // Create data
    uint16_t width = 999,
             height = 999;
    std::vector<uint8_t> image(width * height),
                         result(width * height),
                         sample(width * height);

    // Create TaskData
    std::shared_ptr<ppc::core::TaskData> taskDataSeq =
        std::make_shared<ppc::core::TaskData>();
    taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t*>(image.data()));
    taskDataSeq->inputs_count.emplace_back(width);
    taskDataSeq->inputs_count.emplace_back(height);
    taskDataSeq->outputs.
        emplace_back(reinterpret_cast<uint8_t*>(result.data()));
    taskDataSeq->outputs_count.emplace_back(width);
    taskDataSeq->outputs_count.emplace_back(height);

    // Create Task
    std::shared_ptr<LinearFiltering> testTaskSequential =
        std::make_shared<LinearFiltering>(taskDataSeq);

    // Create Perf attributes
    std::shared_ptr<ppc::core::PerfAttr> perfAttr =
        std::make_shared<ppc::core::PerfAttr>();
    perfAttr->num_running = 10;
    const std::chrono::steady_clock::time_point t0 =
        std::chrono::high_resolution_clock::now();
    perfAttr->current_timer = [&] {
        std::chrono::steady_clock::time_point current_time_point =
            std::chrono::high_resolution_clock::now();
        int64_t duration = std::chrono::duration_cast<std::chrono::nanoseconds>
            (current_time_point - t0).count();
        return static_cast<double>(duration) * 1e-9;
    };

    // Create and init perf results
    std::shared_ptr<ppc::core::PerfResults> perfResults =
        std::make_shared<ppc::core::PerfResults>();

    // Create Perf analyzer
    std::shared_ptr<ppc::core::Perf> perfAnalyzer =
        std::make_shared<ppc::core::Perf>(testTaskSequential);
    perfAnalyzer->task_run(perfAttr, perfResults);
    ppc::core::Perf::print_perf_statistic(perfResults);
    ASSERT_EQ(result, sample);
}
