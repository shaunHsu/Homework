#include "header.h"

template <class T>
int partition(std::vector<T>& arr, int left, int right) {
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
void quickSort(std::vector<T>& arr, int left, int right) {  
    if (left < right) {
        int pivot = partition(arr, left, right);
        quickSort(arr, left, pivot - 1);
        quickSort(arr, pivot + 1, right);
    }
}
