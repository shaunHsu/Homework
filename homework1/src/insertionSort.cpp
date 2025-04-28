#include "header.h"
#include <vector>    // Include vector header
#include <cstddef>   // For size_t (though vector::size_type is preferred)

template <class T>
// Pass vector by reference to modify it
void insertionSort(std::vector< T>& arr, int left, int right) {
    for (int i = left + 1; i <= right; ++i) {
         T key = arr[i];
        int j = i - 1;
        // 將比 key 大的元素向後移動
        while (j >= left && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key; // 插入 key 到正確位置
    }
}

// Explicit instantiation if needed (usually not required if included via header)
// template void insertionSort<uint16_t>(std::vector<uint16_t>& arr);
