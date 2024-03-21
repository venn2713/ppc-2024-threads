// Copyright 2024 Zorin Oleg
#include <gtest/gtest.h>

#include <vector>

#include "seq/zorin_o_crs_matmult/include/crs_matmult_seq.hpp"

TEST(Zorin_O_CRS_MatMult_Seq, zero_rhs_matrix) {
  // Create data
  size_t p = 100;
  size_t q = 100;
  size_t r = 100;
  std::vector<double> lhs_in = getRandomMatrix(p, q);
  std::vector<double> rhs_in(q * r);
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
  for (size_t i = 0; i < out.size(); ++i) {
    EXPECT_DOUBLE_EQ(out[i], 0.0);
  }
}

TEST(Zorin_O_CRS_MatMult_Seq, zero_lhs_matrix) {
  // Create data
  size_t p = 100;
  size_t q = 100;
  size_t r = 100;
  std::vector<double> lhs_in(p * q);
  std::vector<double> rhs_in = getRandomMatrix(q, r);
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
  for (size_t i = 0; i < out.size(); ++i) {
    EXPECT_DOUBLE_EQ(out[i], 0.0);
  }
}

TEST(Zorin_O_CRS_MatMult_Seq, identity_rhs_matrix) {
  // Create data
  size_t p = 100;
  size_t q = 100;
  size_t r = q;
  std::vector<double> lhs_in = getRandomMatrix(p, q);
  std::vector<double> rhs_in = getIdentityMatrix(q);
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
  for (size_t i = 0; i < out.size(); ++i) {
    EXPECT_DOUBLE_EQ(out[i], lhs_in[i]);
  }
}

TEST(Zorin_O_CRS_MatMult_Seq, identity_lhs_matrix) {
  // Create data
  size_t p = 100;
  size_t q = p;
  size_t r = 100;
  std::vector<double> lhs_in = getIdentityMatrix(p);
  std::vector<double> rhs_in = getRandomMatrix(q, r);
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
  for (size_t i = 0; i < out.size(); ++i) {
    EXPECT_DOUBLE_EQ(out[i], rhs_in[i]);
  }
}

TEST(Zorin_O_CRS_MatMult_Seq, test_matmult1) {
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
  for (size_t i = 0; i < out.size(); ++i) {
    EXPECT_DOUBLE_EQ(out[i], ans[i]);
  }
}

TEST(Zorin_O_CRS_MatMult_Seq, test_matmult2) {
  // Create data
  size_t p = 100;
  size_t q = 100;
  size_t r = 100;
  std::vector<double> lhs_in(p * q);
  for (size_t i = 0; i < lhs_in.size(); ++i) {
    if (i % 2 > 0)
      lhs_in[i] = 1.0;
  }
  std::vector<double> rhs_in(q * r);
  for (size_t i = 0; i < lhs_in.size(); ++i) {
    if (i % 2 == 0)
      lhs_in[i] = 1.0;
  }
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
  for (size_t i = 0; i < out.size(); ++i) {
    EXPECT_DOUBLE_EQ(out[i], 0.0);
  }
}
