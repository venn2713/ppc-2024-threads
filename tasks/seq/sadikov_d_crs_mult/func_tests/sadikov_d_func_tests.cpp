// Copyright 2024 Sadikov Damir
#include <gtest/gtest.h>

#include <vector>

#include "seq/sadikov_d_crs_mult/include/sadikov_d_seq.hpp"

TEST(sadikov_d_crs_mult_seq, test_small_real_matrix) {
  matrix_CRS A;
  A.n = 5;
  A.m = 5;
  A.row_id = {0, 1, 4, 4, 6, 8};
  A.col = {0, 1, 3, 4, 0, 4, 1, 3};
  A.value = {1, 2, 4, 3, 1, -3, 7, 6};
  matrix_CRS B;
  B.n = 5;
  B.m = 5;
  B.row_id = {0, 1, 3, 4, 6, 7};
  B.col = {3, 1, 2, 3, 0, 1, 2};
  B.value = {1, 1, 4, -2, 4, 3, 1};
  matrix_CRS C;

  // Create TaskData
  std::shared_ptr<ppc::core::TaskData> taskDataSeq = std::make_shared<ppc::core::TaskData>();
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(&A));
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(&B));
  taskDataSeq->outputs.emplace_back(reinterpret_cast<uint8_t *>(&C));

  // Create Task
  CRSComplexMult_Sequential taskSequential(taskDataSeq);
  ASSERT_EQ(taskSequential.validation(), true);
  ASSERT_EQ(taskSequential.pre_processing(), true);
  ASSERT_EQ(taskSequential.run(), true);
  ASSERT_EQ(taskSequential.post_processing(), true);
  
  // Check Result
  matrix_CRS C_expected;
  C_expected.n = 5;
  C_expected.m = 5;
  C_expected.row_id = {0, 1, 4, 4, 6, 9};
  C_expected.col = {3, 0, 1, 2, 2, 3, 0, 1, 2};
  C_expected.value = {1, 16, 14, 11, -3, 1, 24, 25, 28};

  ASSERT_EQ(C.n, C_expected.n);
  ASSERT_EQ(C.m, C_expected.m);
  ASSERT_EQ(C.row_id, C_expected.row_id);
  ASSERT_EQ(C.col, C_expected.col);
  ASSERT_EQ(C.value, C_expected.value);
  // TODO better comapare with epsilon ???
}

TEST(sadikov_d_crs_mult_seq, test_2) {
  // TODO test_2
}

TEST(sadikov_d_crs_mult_seq, test_3) {
  // TODO test_2
}

TEST(sadikov_d_crs_mult_seq, test_4) {
  // TODO test_4
}

TEST(sadikov_d_crs_mult_seq, test_5) {
  // TODO test_5
}
