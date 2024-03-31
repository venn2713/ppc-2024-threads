// Copyright 2023 Nesterov Alexander
#include <gtest/gtest.h>

#include <random>
#include <numeric>
#include <vector>

#include "seq/kashin_s_dijkstra_algorithm/include/Dijkstra.hpp"

TEST(KashinDijkstraSeqTest, TestGraph10) {
  const int vertexCount = 10, edgeWeight = 100, start = 0;
  // создаем повторяющийся рандом
  std::mt19937 rng(42);
  std::uniform_int_distribution<int> dist(1, edgeWeight);
  std::uniform_int_distribution<int> isEdge(0, 2);

  // Create data
  std::vector<int> in;
  in.reserve(vertexCount * vertexCount);
  std::vector<int> out(vertexCount);
  for (int i = 0; i < vertexCount * vertexCount; i++) {
    int weight = isEdge(rng) == 0 ? -1 : dist(rng);
    in.push_back(weight);
  }

  // Create TaskData
  std::shared_ptr<ppc::core::TaskData> taskDataSeq = std::make_shared<ppc::core::TaskData>();
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(in.data()));
  taskDataSeq->inputs_count.emplace_back(in.size());
  taskDataSeq->inputs_count.emplace_back(start);
  taskDataSeq->outputs.emplace_back(reinterpret_cast<uint8_t *>(out.data()));
  taskDataSeq->outputs_count.emplace_back(out.size());

  // Create Task
  KashinDijkstraSeq::Dijkstra dijkstra(taskDataSeq);
  ASSERT_EQ(dijkstra.validation(), true);
  dijkstra.pre_processing();
  dijkstra.run();
  dijkstra.post_processing();
  ASSERT_EQ(299, std::accumulate(out.begin(), out.end(), 0));
}

TEST(KashinDijkstraSeqTest, TestGraph100) {
  const int vertexCount = 100, edgeWeight = 100, start = 0;
  // создаем повторяющийся рандом
  std::mt19937 rng(42);
  std::uniform_int_distribution<int> dist(1, edgeWeight);
  std::uniform_int_distribution<int> isEdge(0, 2);

  // Create data
  std::vector<int> in;
  in.reserve(vertexCount * vertexCount);
  std::vector<int> out(vertexCount);
  for (int i = 0; i < vertexCount * vertexCount; i++) {
    int weight = isEdge(rng) == 0 ? -1 : dist(rng);
    in.push_back(weight);
  }

  // Create TaskData
  std::shared_ptr<ppc::core::TaskData> taskDataSeq = std::make_shared<ppc::core::TaskData>();
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(in.data()));
  taskDataSeq->inputs_count.emplace_back(in.size());
  taskDataSeq->inputs_count.emplace_back(start);
  taskDataSeq->outputs.emplace_back(reinterpret_cast<uint8_t *>(out.data()));
  taskDataSeq->outputs_count.emplace_back(out.size());

  // Create Task
  KashinDijkstraSeq::Dijkstra dijkstra(taskDataSeq);
  ASSERT_EQ(dijkstra.validation(), true);
  dijkstra.pre_processing();
  dijkstra.run();
  dijkstra.post_processing();
  ASSERT_EQ(987, std::accumulate(out.begin(), out.end(), 0));
}

TEST(KashinDijkstraSeqTest, TestGraph1000) {
  const int vertexCount = 10, edgeWeight = 1000, start = 0;
  // создаем повторяющийся рандом
  std::mt19937 rng(42);
  std::uniform_int_distribution<int> dist(1, edgeWeight);
  std::uniform_int_distribution<int> isEdge(0, 2);

  // Create data
  std::vector<int> in;
  in.reserve(vertexCount * vertexCount);
  std::vector<int> out(vertexCount);
  for (int i = 0; i < vertexCount * vertexCount; i++) {
    int weight = isEdge(rng) == 0 ? -1 : dist(rng);
    in.push_back(weight);
  }

  // Create TaskData
  std::shared_ptr<ppc::core::TaskData> taskDataSeq = std::make_shared<ppc::core::TaskData>();
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(in.data()));
  taskDataSeq->inputs_count.emplace_back(in.size());
  taskDataSeq->inputs_count.emplace_back(start);
  taskDataSeq->outputs.emplace_back(reinterpret_cast<uint8_t *>(out.data()));
  taskDataSeq->outputs_count.emplace_back(out.size());

  // Create Task
  KashinDijkstraSeq::Dijkstra dijkstra(taskDataSeq);
  ASSERT_EQ(dijkstra.validation(), true);
  dijkstra.pre_processing();
  dijkstra.run();
  dijkstra.post_processing();
  ASSERT_EQ(2863, std::accumulate(out.begin(), out.end(), 0));
}

TEST(KashinDijkstraSeqTest, TestGraph10000) {
  const int vertexCount = 10, edgeWeight = 10000, start = 0;
  // создаем повторяющийся рандом
  std::mt19937 rng(42);
  std::uniform_int_distribution<int> dist(1, edgeWeight);
  std::uniform_int_distribution<int> isEdge(0, 2);

  // Create data
  std::vector<int> in;
  in.reserve(vertexCount * vertexCount);
  std::vector<int> out(vertexCount);
  for (int i = 0; i < vertexCount * vertexCount; i++) {
    int weight = isEdge(rng) == 0 ? -1 : dist(rng);
    in.push_back(weight);
  }

  // Create TaskData
  std::shared_ptr<ppc::core::TaskData> taskDataSeq = std::make_shared<ppc::core::TaskData>();
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(in.data()));
  taskDataSeq->inputs_count.emplace_back(in.size());
  taskDataSeq->inputs_count.emplace_back(start);
  taskDataSeq->outputs.emplace_back(reinterpret_cast<uint8_t *>(out.data()));
  taskDataSeq->outputs_count.emplace_back(out.size());

  // Create Task
  KashinDijkstraSeq::Dijkstra dijkstra(taskDataSeq);
  ASSERT_EQ(dijkstra.validation(), true);
  dijkstra.pre_processing();
  dijkstra.run();
  dijkstra.post_processing();
  ASSERT_EQ(28503, std::accumulate(out.begin(), out.end(), 0));
}
