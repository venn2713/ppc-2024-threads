// Copyright 2024 Simonyan Suren
#include "seq/example/include/ops_seq.hpp"

#include <thread>

using namespace std::chrono_literals;

vector<SparseMatrixElement> multiplyCCS(const vector<double>& valuesA, 
  const vector<int>& rowsA, const vector<int>& colPtrA,
  const vector<double>& valuesB, const vector<int>& rowsB,
  const vector<int>& colPtrB, int m, int n, int p) {
    vector<SparseMatrixElement> result;

    for (int j = 0; j < n; ++j) {
        for (int i = 0; i < p; ++i) {
            double dotProduct = 0.0;
            int idxA = colPtrA[i];
            int idxB = colPtrB[j];
            int endA = colPtrA[i + 1];
            int endB = colPtrB[j + 1];

            while (idxA < endA && idxB < endB) {
                if (rowsA[idxA] == rowsB[idxB]) {
                    dotProduct += valuesA[idxA] * valuesB[idxB];
                    ++idxA; ++idxB;
                } else if (rowsA[idxA] < rowsB[idxB]) {
                    ++idxA;
                } else {
                    ++idxB;
                }
            }

            if (dotProduct != 0.0) {
                SparseMatrixElement elem;
                elem.value = dotProduct;
                elem.row = i;
                result.push_back(elem);
            }
        }
    }

    return result;
}

bool TestTaskSequential::pre_processing() {
  internal_order_test();
  // Init value for input and output
  double* matrix1 = reinterpret_cast<double*>(taskData->inputs[0]);
  double* matrix2 = reinterpret_cast<double*>(taskData->inputs[1]);
  numRows1 = taskData->inputs_count[0];
  numCols1 = taskData->inputs_count[1];
  numRows2 = taskData->inputs_count[2];
  numCols2 = taskData->inputs_count[3];

  result = new double[numCols1*numRows2]{};

  int notNullNumbers = 0;
  for (int j = 0; j < numCols1; ++j) {
      colPtr1.push_back(notNullNumbers);
      for (int i = 0; i < numRows1; ++i) {
        int index = i*numRows1 + j;
          if (matrix1[index] != 0) {
              values1.push_back(matrix1[index]);
              rows1.push_back(i);
              notNullNumbers++;
          }
      }
  }
  colPtr1.push_back(notNullNumbers);

  notNullNumbers = 0;
  for (int j = 0; j < numCols2; ++j) {
      colPtr2.push_back(notNullNumbers);
      for (int i = 0; i < numRows2; ++i) {
        int index = i*numRows2 + j;
          if (matrix2[index] != 0) {
              values2.push_back(matrix2[index]);
              rows2.push_back(i);
              notNullNumbers++;
          }
      }
  }
  colPtr2.push_back(notNullNumbers);

  return true;
}

bool TestTaskSequential::validation() {
  internal_order_test();
  return taskData->inputs_count[1] == taskData->inputs_count[2];
}

bool TestTaskSequential::run() {
  internal_order_test();
  
  for (int j = 0; j < numCols2; j++) {
    for (int k = colPtr2[j]; k < colPtr2[j + 1]; k++) {
      int column2 = j;
      int row2 = rows2[k];
      for (int l = colPtr1[row2]; l < colPtr1[row2 + 1]; l++) {
        int row1 = rows1[l];
        double val1 = values1[l];
        double val2 = values2[k];

        int index = row1 * numCols2 + column2;
        result[index] += val1 * val2;
      }
    }
  }
  return true;
}


bool TestTaskSequential::post_processing() {
  internal_order_test();
  return taskData->inputs_count[0] == taskData->outputs_count[0] && 
  taskData->inputs_count[3] == taskData-<outputs_count[1];
}
