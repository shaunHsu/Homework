# 41243225

作業一,組員:41243227

## 解題說明

本題要求分析使用insertion sort, merge sort, quick sort, heap sort四種演算法觀察不同資料長度時的效能,並找出最佳演算法組成一個最佳解方。

### 解題策略

設計四種演算法並測量不同資料長度時的耗時,並找出最佳演算法組成一個最佳解方。
資料內容使用各演算法的worst-case。

## 程式實作

演算法資料使用vector儲存

### Insertion Sort

```c++
#include "header.h"
#include <vector>    
#include <cstddef>   

template <class T>
void insertionSort(std::vector<T>& arr) {
    size_t n = arr.size(); 
    if (n <= 1) return;

    for (size_t i = 1; i < n; i++) {
        T v = arr[i];
        int j = static_cast<int>(i) - 1;
        while (j >= 0 && arr[j] > v) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = v;
    }
}
```

### Merge Sort

```c++
#include "header.h"
#include <vector>    
#include <cstddef>   
#include <algorithm> 

template <typename T>
void merge(std::vector<T>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    std::vector<T> leftArr(arr.begin() + left, arr.begin() + left + n1);
    std::vector<T> rightArr(arr.begin() + mid + 1, arr.begin() + mid + 1 + n2);
    int i = 0, j = 0;
    int k = left;

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
}

template <typename T>
void mergeSort(std::vector<T>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}
```

### Quick Sort

```c++
#include "header.h"
#include <vector>    
#include <algorithm> 

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
        int pi = partition(arr, left, right);

        quickSort(arr, left, pi - 1);
        quickSort(arr, pi + 1, right);
    }
}
```

這裡的快速排序法是用最大的數字當作pivot,而不是用中間的數字當作pivot。

### Heap Sort

```c++
#include "header.h"
#include <vector>   
#include <cstddef>   
#include <algorithm> 

template <class T>
void heapify(std::vector<T>& arr, int n, int i) {
    int largest = i;       
    int l = 2 * i + 1;     
    int r = 2 * i + 2;     

    if (l < n && arr[l] > arr[largest])
        largest = l;
    if (r < n && arr[r] > arr[largest])
        largest = r;
    if (largest != i) {
        std::swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

template <class T>
void heapSort(std::vector<T>& arr) {
    int n = arr.size(); 
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i); 
    for (int i = n - 1; i > 0; i--) { 
        std::swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}
```
#### Composite Sort

```c++
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
```

### 產生測試資料

這裡產生插入排序與合併排序的worst cast資料。</br>
快速排序與堆排序會使用隨機產生的資料。</br>

#### 插入排序

```c++
#include "header.h"
#include <cstdint>   // For uint16_t
#include <numeric>   // For std::iota
#include <algorithm> // For std::reverse
#include <vector>    // Include vector header

// Return a std::vector<uint16_t>
std::vector<uint16_t> genInsertSortWorstCase(uint16_t n) {
    if (n == 0) return {};
    std::vector<uint16_t> arr(n);
    std::iota(arr.begin(), arr.end(), 0); 
    std::reverse(arr.begin(), arr.end()); 

    return arr;
}
```

當呼叫時,會產生一個vector,並將0到n-1的數字填入,然後反轉vector,最後回傳vector。

#### 合併排序

```c++
#include "header.h"
#include <cstdint>   
#include <numeric>   
#include <cmath>     
#include <vector>    
#include <algorithm> 

std::vector<uint16_t> generateWorstCaseRecursive(const std::vector<uint16_t>& sorted_segment) {
    uint16_t n = sorted_segment.size();
    if (n <= 1) {
        return sorted_segment; 
    }

    uint16_t n1 = static_cast<uint16_t>(std::ceil(n / 2.0));
    uint16_t n2 = n / 2; 

    std::vector<uint16_t> left_part;
    left_part.reserve(n1);
    std::vector<uint16_t> right_part;
    right_part.reserve(n2); 
    for (uint16_t i = 0; i < n; i++) {
        if (i % 2 == 0) {
            left_part.push_back(sorted_segment[i]);
        } else {
            right_part.push_back(sorted_segment[i]);
        }
    }

    std::vector<uint16_t> worst_left = generateWorstCaseRecursive(left_part);
    std::vector<uint16_t> worst_right = generateWorstCaseRecursive(right_part);

    std::vector<uint16_t> result;
    result.reserve(n);
    result.insert(result.end(), worst_left.begin(), worst_left.end());
    result.insert(result.end(), worst_right.begin(), worst_right.end());

    return result;
}

std::vector<uint16_t> genMergeSortWorstCase(uint16_t n) {
    if (n == 0) {
        return {}; 
    }

    std::vector<uint16_t> initial_sorted(n); 
    std::iota(initial_sorted.begin(), initial_sorted.end(), 1); 
    std::vector<uint16_t> result = generateWorstCaseRecursive(initial_sorted);

    return result; 
}
```

將合併排序法過程相反，產生worst case。

#### 產生隨機資料

```c++
#include "header.h"
#include <cstdint>   
#include <numeric>   
#include <algorithm> 
#include <random>    
#include <chrono>    
#include <vector>    

std::vector<uint16_t> genRandom(uint16_t n){
    if (n == 0) return {}; 
    std::vector<uint16_t> arr(n); 

    std::iota(arr.begin(), arr.end(), 0); 
    unsigned seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    std::mt19937 engine(seed);
    std::shuffle(arr.begin(), arr.end(), engine); 

    return arr; 
}

```

產生一個vector,並將0到n-1的數字填入,然後用std::shuffle隨機打亂vector,最後回傳vector。

### 主程式

使用上述方法產生對應的測試資料</br>
在每次排序前先複製一次測試資料,以免測資被更改</br>
開始前會測試一次目前記憶體使用情況</br>
在排序後會再一次測試記憶體使用情況</br>
並在輸出附上記憶體使用情況的資訊，單位為KB</br>
時間測試時只包含排序過程的所需時間</br>
每次測試會重複repeat次</br>
在插入與合併時會取平均時間</br>
在快速與堆排序時會取最大時間</br>
以下是測試單元範例程式</br>

#### 插入排序測試單元

```c++
void insertionSortTest(uint16_t n, uint16_t repeat)
{
    std::vector<uint16_t> arr = genInsertSortWorstCase(n);
    if (arr.empty() && n > 0)
    { 
        cout << "Failed to generate data for insertion sort test (n=" << n << ")" << endl;
        return;
    }
    if (n == 0)
    { 
        cout << "Skipping insertion sort test for n=0" << endl;
        return;
    }
    cout << format("============Insertion Sort n={:<4d} (worst case) Test=======", n) << endl;
    cout << "before insertion sort (worst case) memory info: " << endl;
    size_t before = showMemUsage();
    long long totalTime = 0;
    for (uint16_t i = 0; i < repeat; i++)
    {
        std::vector<uint16_t> t = arr;

        auto start = std::chrono::high_resolution_clock::now();
        insertionSort(t);
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

        totalTime += duration.count();
    }
    cout << "after insertion sort (worst case) memory info: " << endl;
    size_t after = showMemUsage();
    cout << "insertion sort (worst case) avgerage using: " << totalTime / repeat << "ms" << ", memory usage: " << (after > before ? (after - before) / 1024 : 0) << "KB" << endl; 
    cout << "==========================================================" << endl;
}
```

#### 合併排序測試單元

```c++
void mergeSortTest(uint16_t n, uint16_t repeat)
{
    std::vector<uint16_t> arr = genMergeSortWorstCase(n);
    if (arr.empty() && n > 0)
    {
        cout << "Failed to generate data for merge sort test (n=" << n << ")" << endl;
        return;
    }
    if (n == 0)
    {
        cout << "Skipping merge sort test for n=0" << endl;
        return;
    }
    cout << format("==============Merge Sort n={:<4d} (worst case) Test=========", n) << endl;
    cout << "before merge sort (worst case) memory info: " << endl;
    size_t before = showMemUsage();
    long long totalTime = 0;
    for (uint16_t i = 0; i < repeat; i++)
    {
        std::vector<uint16_t> t = arr;

        auto start = std::chrono::high_resolution_clock::now();
        mergeSort(t, 0, t.size() - 1);
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

        totalTime += duration.count();
    }
    cout << "after merge sort (worst case) memory info: " << endl;
    size_t after = showMemUsage();
    cout << "merge sort (worst case) avgerage using: " << totalTime / repeat << "ms" << ", memory usage: " << (after > before ? (after - before) / 1024 : 0) << "KB" << endl;
    cout << "==========================================================" << endl;
}
```

#### 快速排序測試單元

```c++
void quickSortTest(uint16_t n, uint16_t repeat)
{
    if (n == 0)
    {
        cout << "Skipping quick sort test for n=0" << endl;
        return;
    }
    cout << format("==============Quick Sort n={:<4d} (worst case) Test=========", n) << endl;
    cout << "before quick sort (worst case) memory info: " << endl;
    size_t before = showMemUsage();
    long long longestTime = 0;
    for (uint16_t i = 0; i < repeat; i++)
    {
        std::vector<uint16_t> arr = genRandom(n);
        if (arr.empty() && n > 0)
        {
            cout << "Failed to generate data for quick sort test (n=" << n << ", iter=" << i << ")" << endl;
            continue; 
        }
        if (arr.empty())
            continue; 

        auto start = std::chrono::high_resolution_clock::now();
        quickSort(arr, 0, arr.size() - 1);
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

        if (duration.count() > longestTime)
            longestTime = duration.count();
    }
    cout << "after quick sort (worst case) memory info: " << endl;
    size_t after = showMemUsage();
    cout << "quick sort (longest random case) using: " << longestTime << "ms" << ", memory usage: " << (after > before ? (after - before) / 1024 : 0) << "KB" << endl;
    cout << "==========================================================" << endl;
}
```

#### 堆排序測試單元

```c++
void heapSortTest(uint16_t n, uint16_t repeat)
{
    if (n == 0)
    {
        cout << "Skipping heap sort test for n=0" << endl;
        return;
    }
    cout << format("===============Heap Sort n={:<4d} (worst case) Test=========", n) << endl;
    cout << "before heap sort (worst case) memory info: " << endl;
    size_t before = showMemUsage();
    long long longestTime = 0; calculate average
    for (uint16_t i = 0; i < repeat; i++)
    {
        std::vector<uint16_t> arr = genRandom(n);
        if (arr.empty() && n > 0)
        {
            cout << "Failed to generate data for heap sort test (n=" << n << ", iter=" << i << ")" << endl;
            continue; 
        }
        if (arr.empty())
            continue; 

        auto start = std::chrono::high_resolution_clock::now();
        heapSort(arr); 
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

        if (duration.count() > longestTime)
            longestTime = duration.count();
    }
    cout << "after heap sort (worst case) memory info: " << endl;
    size_t after = showMemUsage();
    cout << "heap sort (longest random case) using: " << longestTime << "ms" << ", memory usage: " << (after > before ? (after - before) / 1024 : 0) << "KB" << endl;
    cout << "==========================================================" << endl;
}
```

#### 混和排序測試單元

```c++
void compositeSortTest(uint16_t n, uint16_t repeat)
{
    if (n == 0)
    {
        cout << "Skipping heap sort test for n=0" << endl;
        return;
    }
    cout << format("===========Composite Sort n={:<4d} (worst case) Test========", n) << endl;
    cout << "before heap sort (worst case) memory info: " << endl;
    size_t before = showMemUsage();
    long long longestTime = 0;
    for (uint16_t i = 0; i < repeat; i++)
    {
        std::vector<uint16_t> arr = genRandom(n);
        if (arr.empty() && n > 0)
        {
            cout << "Failed to generate data for heap sort test (n=" << n << ", iter=" << i << ")" << endl;
            continue;
        }
        if (arr.empty())
            continue;

        auto start = std::chrono::high_resolution_clock::now();
        compositeSort(arr); 
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

        if (duration.count() > longestTime)
            longestTime = duration.count();
    }
    cout << "after heap sort (worst case) memory info: " << endl;
    size_t after = showMemUsage();
    cout << "heap sort (longest random case) using: " << longestTime << "ms" << ", memory usage: " << (after > before ? (after - before) / 1024 : 0) << "KB" << endl;
    cout << "==========================================================" << endl;
}
```

#### 記憶體資訊顯示

```c++
size_t showMemUsage()
{
    PROCESS_MEMORY_COUNTERS memInfo;
    GetProcessMemoryInfo(GetCurrentProcess(), &memInfo, sizeof(memInfo));
    cout << "----------------------------------------------------------" << endl
         << "Memory Usage Information:" << endl
         << "Working Set Size: " << memInfo.WorkingSetSize / 1024 << " KB" << endl
         << "Peak Working Set Size: " << memInfo.PeakWorkingSetSize / 1024 << " KB" << endl
         << "Pagefile Usage: " << memInfo.PagefileUsage / 1024 << " KB" << endl
         << "----------------------------------------------------------" << endl;
    return memInfo.WorkingSetSize;
}
```

#### main 函式

```c++
int main()
{
    uint16_t noe[] = {500, 1000, 2000, 3000, 4000, 5000};
    uint16_t repeat = 1000;
    for (uint16_t n : noe)
    {
        insertionSortTest(n, repeat);
        mergeSortTest(n, repeat);
        quickSortTest(n, repeat);
        heapSortTest(n, repeat);

        compositeSortTest(n,repeat);
    }
    showMemUsage();
    return 0;
}
```

## 效能分析

在測試中,我們分析了四種排序演算法在worst case的效能,包括插入排序、合併排序、快速排序和堆排序。

### 時間複雜度

Insertion Sort = O(n^2) </br>
Merge Sort = O(nlogn) </br>
Quick Sort = O(n^2) </br>
Heap Sort = O(nlogn) </br>

### 空間複雜度

Insertion Sort = O(1) </br>
Merge Sort = O(n) </br>
Quick Sort = O(n) </br>
Heap Sort = O(1) </br>

## 測試與驗證

測試環境使用windows</br>
使用power shell 5.7.1執行</br>
使用c++23標準</br>

```shell
$ g++ -std=c++23 main.cpp -o main.exe
$ ./main.exe > result.txt
```

測試結果請參考result1.txt</br>
將result1.txt整理如下</br>

### 排序時間計時

| n    | Insertion Sort | Merge Sort | Quick Sort | Heap Sort |
| :--- | :------------- | :--------- | :--------- | :-------- |
| 500  | 0              | 0          | 0          | 1         |
| 1000 | 2              | 0          | 0          | 0         |
| 2000 | 10             | 0          | 0          | 1         |
| 3000 | 25             | 1          | 1          | 1         |
| 4000 | 45             | 1          | 1          | 2         |
| 5000 | 69             | 1          | 2          | 2         |

本表格記錄了四種排序演算法在不同資料量 (n) 下的執行時間。時間單位為毫秒 (ms)。

Insertion Sort 與 Merge Sort 的時間是使用其 worst-case 輸入資料，重複執行 2000 次所得的平均執行時間。
Quick Sort (longest random case) 與 Heap Sort (longest random case) 的時間則是使用隨機產生的資料，重複執行 2000 次，並記錄其中最長的一次執行時間。

![](https://github.com/shaunHsu/DSHomework/blob/main/homework1/src/a.png)

在上表和折線圖中可以看到，Insertion Sort 在小資料量的情況下表現良好，但在大資料量的情況下表現不佳成，整體為指數成長O(n^2)。

heap sort 在 n=1000 時表現最好，整體符合O(nlogn)。

其餘兩個演算法因計時器精度不夠，無法得出精確結果。

### 結論

在測試中，我們分析了四種排序演算法在worst case的效能,並找出最佳演算法組成一個最佳解方。當n<500時使用插入排序會更快速，當n>500時使用合併排序會更快速。綜合結果寫出的混和排序請參考compositeSort.cpp

| n    | Composite Sort |
| :--- | :------------- |
| 500  | 0 |
| 1000 | 0 |
| 2000 | 0 |
| 3000 | 0 |
| 4000 | 0 |
| 5000 | 0 |

上方表格中是排序的結果，資料採用隨機測資，每個長度重複2000次，取最大值。可以看到全部都小於1ms。

## 申論及開發報告

從上述測試結果可見，由於時鐘精度為毫秒（ms）級，不足以精準捕捉細微的時間差異。若要觀察到顯著差異，需要增加測試數據量，或採用更高精度的計時工具。另一種更為穩定的評估方法是計算執行步驟數，這可以有效避免系統因素對結果造成的影響。

本次測試中，我們以 vector 作為測試數據的載體。雖然 vector 在變更長度與空間管理方面提供了便利性，然而其內部實現可能為了優化效能而引入問題。例如，為提升效率，vector 可能會向系統申請超過實際需求的備用空間（預留容量），或是在超出其作用域後暫時不立即釋放未使用的記憶體。這會導致測試中對記憶體使用量的測量產生嚴重誤差，同時，這些操作也可能對計時結果造成潛在的影響。
