// Copyright 2024 Sharapov Georgiy

#pragma once

#include <vector>
#include <utility>
#include <memory>

#include "core/task/include/task.hpp"

class SSobelSeq : public ppc::core::Task {
 public:
  explicit SSobelSeq(std::shared_ptr<ppc::core::TaskData> taskData_) : Task(std::move(taskData_)) {}
  bool pre_processing() override;
  bool validation() override;
  bool run() override;
  bool post_processing() override;

    struct RGB {
      uint8_t r, g, b;
    };

    struct GrayScale {
      uint8_t value;
    };

  static void printPixel(std::vector<GrayScale> Image, int width, int height);
  static std::vector<RGB> generateColorImage(size_t width, size_t height, size_t seed);
  static GrayScale getPixel(const std::vector<GrayScale>& image, size_t x, size_t y, size_t width, size_t height);

  std::vector<GrayScale> convertToGrayScale(const std::vector<RGB>& colorImage, size_t width, size_t height);
  std::vector<GrayScale> SobelOperatorSeq(const std::vector<GrayScale>& grayImage, size_t width, size_t height);

 private:
  size_t imgWidth{}, imgHeight{}, imgSize{};
  std::vector<RGB>       colored_img{};
  std::vector<GrayScale> grayscale_img{};
  std::vector<GrayScale> result{};
};
