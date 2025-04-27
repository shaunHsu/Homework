#include "header.h"
#include <vector>    // Include vector header
#include <algorithm> // For std::swap

template <class T>
// Pass vector by reference
int partition(std::vector<T>& arr, int left, int right) {
    T pivot = arr[right]; // Pivot element
    int i = left - 1;     // Index of smaller element

    for (int j = left; j <= right - 1; j++) {
        // If current element is smaller than the pivot
        if (arr[j] < pivot) {
            i++; // increment index of smaller element
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[right]);
    return (i + 1);
}

template <class T>
// Pass vector by reference
void quickSort(std::vector<T>& arr, int left, int right) {
    if (left < right) {
        // pi is partitioning index, arr[pi] is now at right place
        int pi = partition(arr, left, right);

        // Separately sort elements before partition and after partition
        quickSort(arr, left, pi - 1);
        quickSort(arr, pi + 1, right);
    }
}

// Explicit instantiation if needed
// template void quickSort<uint16_t>(std::vector<uint16_t>& arr, int left, int right);
