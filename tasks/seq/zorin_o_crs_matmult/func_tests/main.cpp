// Copyright 2024 Zorin Oleg
#include <gtest/gtest.h>

#include <vector>

#include "seq/zorin_o_crs_matmult/include/crs_matmult_seq.hpp"

TEST(Sequential, Zorin_O_CRS_MatMult) {
  // Create data
  size_t p = 4;
  size_t q = 5;
  size_t r = 4;
  std::vector<double> lhs_in{
      0, 10, 0, 0, 0, 0, 5, 3, 0, 0, 1, -1, -1, 0, 0, 0, 0, -5, 0, 20,
  };
  std::vector<double> rhs_in{
      1, 1, 0, 0, 0, 5, 9, 9, 0, 0, 0, -1, 13, 7, 0, 0, 7, 0, 8, 0,
  };
  std::vector<double> ans{
      0, 50, 90, 90, 0, 25, 45, 42, 1, -4, -9, -8, 140, 0, 160, 5,
  };
  std::vector<double> out(p * r);
  // Create TaskData
  std::shared_ptr<ppc::core::TaskData> taskDataSeq = std::make_shared<ppc::core::TaskData>();
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(lhs_in.data()));
  taskDataSeq->inputs_count.emplace_back(p);
  taskDataSeq->inputs_count.emplace_back(q);
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(rhs_in.data()));
  taskDataSeq->inputs_count.emplace_back(q);
  taskDataSeq->inputs_count.emplace_back(r);
  taskDataSeq->outputs.emplace_back(reinterpret_cast<uint8_t *>(out.data()));
  taskDataSeq->outputs_count.emplace_back(p);
  taskDataSeq->outputs_count.emplace_back(r);

  // Create Task
  CRSMatMult crsMatMultSeq(taskDataSeq);
  ASSERT_TRUE(crsMatMultSeq.validation());
  ASSERT_TRUE(crsMatMultSeq.pre_processing());
  ASSERT_TRUE(crsMatMultSeq.run());
  ASSERT_TRUE(crsMatMultSeq.post_processing());
  for (size_t i = 0; i < p; ++i) {
    for (size_t j = 0; j < r; ++j) {
      EXPECT_DOUBLE_EQ(out[i * r + j], ans[i * r + j]);
    }
  }
}
