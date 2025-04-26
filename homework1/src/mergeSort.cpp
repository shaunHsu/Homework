#include "header.h"
#include <cstddef> // For size_t
#include <new>     // For new/delete

template <typename T>
void merge(T* arr, int left, int mid, int right) { // Changed signature
  int n1 = mid - left + 1;
  int n2 = right - mid;

  // Allocate C-style arrays
  T* leftArr = new T[n1];
  T* rightArr = new T[n2];

  // Copy data to temp arrays
  for (int i = 0; i < n1; i++) {
    leftArr[i] = arr[left + i];
  }
  for (int j = 0; j < n2; j++) {
    rightArr[j] = arr[mid + 1 + j];
  }

  int i = 0, j = 0, k = left;
  while (i < n1 && j < n2) {
    if (leftArr[i] <= rightArr[j]) {
      arr[k] = leftArr[i];
      i++;
    } else {
      arr[k] = rightArr[j];
      j++;
    }
    k++;
  }

  while (i < n1) {
    arr[k] = leftArr[i];
    i++;
    k++;
  }

  while (j < n2) {
    arr[k] = rightArr[j];
    j++;
    k++;
  }

  // Deallocate memory
  delete[] leftArr;
  delete[] rightArr;
}

template <typename T>
void mergeSort(T* arr, int left, int right) { // Changed signature
  if (left < right) {
    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
  }
}

// Explicit instantiation if needed
// template void mergeSort<uint16_t>(uint16_t* arr, int left, int right);
