#include <vector>
#include <algorithm> // std::copy, std::inplace_merge (或者手動實現 merge)
#include <iostream>   // 用於範例輸出
#include "sort.h"

void hybridMergeSortRecursive(std::vector<int>& arr, int left, int right, const int INSERTION_SORT_THRESHOLD) {
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
        // 或者使用 C++ 標準庫的 inplace_merge (可能更慢，但不需要額外手動分配空間)
        // std::inplace_merge(arr.begin() + left, arr.begin() + mid + 1, arr.begin() + right + 1);
    }
}

// 混合式合併排序的主函式 (使用者呼叫的介面)
void compositeSort(std::vector<int>& arr) {
    if (arr.empty()) {
        return;
    }
    // 設定切換到插入排序的閾值
    const int INSERTION_SORT_THRESHOLD = 32;
    hybridMergeSortRecursive(arr, 0, arr.size() - 1, INSERTION_SORT_THRESHOLD);
}