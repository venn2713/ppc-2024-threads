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
  std::vector<int> img = findComponents(image, w, h);
  int c = countComponents(img);
  for (int i = 1; i <= c; ++i) {
    std::vector<int> component = removePoints(img, w, h, i);
    std::vector<int> hullComponent = AlgorithmGraham(component);
    for (size_t j = 0; j < hullComponent.size(); ++j) {
      hull.emplace_back(hullComponent[j]);
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

void markComponents(std::vector<int>* image, int w, int h, int startY, int startX, int label) {
  std::stack<std::pair<int, int>> stack;

  stack.emplace(startX, startY);

  while (!stack.empty()) {
    int x = stack.top().first;
    int y = stack.top().second;
    stack.pop();

    if (x >= 0 && y >= 0 && x < w && y < h && image->at(y * w + x) == 1) {
      (*image)[y * w + x] = label;

      stack.emplace(x - 1, y);
      stack.emplace(x - 1, y - 1);
      stack.emplace(x - 1, y + 1);
      stack.emplace(x, y - 1);
      stack.emplace(x, y + 1);
      stack.emplace(x + 1, y);
      stack.emplace(x + 1, y - 1);
      stack.emplace(x + 1, y + 1);
    }
  }
}

std::vector<int> findComponents(const std::vector<std::vector<int>>& image, int w, int h) {
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
        markComponents(&image_arr, w, h, i, j, label);
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

int countComponents(const std::vector<int>& image) {
  int c = 0;
  for (size_t i = 0; i < image.size(); ++i) {
    if (image[i] > c) {
      c = image[i];
    }
  }
  return c;
}

int countPointsComponent(const std::vector<int>& image) {
  int c = 0;
  for (size_t i = 0; i < image.size(); ++i) {
    if (image[i] != 0) {
      c++;
    }
  }
  return c;
}

std::vector<int> removePoints(const std::vector<int>& image, int w, int h, int label) {
  std::vector<int> img(image);
  for (int i = 0; i < h; ++i) {
    for (int j = 0; j < w; ++j) {
      if (image[i * w + j] == label) {
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
          continue;
        }
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
        }
      } else {
        img[i * w + j] = 0;
      }
    }
  }
  int sz = countPointsComponent(img);
  std::vector<int> points_j_i(sz * 2);
  int c = 0;
  for (int i = 0; i < h; ++i) {
    for (int j = 0; j < w; ++j) {
      if (img[i * w + j] != 0) {
        points_j_i[c] = j;
        c++;
        points_j_i[c] = i;
        c++;
      }
    }
  }
  return points_j_i;
}

int positionPoints(int x1, int y1, int x2, int y2, int x3, int y3) {
  return ((x2 - x1) * (y3 - y2) - (x3 - x2) * (y2 - y1));
}

void Sort(std::vector<int>* component, int minX, int minY) {
  int sz = component->size() / 2;
  for (int i = 1; i < sz; ++i) {
    int j = i;
    while ((j > 0) && (positionPoints(minX, minY, (*component)[2 * j - 2], (*component)[2 * j - 1], (*component)[2 * j],
                                      (*component)[2 * j + 1]) < 0)) {
      int tmp = (*component)[2 * j - 1];
      (*component)[2 * j - 1] = (*component)[2 * j + 1];
      (*component)[2 * j + 1] = tmp;
      tmp = (*component)[2 * j - 2];
      (*component)[2 * j - 2] = (*component)[2 * j];
      (*component)[2 * j] = tmp;
      j--;
    }
  }
}

std::vector<int> AlgorithmGraham(std::vector<int> component) {
  std::vector<int> result;

  int N = component.size() / 2;

  if (N > 1) {
    int minX = component[0];
    int minY = component[1];

    int minIdx = 0;

    for (size_t i = 2; i < component.size(); i += 2) {
      if (component[i] < minX || (component[i] == minX && component[i + 1] < minY)) {
        minX = component[i];

        minY = component[i + 1];

        minIdx = i;
      }
    }

    int tmp = component[minIdx];
    component[minIdx] = component[N * 2 - 2];
    component[N * 2 - 2] = tmp;

    tmp = component[minIdx + 1];
    component[minIdx + 1] = component[N * 2 - 1];
    component[N * 2 - 1] = tmp;

    component.pop_back();
    component.pop_back();

    Sort(&component, minX, minY);

    result.emplace_back(minX);
    result.emplace_back(minY);
    result.emplace_back(component[0]);
    result.emplace_back(component[1]);

    for (size_t i = 2; i < component.size(); i += 2) {
      int resSize = result.size();

      int x1 = result[resSize - 4];
      int y1 = result[resSize - 3];
      int x2 = result[resSize - 2];
      int y2 = result[resSize - 1];
      int x3 = component[i];
      int y3 = component[i + 1];

      int rot = positionPoints(x1, y1, x2, y2, x3, y3);
      if (rot == 0) {
        result[resSize - 2] = x3;
        result[resSize - 1] = y3;
      } else if (rot < 0) {
        while (positionPoints(result[(result.size()) - 4], result[(result.size()) - 3], result[(result.size()) - 2],
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
    result[0] = component[0];
    result[1] = component[1];
  }
  return result;
}
