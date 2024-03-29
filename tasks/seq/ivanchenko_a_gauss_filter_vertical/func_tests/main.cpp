// Copyright 2024 Ivanchenko Aleksei
#include <gtest/gtest.h>

#include <vector>

#include "seq/ivanchenko_a_gauss_filter_vertical/include/ops_seq.hpp"

TEST(ivanchenko_a_gauss_filter_vertical, Test) {
  uint32_t width = 10, height = 10; 
  
  // Create data
  std::vector<uint8_t> in(width*height*3, 128);
  std::vector<uint8_t> out(width*height*3, 0);

  // Create TaskData
  std::shared_ptr<ppc::core::TaskData> taskDataSeq = std::make_shared<ppc::core::TaskData>();
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(in.data()));
  taskDataSeq->inputs_count.emplace_back(width);
  taskDataSeq->inputs_count.emplace_back(height);
  taskDataSeq->outputs.emplace_back(reinterpret_cast<uint8_t *>(out.data()));
  taskDataSeq->outputs_count.emplace_back(width);
  taskDataSeq->outputs_count.emplace_back(height);

  // Create Task
  GaussFilterSequential gaussFilterSequential(taskDataSeq);
  ASSERT_EQ(gaussFilterSequential.validation(), true);
  gaussFilterSequential.pre_processing();
  gaussFilterSequential.run();
  gaussFilterSequential.post_processing();
  ASSERT_EQ(in[0], out[0]);
}
