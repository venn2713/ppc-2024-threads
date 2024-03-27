// Copyright 2024 Sharapov Georgiy

#include <gtest/gtest.h>

#include <vector>

#include "seq/sharapov_g_sobel/include/ssobel_seq.hpp"

TEST(sharapov_g_sobel_seq, Test_Seed_1234) {
  int width = 10;
  int height = 10;
  std::vector<SSobelSeq::RGB> ColoredImage = SSobelSeq::generateColorImage(width, height, 1234);
  std::vector<SSobelSeq::GrayScale> EdgeImage(ColoredImage.size());
  std::vector<SSobelSeq::GrayScale> EdgeImageExpected = {
      {255}, {0},   {255}, {255}, {255}, {0},   {255}, {0},   {255}, {0},   {255}, {0},   {0},   {0},   {0},
      {0},   {255}, {255}, {255}, {255}, {255}, {255}, {0},   {0},   {0},   {255}, {0},   {255}, {0},   {0},
      {255}, {0},   {0},   {0},   {0},   {0},   {255}, {0},   {255}, {255}, {255}, {255}, {0},   {0},   {255},
      {255}, {255}, {0},   {255}, {0},   {0},   {0},   {0},   {0},   {0},   {0},   {255}, {255}, {255}, {255},
      {255}, {255}, {0},   {0},   {0},   {0},   {255}, {255}, {0},   {0},   {255}, {255}, {0},   {0},   {0},
      {0},   {0},   {255}, {255}, {255}, {0},   {255}, {255}, {255}, {0},   {0},   {0},   {0},   {0},   {0},
      {255}, {255}, {255}, {255}, {255}, {255}, {255}, {0},   {255}, {0},
  };

  // TaskData
  std::shared_ptr<ppc::core::TaskData> taskDataSeq = std::make_shared<ppc::core::TaskData>();
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(ColoredImage.data()));
  taskDataSeq->inputs_count.emplace_back(width);
  taskDataSeq->inputs_count.emplace_back(height);
  taskDataSeq->outputs.emplace_back(reinterpret_cast<uint8_t *>(EdgeImage.data()));
  taskDataSeq->outputs_count.emplace_back(width);
  taskDataSeq->outputs_count.emplace_back(height);

  // Task
  SSobelSeq SSobelSeq(taskDataSeq);
  ASSERT_EQ(SSobelSeq.validation(), true);
  ASSERT_EQ(SSobelSeq.pre_processing(), true);
  ASSERT_EQ(SSobelSeq.run(), true);
  ASSERT_EQ(SSobelSeq.post_processing(), true);

  for (size_t i = 0; i < ColoredImage.size(); ++i) {
    ASSERT_EQ(static_cast<int>(EdgeImageExpected[i].value), static_cast<int>(EdgeImage[i].value));
  }
}

TEST(sharapov_g_sobel_seq, Test_Seed_2451) {
  int width = 10;
  int height = 10;
  std::vector<SSobelSeq::RGB> ColoredImage = SSobelSeq::generateColorImage(width, height, 2451);
  std::vector<SSobelSeq::GrayScale> EdgeImage(ColoredImage.size());
  std::vector<SSobelSeq::GrayScale> EdgeImageExpected = {
      {0},   {255}, {255}, {0},   {255}, {255}, {0},   {0},   {0},   {0},   {255}, {0},   {0},   {255}, {255},
      {255}, {0},   {0},   {0},   {255}, {0},   {255}, {255}, {255}, {0},   {255}, {255}, {255}, {255}, {255},
      {0},   {0},   {0},   {0},   {255}, {255}, {255}, {0},   {0},   {255}, {0},   {0},   {255}, {255}, {0},
      {255}, {255}, {255}, {255}, {255}, {255}, {255}, {0},   {255}, {0},   {255}, {0},   {255}, {255}, {255},
      {255}, {0},   {255}, {0},   {255}, {255}, {255}, {255}, {255}, {0},   {255}, {255}, {255}, {0},   {255},
      {255}, {255}, {255}, {255}, {255}, {255}, {255}, {0},   {255}, {255}, {255}, {0},   {255}, {255}, {255},
      {255}, {255}, {255}, {0},   {255}, {255}, {255}, {255}, {0},   {255},
  };

  // TaskData
  std::shared_ptr<ppc::core::TaskData> taskDataSeq = std::make_shared<ppc::core::TaskData>();
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(ColoredImage.data()));
  taskDataSeq->inputs_count.emplace_back(width);
  taskDataSeq->inputs_count.emplace_back(height);
  taskDataSeq->outputs.emplace_back(reinterpret_cast<uint8_t *>(EdgeImage.data()));
  taskDataSeq->outputs_count.emplace_back(width);
  taskDataSeq->outputs_count.emplace_back(height);

  // Task
  SSobelSeq SSobelSeq(taskDataSeq);
  ASSERT_EQ(SSobelSeq.validation(), true);
  ASSERT_EQ(SSobelSeq.pre_processing(), true);
  ASSERT_EQ(SSobelSeq.run(), true);
  ASSERT_EQ(SSobelSeq.post_processing(), true);

  for (size_t i = 0; i < ColoredImage.size(); ++i) {
    ASSERT_EQ(static_cast<int>(EdgeImageExpected[i].value), static_cast<int>(EdgeImage[i].value));
  }
}

TEST(sharapov_g_sobel_seq, Test_Seed_2423) {
  int width = 10;
  int height = 10;
  std::vector<SSobelSeq::RGB> ColoredImage = SSobelSeq::generateColorImage(width, height, 2423);
  std::vector<SSobelSeq::GrayScale> EdgeImage(ColoredImage.size());
  std::vector<SSobelSeq::GrayScale> EdgeImageExpected = {
      {255}, {255}, {255}, {0},   {0},   {255}, {255}, {255}, {0},   {0},   {0},   {255}, {0}, {255}, {255},
      {0},   {0},   {0},   {0},   {0},   {0},   {255}, {255}, {0},   {0},   {255}, {255}, {0}, {0},   {0},
      {255}, {255}, {0},   {255}, {255}, {255}, {0},   {0},   {0},   {255}, {0},   {0},   {0}, {0},   {255},
      {0},   {0},   {0},   {255}, {255}, {255}, {255}, {255}, {0},   {0},   {255}, {255}, {0}, {0},   {255},
      {255}, {255}, {0},   {255}, {255}, {0},   {255}, {255}, {255}, {0},   {0},   {255}, {0}, {0},   {255},
      {0},   {0},   {0},   {255}, {0},   {255}, {255}, {255}, {0},   {0},   {0},   {0},   {0}, {255}, {255},
      {255}, {255}, {0},   {0},   {0},   {0},   {255}, {255}, {255}, {0},
  };

  // TaskData
  std::shared_ptr<ppc::core::TaskData> taskDataSeq = std::make_shared<ppc::core::TaskData>();
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(ColoredImage.data()));
  taskDataSeq->inputs_count.emplace_back(width);
  taskDataSeq->inputs_count.emplace_back(height);
  taskDataSeq->outputs.emplace_back(reinterpret_cast<uint8_t *>(EdgeImage.data()));
  taskDataSeq->outputs_count.emplace_back(width);
  taskDataSeq->outputs_count.emplace_back(height);

  // Task
  SSobelSeq SSobelSeq(taskDataSeq);
  ASSERT_EQ(SSobelSeq.validation(), true);
  ASSERT_EQ(SSobelSeq.pre_processing(), true);
  ASSERT_EQ(SSobelSeq.run(), true);
  ASSERT_EQ(SSobelSeq.post_processing(), true);

  for (size_t i = 0; i < ColoredImage.size(); ++i) {
    ASSERT_EQ(static_cast<int>(EdgeImageExpected[i].value), static_cast<int>(EdgeImage[i].value));
  }
}

TEST(sharapov_g_sobel_seq, Test_Seed_2354) {
  int width = 10;
  int height = 10;
  std::vector<SSobelSeq::RGB> ColoredImage = SSobelSeq::generateColorImage(width, height, 2354);
  std::vector<SSobelSeq::GrayScale> EdgeImage(ColoredImage.size());
  std::vector<SSobelSeq::GrayScale> EdgeImageExpected = {
      {255}, {255}, {0},   {255}, {0},   {0},   {0},   {0},   {0},   {0},   {255}, {255}, {255}, {255}, {0},
      {255}, {0},   {0},   {255}, {0},   {255}, {255}, {0},   {0},   {0},   {255}, {255}, {0},   {255}, {0},
      {255}, {255}, {0},   {0},   {255}, {255}, {255}, {0},   {255}, {0},   {255}, {255}, {0},   {255}, {255},
      {0},   {255}, {0},   {0},   {255}, {0},   {255}, {255}, {0},   {0},   {255}, {255}, {255}, {0},   {0},
      {255}, {255}, {255}, {255}, {0},   {255}, {0},   {255}, {255}, {255}, {0},   {255}, {0},   {255}, {0},
      {255}, {255}, {255}, {0},   {0},   {255}, {0},   {255}, {255}, {255}, {0},   {255}, {255}, {0},   {0},
      {0},   {255}, {255}, {255}, {255}, {255}, {0},   {255}, {0},   {0},
  };

  // TaskData
  std::shared_ptr<ppc::core::TaskData> taskDataSeq = std::make_shared<ppc::core::TaskData>();
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(ColoredImage.data()));
  taskDataSeq->inputs_count.emplace_back(width);
  taskDataSeq->inputs_count.emplace_back(height);
  taskDataSeq->outputs.emplace_back(reinterpret_cast<uint8_t *>(EdgeImage.data()));
  taskDataSeq->outputs_count.emplace_back(width);
  taskDataSeq->outputs_count.emplace_back(height);

  // Task
  SSobelSeq SSobelSeq(taskDataSeq);
  ASSERT_EQ(SSobelSeq.validation(), true);
  ASSERT_EQ(SSobelSeq.pre_processing(), true);
  ASSERT_EQ(SSobelSeq.run(), true);
  ASSERT_EQ(SSobelSeq.post_processing(), true);

  for (size_t i = 0; i < ColoredImage.size(); ++i) {
    ASSERT_EQ(static_cast<int>(EdgeImageExpected[i].value), static_cast<int>(EdgeImage[i].value));
  }
}

TEST(sharapov_g_sobel_seq, Test_Seed_3453) {
  int width = 10;
  int height = 10;
  std::vector<SSobelSeq::RGB> ColoredImage = SSobelSeq::generateColorImage(width, height, 3453);
  std::vector<SSobelSeq::GrayScale> EdgeImage(ColoredImage.size());
  std::vector<SSobelSeq::GrayScale> EdgeImageExpected = {
      {0},   {255}, {0},   {0},   {0},   {255}, {0},   {255}, {0},   {0},   {255}, {255}, {0},   {0},   {0},
      {255}, {0},   {255}, {0},   {255}, {0},   {0},   {0},   {0},   {0},   {0},   {255}, {255}, {0},   {0},
      {0},   {0},   {0},   {255}, {255}, {0},   {0},   {0},   {255}, {0},   {0},   {255}, {255}, {255}, {255},
      {0},   {0},   {0},   {0},   {0},   {255}, {255}, {0},   {255}, {0},   {255}, {255}, {0},   {0},   {0},
      {255}, {255}, {255}, {255}, {255}, {255}, {0},   {0},   {0},   {0},   {0},   {255}, {255}, {255}, {0},
      {0},   {0},   {0},   {0},   {0},   {255}, {0},   {255}, {255}, {255}, {0},   {0},   {255}, {0},   {255},
      {255}, {0},   {0},   {0},   {255}, {0},   {255}, {255}, {255}, {255},
  };

  // TaskData
  std::shared_ptr<ppc::core::TaskData> taskDataSeq = std::make_shared<ppc::core::TaskData>();
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(ColoredImage.data()));
  taskDataSeq->inputs_count.emplace_back(width);
  taskDataSeq->inputs_count.emplace_back(height);
  taskDataSeq->outputs.emplace_back(reinterpret_cast<uint8_t *>(EdgeImage.data()));
  taskDataSeq->outputs_count.emplace_back(width);
  taskDataSeq->outputs_count.emplace_back(height);

  // Task
  SSobelSeq SSobelSeq(taskDataSeq);
  ASSERT_EQ(SSobelSeq.validation(), true);
  ASSERT_EQ(SSobelSeq.pre_processing(), true);
  ASSERT_EQ(SSobelSeq.run(), true);
  ASSERT_EQ(SSobelSeq.post_processing(), true);

  for (size_t i = 0; i < ColoredImage.size(); ++i) {
    ASSERT_EQ(static_cast<int>(EdgeImageExpected[i].value), static_cast<int>(EdgeImage[i].value));
  }
}
