// Copyright 2024 Petrov Maksim
#include <gtest/gtest.h>

#include <vector>

#include "seq/petrov_m_radix_sort_double_simple_merging/include/ops_seq.hpp"

TEST(Petrov_M_Radix_Sort_Sequential, Test_With_Positive_Numbers) {
  // Create data
  std::vector<double> in{2.5, 3.22, 5.32, 1.11};
  std::vector<double> sorted{1.11, 2.5, 3.22, 5.32 };
  std::vector<double> out(in.size());

  // Create TaskData
  std::shared_ptr<ppc::core::TaskData> taskDataSeq = std::make_shared<ppc::core::TaskData>(); 
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(in.data()));
  taskDataSeq->inputs_count.emplace_back(in.size());
  taskDataSeq->outputs.emplace_back(reinterpret_cast<uint8_t *>(out.data()));
  taskDataSeq->outputs_count.emplace_back(out.size());

  // Create Task
  RadixSortDoubleSequential testTaskSequential(taskDataSeq);
  ASSERT_EQ(testTaskSequential.validation(), true);
  testTaskSequential.pre_processing();
  testTaskSequential.run();
  testTaskSequential.post_processing();
 for (int i = 0; i < out.size(); i++) {
    ASSERT_EQ(sorted[i], out[i]);
  }
}

TEST(Petrov_M_Radix_Sort_Sequential, Test_With_Negative_Numbers) {

  // Create data
  std::vector<double> in{-2.5, -3.22, -5.32, -1.11};
  std::vector<double> sorted{-5.32, -3.22,-2.5,-1.11};
  std::vector<double> out(in.size());

  // Create TaskData
  std::shared_ptr<ppc::core::TaskData> taskDataSeq = std::make_shared<ppc::core::TaskData>(); 
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(in.data()));
  taskDataSeq->inputs_count.emplace_back(in.size());
  taskDataSeq->outputs.emplace_back(reinterpret_cast<uint8_t *>(out.data()));
  taskDataSeq->outputs_count.emplace_back(out.size());

  // Create Task
  RadixSortDoubleSequential testTaskSequential(taskDataSeq);
  ASSERT_EQ(testTaskSequential.validation(), true);
  testTaskSequential.pre_processing();
  testTaskSequential.run();
  testTaskSequential.post_processing();
 for (int i = 0; i < out.size(); i++) {
    ASSERT_EQ(sorted[i], out[i]);
  }
}

TEST(Petrov_M_Radix_Sort_Sequential, Test_With_Positive_and_Negative_Numbers) {
  // Create data
  std::vector<double> in{2.5, -3.22, 5.32, -1.11};
  std::vector<double> sorted{-3.22, -1.11, 2.5, 5.32 };
  std::vector<double> out(in.size());

  // Create TaskData
  std::shared_ptr<ppc::core::TaskData> taskDataSeq = std::make_shared<ppc::core::TaskData>(); 
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(in.data()));
  taskDataSeq->inputs_count.emplace_back(in.size());
  taskDataSeq->outputs.emplace_back(reinterpret_cast<uint8_t *>(out.data()));
  taskDataSeq->outputs_count.emplace_back(out.size());

  // Create Task
  RadixSortDoubleSequential testTaskSequential(taskDataSeq);
  ASSERT_EQ(testTaskSequential.validation(), true);
  testTaskSequential.pre_processing();
  testTaskSequential.run();
  testTaskSequential.post_processing();
 for (int i = 0; i < out.size(); i++) {
    ASSERT_EQ(sorted[i], out[i]);
  }
}

TEST(Petrov_M_Radix_Sort_Sequential, Test_With_Positive_Numbers2) {

  // Create data
  std::vector<double> in{2.55, 3.223, 5.323, 1.116, 2.56, 3.222, 5.322, 1.115};
  std::vector<double> sorted{1.115,1.116, 2.55,2.56, 3.222,3.223, 5.322,5.323 };
  std::vector<double> out(in.size());

  // Create TaskData
  std::shared_ptr<ppc::core::TaskData> taskDataSeq = std::make_shared<ppc::core::TaskData>();
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(in.data()));
  taskDataSeq->inputs_count.emplace_back(in.size());
  taskDataSeq->outputs.emplace_back(reinterpret_cast<uint8_t *>(out.data()));
  taskDataSeq->outputs_count.emplace_back(out.size());

  // Create Task
  RadixSortDoubleSequential testTaskSequential(taskDataSeq);
  ASSERT_EQ(testTaskSequential.validation(), true);
  testTaskSequential.pre_processing();
  testTaskSequential.run();
  testTaskSequential.post_processing();
 for (int i = 0; i < out.size(); i++) {
    ASSERT_EQ(sorted[i], out[i]);
  }
}

TEST(Petrov_M_Radix_Sort_Sequential, Test_With_Negative_Numbers2) {

  // Create data
  std::vector<double> in{-1.1, -2.2, -3.3, -4.4, -5.5, -6.6, -7.7, -8.8, -9.9, -10.0};
  std::vector<double> sorted{-10.0,-9.9, -8.8, -7.7, -6.6, -5.5, -4.4, -3.3, -2.2, -1.1};
  std::vector<double> out(in.size());

  // Create TaskData
  std::shared_ptr<ppc::core::TaskData> taskDataSeq = std::make_shared<ppc::core::TaskData>(); 
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(in.data()));
  taskDataSeq->inputs_count.emplace_back(in.size());
  taskDataSeq->outputs.emplace_back(reinterpret_cast<uint8_t *>(out.data()));
  taskDataSeq->outputs_count.emplace_back(out.size());

  // Create Task
  RadixSortDoubleSequential testTaskSequential(taskDataSeq);
  ASSERT_EQ(testTaskSequential.validation(), true);
  testTaskSequential.pre_processing();
  testTaskSequential.run();
  testTaskSequential.post_processing();
 for (int i = 0; i < out.size(); i++) {
    ASSERT_EQ(sorted[i], out[i]);
  }
}
