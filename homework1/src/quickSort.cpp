#include "header.h"
#include <algorithm> // For std::swap

template <class T>
int partition(T* arr, int left, int right) { // Changed signature
    T pivot = arr[right];
    int i = left - 1;
    for (int j = left; j <= right - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[right]);
    return (i + 1);
}

template <class T>
void quickSort(T* arr, int left, int right) { // Changed signature
    if (left < right) {
        int pivot = partition(arr, left, right);
        quickSort(arr, left, pivot - 1);
        quickSort(arr, pivot + 1, right);
    }
}

// Explicit instantiation if needed
// template void quickSort<uint16_t>(uint16_t* arr, int left, int right);
