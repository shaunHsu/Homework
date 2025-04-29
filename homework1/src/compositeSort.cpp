#include <vector>
#include <algorithm> 
#include <iostream>   
#include "sort.h"

template<class T>
void hybridMergeSortRecursive(std::vector<T>& arr, int left, int right, const int INSERTION_SORT_THRESHOLD) {
    // 基本情況：如果範圍無效或只有一個元素，則已排序
    if (left >= right) {
        return;
    }

    // 優化：如果子陣列大小小於等於閾值，使用插入排序
    if (right - left + 1 <= INSERTION_SORT_THRESHOLD) {
        insertionSort(arr, left, right);
    } else {
        // 否則，繼續使用合併排序的分解步驟
        int mid = left + (right - left) / 2; // 防止溢位

        hybridMergeSortRecursive(arr, left, mid, INSERTION_SORT_THRESHOLD);
        hybridMergeSortRecursive(arr, mid + 1, right, INSERTION_SORT_THRESHOLD);

        // 優化：如果 arr[mid] <= arr[mid+1]，表示兩個子陣列已經自然有序，無需合併
        if (arr[mid] <= arr[mid + 1]) {
           return;
        }

        // 合併兩個已排序的子陣列
        merge(arr, left, mid, right);
    }
}

template<class T>
void compositeSort(std::vector<T>& arr) {
    if (arr.empty()) {
        return;
    }
    const int INSERTION_SORT_THRESHOLD = 32;
    hybridMergeSortRecursive(arr, 0, arr.size() - 1, INSERTION_SORT_THRESHOLD);
}