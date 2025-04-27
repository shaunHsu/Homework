#include "header.h"
#include <vector>    // Include vector header
#include <cstddef>   // For size_t
#include <algorithm> // For std::copy (optional, can use range constructor)

template <typename T>
// Pass vector by reference
void merge(std::vector<T>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Create temporary vectors using range constructors (simpler than new/delete)
    std::vector<T> leftArr(arr.begin() + left, arr.begin() + left + n1);
    std::vector<T> rightArr(arr.begin() + mid + 1, arr.begin() + mid + 1 + n2);

    // --- Merge logic remains the same, using vector indexing ---
    int i = 0, j = 0;
    int k = left; // Index for the main array 'arr'

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

    // Copy remaining elements of leftArr, if any
    while (i < n1) {
        arr[k] = leftArr[i];
        i++;
        k++;
    }

    // Copy remaining elements of rightArr, if any
    while (j < n2) {
        arr[k] = rightArr[j];
        j++;
        k++;
    }
    // No delete[] needed, vectors manage their own memory
}

template <typename T>
// Pass vector by reference
void mergeSort(std::vector<T>& arr, int left, int right) {
    if (left < right) {
        // Finding the middle point
        int mid = left + (right - left) / 2;

        // Sort first and second halves
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        // Merge the sorted halves
        merge(arr, left, mid, right);
    }
}

// Explicit instantiation if needed
// template void mergeSort<uint16_t>(std::vector<uint16_t>& arr, int left, int right);
