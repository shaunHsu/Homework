#include "header.h"

template <class T>
void insertionSort(std::vector<T>& arr) {
    for (int i = 1; i < arr.size(); i++) {
        T v = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > v) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = v;
    }
}