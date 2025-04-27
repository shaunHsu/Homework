#include "header.h"
#include <vector>    // Include vector header
#include <cstddef>   // For size_t
#include <algorithm> // For std::swap

template <class T>
// Pass vector by reference, n is the size of the heap (can be less than arr.size())
void heapify(std::vector<T>& arr, int n, int i) {
    int largest = i;       // Initialize largest as root
    int l = 2 * i + 1;     // left = 2*i + 1
    int r = 2 * i + 2;     // right = 2*i + 2

    // If left child is larger than root
    if (l < n && arr[l] > arr[largest])
        largest = l;

    // If right child is larger than largest so far
    if (r < n && arr[r] > arr[largest])
        largest = r;

    // If largest is not root
    if (largest != i) {
        std::swap(arr[i], arr[largest]);

        // Recursively heapify the affected sub-tree
        heapify(arr, n, largest);
    }
}

template <class T>
// Pass vector by reference
void heapSort(std::vector<T>& arr) {
    int n = arr.size(); // Get size from vector

    // Build heap (rearrange array)
    // Start from the last non-leaf node and go up
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i); // n is the total size here

    // One by one extract an element from heap
    for (int i = n - 1; i > 0; i--) { // Loop from n-1 down to 1
        // Move current root to end
        std::swap(arr[0], arr[i]);

        // call max heapify on the reduced heap
        // The size of the heap is now 'i'
        heapify(arr, i, 0);
    }
}

// Explicit instantiation if needed
// template void heapSort<uint16_t>(std::vector<uint16_t>& arr);
