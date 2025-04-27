#include "header.h"
#include <vector>    // Include vector header
#include <cstddef>   // For size_t (though vector::size_type is preferred)

template <class T>
// Pass vector by reference to modify it
void insertionSort(std::vector<T>& arr) {
    size_t n = arr.size(); // Get size from vector
    if (n <= 1) return; // Nothing to sort

    for (size_t i = 1; i < n; i++) {
        T v = arr[i];
        // Use long long or ptrdiff_t for j if size_t can exceed int max,
        // or rewrite loop condition carefully. int is usually fine here.
        int j = static_cast<int>(i) - 1;
        while (j >= 0 && arr[j] > v) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = v;
    }
}

// Explicit instantiation if needed (usually not required if included via header)
// template void insertionSort<uint16_t>(std::vector<uint16_t>& arr);
