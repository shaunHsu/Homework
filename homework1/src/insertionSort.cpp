#include "header.h"
#include <cstddef> // Include necessary headers directly in cpp files

template <class T>
void insertionSort(T* arr, size_t n) { // Changed signature
    for (size_t i = 1; i < n; i++) {   // Use size_t for index, compare with n
        T v = arr[i];
        int j = i - 1; // Keep j as int for comparison with >= 0
        while (j >= 0 && arr[j] > v) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = v;
    }
}

// Explicit instantiation if needed, or keep in header if included there
// template void insertionSort<uint16_t>(uint16_t* arr, size_t n);
