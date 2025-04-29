#include "header.h"
#include "sort.h"

#include "genInsertSortWorstCase.cpp"
#include "genMergeSortWorstCase.cpp"
#include "genRandom.cpp"

using namespace std;

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
        insertionSort(t, 0, t.size() - 1); 
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

        totalTime += duration.count();
    }
    cout << "after insertion sort (worst case) memory info: " << endl;
    size_t after = showMemUsage();
    cout << "insertion sort (worst case) avgerage using: " << totalTime / repeat << "ms" << ", memory usage: " << (after > before ? (after - before) / 1024 : 0) << "KB" << endl; // Avoid potential negative if memory decreased
    cout << "==========================================================" << endl;
}

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
    cout << "merge sort (worst case) avgerage using: "<< totalTime / repeat << "ms"<< ", memory usage: " << (after > before ? (after - before) / 1024 : 0) << "KB" << endl;
    cout << "==========================================================" << endl;
}

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

int main()
{
    // Note: Vector usage might slightly change memory footprint compared to raw arrays.
    uint16_t noe[] = {500, 1000, 2000, 3000, 4000, 5000}; 
    uint16_t repeat = 2000;                                
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
