// Copyright 2024 Petrov Maksim

#include "seq/petrov_m_radix_sort_double_simple_merging/include/ops_seq.hpp"

#include <thread>

using namespace std::chrono_literals;

void countSort(double* in, double* out, int len, int exp) {
    unsigned char* buf = reinterpret_cast<unsigned char*>(in);
    int count[256] = { 0 };
    for (int i = 0; i < len; i++) {
        count[buf[8 * i + exp]]++;
    }
   
    int sum = 0;
    for (int i = 0; i < 256; i++) {
        int temp = count[i];
        count[i] = sum;
        sum += temp;
    }
 
    for (int i = 0; i < len; i++) {
        out[count[buf[8 * i + exp]]] = in[i];
        count[buf[8 * i + exp]]++;
    }
}

bool countSortSigns(double* in, double* out, int len) {
    bool positiveFlag = false, negativeFlag = false;
    int firstNegativeIndex = -1;
    int firstPositiveIndex = -1;
    
    for (int i = 0; i < len; i++) {
        if (positiveFlag && negativeFlag) {
            break;
        }
        if (in[i] < 0 && !negativeFlag) {
            negativeFlag = true;
            firstNegativeIndex = i;
        }
        if (in[i] > 0 && !positiveFlag) {
            positiveFlag = true;
            firstPositiveIndex = i;
        }
    }
    if (positiveFlag && negativeFlag) {
        bool forward = false;
        int j = len - 1;
        for (int i = 0; i < len; i++) {
            out[i] = in[j];
            if (forward) {
                j++;
            }
            else {
                j--;
            }
            if (j == firstNegativeIndex - 1 && !forward) {
                j = 0;
                forward = true;
            }
        }
        return true;
    }
    else if (!positiveFlag) {
        for (int i = len - 1, j = 0; i >= 0; i--, j++) {
            out[j] = in[i];
        }
        return true;
    }
    return false;
}

std::vector<double> radixSort(const std::vector<double>& data) {
    int len = static_cast<int>(data.size());
    std::vector<double> in = data;
    std::vector<double> out(data.size());

    for (int i = 0; i < 4; i++) {
        countSort(in.data(), out.data(), len, 2 * i);
        countSort(out.data(), in.data(), len, 2 * i + 1);
    }
    if (!countSortSigns(in.data(), out.data(), len)) {
        in.swap(out);
    }
   
    return out;
}


bool RadixSortDoubleSequential::pre_processing() {
  internal_order_test(); //для проверки порядка вызова методов
  // Init value for input and output
  try{
  sort = reinterpret_cast<std::vector<double>*>((taskData->inputs[0]));
  data_size = taskData->inputs_count[0];
  }catch(...){
     std::cout<<"\n";
    std::cout<<"Double radix sort error";
    std::cout<<"\n";
    return false;
  }
  return true;
}
bool RadixSortDoubleSequential::validation() {
  internal_order_test();
  // Check count elements of output
  return ((taskData->inputs_count[0] > 1) && (taskData->outputs_count[0] == taskData->inputs_count[0]));
}

bool RadixSortDoubleSequential::run() {
  internal_order_test();
  try{

    for (const double& num : *sort) {
    std::cout << num << " ";
    }
    std::cout<<"\n";
    *sort = radixSort(*sort); 

    for (const double& num : *sort) {
    std::cout << num << " ";
    }
    std::cout<<"\n";
    
  }
  catch(...){
    std::cout<<"\n";
    std::cout<<"Double radix sort error";
    std::cout<<"\n";
    return false;
  }
  return true;
}

bool RadixSortDoubleSequential::post_processing() {
  internal_order_test();
  try{
  *reinterpret_cast<std::vector<double>*>(taskData->outputs[0]) = *sort;
  }
  catch(...){ std::cout<<"\n";
    std::cout<<"Double radix sort error";
    std::cout<<"\n";
    return false;}
  return true;
  
}
