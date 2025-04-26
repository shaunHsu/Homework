#include "header.h"
#include <cstddef>   // For size_t
#include <algorithm> // For std::swap

template <class T>
void heapify(T* arr, int n, int i) { // Changed signature (n is current heap size)
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    if (l < n && arr[l] > arr[largest]) {
        largest = l;
    }
    if (r < n && arr[r] > arr[largest]) {
        largest = r;
    }
    if (largest != i) {
        std::swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

template <class T>
void heapSort(T* arr, size_t n) { // Changed signature
    // Build heap (rearrange array)
    for (int i = n / 2 - 1; i >= 0; i--) { // Use int for loop index >= 0 check
        heapify(arr, n, i); // Pass n as current heap size
    }
    // One by one extract an element from heap
    for (int i = n - 1; i >= 0; i--) { // Use int for loop index >= 0 check
        // Move current root to end
        std::swap(arr[0], arr[i]);
        // call max heapify on the reduced heap
        heapify(arr, i, 0); // Pass i as the size of the reduced heap
    }
}

// Explicit instantiation if needed
// template void heapSort<uint16_t>(uint16_t* arr, size_t n);
