// Copyright 2023 Simonyan Suren
#include <gtest/gtest.h>

#include <vector>

#include "seq/example/include/ops_seq.hpp"

TEST(Sequential, Test_Sum_10) {

  // Create data
  std::vector<double> in1{5,0,0,0,
                          0,0,5,0,
                          0,1,0,0,
                          8,0,6,0};

  std::vector<double> in2{5,0,0,8,
                          0,0,1,0,
                          0,5,0,6,
                          0,0,0,0};

  std:vector<double> out {25,0,0,40,
                          0,25,0,30,
                          0,0,1,0,
                          40,30,0,100}; 

  // Create TaskData
  std::shared_ptr<ppc::core::TaskData> taskDataSeq = std::make_shared<ppc::core::TaskData>();
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(in1.data()));
  taskDataSeq->inputs_count.emplace_back(in1.size());
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(in2.data()));
  taskDataSeq->inputs_count.emplace_back(in2.size());
  taskDataSeq->outputs.emplace_back(reinterpret_cast<uint8_t *>(out.data()));
  taskDataSeq->outputs_count.emplace_back(out.size());

  // Create Task
  TestTaskSequential testTaskSequential(taskDataSeq);
  ASSERT_EQ(testTaskSequential.validation(), true);
  testTaskSequential.pre_processing();
  testTaskSequential.run();
  testTaskSequential.post_processing();
  int ch = 0;
  for(int i = 0; i < out.size; ++i) {
    if(result[i] == out[i]) {
      k++;
    }
  }
  ASSERT_EQ(k, 16);
}