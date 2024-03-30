// Copyright 2024 Petrov Maksim

#pragma once //для защиты хедера

#include <string>
#include <vector>

#include "core/task/include/task.hpp"

class RadixSortDoubleSequential : public ppc::core::Task {
 public:
  explicit RadixSortDoubleSequential(std::shared_ptr<ppc::core::TaskData> taskData_) : Task(std::move(taskData_)) {}//перенос данных(для всех задач один и тот же перенос, т.е. не изменяй)
  bool pre_processing() override; // подготавливаем данные к вычислениям(усовершенствовать taskdata(универсальный хранитель данных) для  выполнения run)
  bool validation() override;//проверить, что данные корректны 
  bool run() override;//запуск 
  bool post_processing() override;//получаем нужный ответ

 private:
  //int input_{}, res{};
  //std::vector<double>& input;
  //std::vector<double>& output;
  int data_size;
  std::vector<double>* sort;

  void countSort(double* in, double* out, int len, int exp);
  bool countSortSigns(double* in, double* out, int len);
  std::vector<double> radixSort(const std::vector<double>& data1);

};
