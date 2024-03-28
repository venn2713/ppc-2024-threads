// Copyright 2024 Savotina Valeria
#include <gtest/gtest.h>

//#include <vector>

#include "seq/savotina_v_grahams_alg/include/ops_seq.hpp"

TEST(Sequential, Test_) {
  // Create data
  std::vector<Point> points = {Point(1, 10), Point(12, 14), Point(17, 1), Point(3, 16), Point(7, 12), Point(5, 3), Point(15, 6), Point(9, 8)};
  std::vector<Point> mch = {};
  std::vector<Point> res = {Point(1, 10), Point(5, 3), Point(17, 1), Point(12, 14), Point(3, 16)};

  // Create TaskData
  std::shared_ptr<ppc::core::TaskData> dataGrahamsAlgSeq = std::make_shared<ppc::core::TaskData>();
  dataGrahamsAlgSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(points.data()));
  dataGrahamsAlgSeq->inputs_count.emplace_back(points.size());
  dataGrahamsAlgSeq->outputs.emplace_back(reinterpret_cast<uint8_t *>(mch.data()));
  dataGrahamsAlgSeq->outputs_count.emplace_back(mch.size());

  // Create Task
  GrahamsAlgorithmSequential testGrahamsAlgSeq(dataGrahamsAlgSeq);
  ASSERT_EQ(testGrahamsAlgSeq.validation(), true);
  testGrahamsAlgSeq.pre_processing();
  testGrahamsAlgSeq.run();
  testGrahamsAlgSeq.post_processing();
  ASSERT_EQ(res.data(), mch.data());
}


int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
} // если чё, удалить
