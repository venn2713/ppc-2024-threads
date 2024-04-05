// Copyright 2024 Vetoshnikova Ekaterina
#include "seq/vetoshnikova_k_convex_hull_bin_image_components/include/ops_seq.hpp"

#include <thread>

using namespace std::chrono_literals;

bool TaskSequential::pre_processing() {
  internal_order_test();
  image_ = reinterpret_cast<decltype(image_)>(taskData->inputs[0]);
  w = taskData->inputs_count[0];
  h = taskData->inputs_count[1];
  image = *image_;
  hull = {};
  return true;
}

bool TaskSequential::validation() {
  internal_order_test();
  return taskData->inputs_count[0] > 0 && taskData->inputs_count[1] > 0;
}

bool TaskSequential::run() {
  internal_order_test();
  std::vector<int> img = find_components(image, w, h);
  int components = count_components(img);
  for (int i = 1; i <= components; ++i) {
    std::vector<int> points = remove_extra_points(img, w, h, i);
    std::vector<int> ch = Algorithm_Graham(points);
    for (int j = 0; j < ch.size(); ++j) {
      hull.emplace_back(ch[j]);
    }
    hull.emplace_back(-1);
  }

  return true;
}

bool TaskSequential::post_processing() {
  internal_order_test();
  std::copy(hull.begin(), hull.end(), reinterpret_cast<int*>(taskData->outputs[0]));
  return true;
}

void mark_component(std::vector<int>* image, int h, int w, int yStart, int xStart, int label) {
  std::stack<std::pair<int, int>> stack;

  stack.push(std::make_pair(xStart, yStart));

  while (!stack.empty()) {
    int x = stack.top().first;
    int y = stack.top().second;
    stack.pop();

    if (x >= 0 && y >= 0 && x < w && y < h && image->at(y * w + x) == 1) {
      (*image)[y * w + x] = label;

      stack.push(std::make_pair(x - 1, y));
      stack.push(std::make_pair(x - 1, y - 1));
      stack.push(std::make_pair(x - 1, y + 1));
      stack.push(std::make_pair(x, y - 1));
      stack.push(std::make_pair(x, y + 1));
      stack.push(std::make_pair(x + 1, y));
      stack.push(std::make_pair(x + 1, y - 1));
      stack.push(std::make_pair(x + 1, y + 1));
    }
  }
}

std::vector<int> find_components(const std::vector<std::vector<int>>& image, int w, int h) {
  std::vector<int> image_arr(w * h);
  for (int i = 0; i < h; ++i) {
    for (int j = 0; j < w; ++j) {
      image_arr[i * w + j] = image[i][j];
    }
  }
  int label = 10;
  for (int i = 0; i < h; ++i) {
    for (int j = 0; j < w; ++j) {
      if (image_arr[i * w + j] == 1) {
        mark_component(&image_arr, h, w, i, j, label);
        ++label;
      }
    }
  }
  for (int i = 0; i < h; ++i) {
    for (int j = 0; j < w; ++j) {
      if (image_arr[i * w + j] != 0) {
        image_arr[i * w + j] -= 9;
      }
    }
  }
  return image_arr;
}

int count_components(const std::vector<int>& image) {
  int c = 0;
  for (int i = 0; i < image.size(); ++i) {
    if (image[i] > c) {
      c = image[i];
    }
  }
  return c;
}

int count_points_component(const std::vector<int>& image) {
  int count_points = 0;
  for (int i = 0; i < image.size(); ++i) {
    if (image[i] != 0) {
      count_points++;
    }
  }
  return count_points;
}

std::vector<int> remove_extra_points(const std::vector<int>& image, int w, int h, int label) {
  std::vector<int> img(image);
  for (int i = 0; i < h; ++i) {
    for (int j = 0; j < w; ++j) {
      if (image[i * w + j] == label) {
        if ((j > 0) && (j < w - 1)) {
          if ((i == 0) || (i == h - 1)) {
            if ((image[i * w + j - 1] == label) && (image[i * w + j + 1] == label)) {
              img[i * w + j] = 0;
            }
          }
          if ((i > 0) && (i < h - 1)) {
            if (((image[i * w + j - 1] == label) && (image[i * w + j + 1] == label)) ||
                ((image[(i + 1) * w + j] == label) && (image[(i - 1) * w + j] == label))) {
              img[i * w + j] = 0;
            }
          }
          continue;
        }
        if ((i > 0) && (i < h - 1)) {
          if ((j == 0) || (j == w - 1)) {
            if ((image[(i - 1) * w + j] == label) && (image[(i + 1) * w + j] == label)) {
              img[i * w + j] = 0;
            }
          }
          if ((j > 0) && (j < w - 1)) {
            if (((image[i * w + j - 1] == label) && (image[i * w + j + 1] == label)) ||
                ((image[(i + 1) * w + j] == label) && (image[(i - 1) * w + j] == label))) {
              img[i * w + j] = 0;
            }
          }
        }
      } else {
        img[i * w + j] = 0;
      }
    }
  }
  int size = count_points_component(img);
  std::vector<int> points(size * 2);
  int k = 0;
  for (int i = 0; i < h; ++i) {
    for (int j = 0; j < w; ++j) {
      if (img[i * w + j] != 0) {
        points[k] = j;
        k++;
        points[k] = i;
        k++;
      }
    }
  }
  return points;
}

int Cross(int x1, int y1, int x2, int y2, int x3, int y3) { return ((x2 - x1) * (y3 - y2) - (x3 - x2) * (y2 - y1)); }

void Sort(std::vector<int>* points, int xMin, int yMin) {
  int size = points->size() / 2;
  for (int i = 1; i < size; ++i) {
    int j = i;
    while ((j > 0) && (Cross(xMin, yMin, (*points)[2 * j - 2], (*points)[2 * j - 1], (*points)[2 * j],
                             (*points)[2 * j + 1]) < 0)) {
      int temp = (*points)[2 * j - 2];
      (*points)[2 * j - 2] = (*points)[2 * j];
      (*points)[2 * j] = temp;

      temp = (*points)[2 * j - 1];
      (*points)[2 * j - 1] = (*points)[2 * j + 1];
      (*points)[2 * j + 1] = temp;
      j--;
    }
  }
}

std::vector<int> Algorithm_Graham(std::vector<int> points) {
  std::vector<int> result;

  int num_points = points.size() / 2;

  if (num_points > 1) {
    int x_min = points[0];
    int y_min = points[1];

    int min_index = 0;

    for (int i = 2; i < points.size(); i += 2) {
      if (points[i] < x_min || (points[i] == x_min && points[i + 1] < y_min)) {
        x_min = points[i];

        y_min = points[i + 1];

        min_index = i;
      }
    }

    int temp = points[min_index];
    points[min_index] = points[num_points * 2 - 2];
    points[num_points * 2 - 2] = temp;

    temp = points[min_index + 1];
    points[min_index + 1] = points[num_points * 2 - 1];
    points[num_points * 2 - 1] = temp;

    points.pop_back();
    points.pop_back();

    Sort(&points, x_min, y_min);

    result.emplace_back(x_min);
    result.emplace_back(y_min);
    result.emplace_back(points[0]);
    result.emplace_back(points[1]);

    for (int i = 2; i < points.size(); i += 2) {
      int result_size = result.size();

      int x1 = result[result_size - 4];
      int y1 = result[result_size - 3];
      int x2 = result[result_size - 2];
      int y2 = result[result_size - 1];
      int x3 = points[i];
      int y3 = points[i + 1];

      int rot = Cross(x1, y1, x2, y2, x3, y3);
      if (rot == 0) {
        result[result_size - 2] = x3;
        result[result_size - 1] = y3;
      } else if (rot < 0) {
        while (Cross(result[(result.size()) - 4], result[(result.size()) - 3], result[(result.size()) - 2],
                     result[(result.size()) - 1], x3, y3) < 0)
          result.pop_back(), result.pop_back();
        result.emplace_back(x3);
        result.emplace_back(y3);
      } else {
        result.emplace_back(x3);
        result.emplace_back(y3);
      }
    }
  } else {
    result.resize(2);
    result[0] = points[0];
    result[1] = points[1];
  }
  return result;
}
