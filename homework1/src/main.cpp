#include "header.h"
#include "sort.h" // Should now correctly include/declare everything needed

// Include implementations for non-template functions if not linking separately
#include "genInsertSortWorstCase.cpp"
#include "genMergeSortWorstCase.cpp"
#include "genRandom.cpp"


using namespace std;

size_t showMemUsage()
{
    PROCESS_MEMORY_COUNTERS memInfo;
    GetProcessMemoryInfo(GetCurrentProcess(), &memInfo, sizeof(memInfo));
    cout << "----------------------------------------------------------" << endl;
    cout << "Memory Usage Information:" << endl;
    cout << "Working Set Size: " << memInfo.WorkingSetSize / 1024 << " KB" << endl;
    cout << "Peak Working Set Size: " << memInfo.PeakWorkingSetSize / 1024 << " KB" << endl;
    cout << "Pagefile Usage: " << memInfo.PagefileUsage / 1024 << " KB" << endl;
    cout << "----------------------------------------------------------" << endl;
    return memInfo.WorkingSetSize;
}

void insertionSortTest(uint16_t n, uint16_t repeat)
{
    uint16_t* arr = genInsertSortWorstCase(n); // Get pointer
    if (!arr) {
        cout << "Failed to generate data for insertion sort test (n=" << n << ")" << endl;
        return;
    }
    cout << format("============Insertion Sort n={:<4d} (worst case) Test=======", n) << endl;
    cout << "before insertion sort (worst case) memory info: " << endl;
    size_t before = showMemUsage();
    long long totalTime = 0;
    for (uint16_t i = 0; i < repeat; i++)
    {
        // Create a copy using C-style array
        uint16_t* t = new uint16_t[n];
        memcpy(t, arr, n * sizeof(uint16_t));

        auto start = std::chrono::high_resolution_clock::now();
        insertionSort(t, n); // Pass pointer and size
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

        totalTime += duration.count();
        delete[] t; // Free the copy
    }
    cout << "after insertion sort (worst case) memory info: " << endl;
    size_t after = showMemUsage();
    cout << "insertion sort (worst case) avgerage using: " << totalTime / repeat << "ms" << ", memory usage: " << (after > before ? (after - before) / 1024 : 0) << "KB" << endl; // Avoid potential negative if memory decreased
    cout << "==========================================================" << endl;
    delete[] arr; // Free the original generated array
}

void mergeSortTest(uint16_t n, uint16_t repeat)
{
    uint16_t* arr = genMergeSortWorstCase(n); // Get pointer
     if (!arr) {
        cout << "Failed to generate data for merge sort test (n=" << n << ")" << endl;
        return;
    }
    cout << format("==============Merge Sort n={:<4d} (worst case) Test=========", n) << endl;
    cout << "before merge sort (worst case) memory info: " << endl;
    size_t before = showMemUsage();
    long long totalTime = 0;
    for (uint16_t i = 0; i < repeat; i++)
    {
        // Create a copy
        uint16_t* t = new uint16_t[n];
        memcpy(t, arr, n * sizeof(uint16_t));

        auto start = std::chrono::high_resolution_clock::now();
        mergeSort(t, 0, n - 1); // Pass pointer and bounds
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

        totalTime += duration.count();
        delete[] t; // Free the copy
    }
    cout << "after merge sort (worst case) memory info: " << endl;
    size_t after = showMemUsage();
    cout << "merge sort (worst case) avgerage using: " << totalTime / repeat << "ms" << ", memory usage: " << (after > before ? (after - before) / 1024 : 0) << "KB" << endl;
    cout << "==========================================================" << endl;
    delete[] arr; // Free the original
}

void quickSortTest(uint16_t n, uint16_t repeat)
{
    // Generate random data inside the loop for quick sort worst-case (often random)
    cout << format("==============Quick Sort n={:<4d} (worst case) Test=========", n) << endl;
    cout << "before quick sort (worst case) memory info: " << endl;
    size_t before = showMemUsage();
    long long longestTime = 0;
    for (uint16_t i = 0; i < repeat; i++)
    {
        uint16_t* arr = genRandom(n); // Generate inside loop
        if (!arr) {
            cout << "Failed to generate data for quick sort test (n=" << n << ", iter=" << i << ")" << endl;
            continue; // Skip this iteration
        }

        auto start = std::chrono::high_resolution_clock::now();
        quickSort(arr, 0, n - 1); // Pass pointer and bounds
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

        if(duration.count() > longestTime) longestTime = duration.count();
        delete[] arr; // Free array generated in this iteration
    }
    cout << "after quick sort (worst case) memory info: " << endl;
    size_t after = showMemUsage();
    // Note: Quick sort worst case isn't guaranteed by random data, but often measured this way.
    // The time reported is the longest observed time over 'repeat' random trials.
    cout << "quick sort (longest random case) using: " << longestTime << "ms" << ", memory usage: " << (after > before ? (after - before) / 1024 : 0) << "KB" << endl;
    cout << "==========================================================" << endl;
}

void heapSortTest(uint16_t n, uint16_t repeat)
{
    // Generate random data inside the loop (Heap sort worst/average are similar O(n log n))
    cout << format("===============Heap Sort n={:<4d} (worst case) Test=========", n) << endl;
    cout << "before heap sort (worst case) memory info: " << endl;
    size_t before = showMemUsage();
    long long longestTime = 0; // Or use totalTime / repeat for average
    // long long totalTime = 0; // Alternative: calculate average
    for (uint16_t i = 0; i < repeat; i++)
    {
        uint16_t* arr = genRandom(n); // Generate inside loop
         if (!arr) {
            cout << "Failed to generate data for heap sort test (n=" << n << ", iter=" << i << ")" << endl;
            continue; // Skip this iteration
        }

        auto start = std::chrono::high_resolution_clock::now();
        heapSort(arr, n); // *** CORRECTED: Call heapSort, pass pointer and size ***
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

        if(duration.count() > longestTime) longestTime = duration.count(); // Keep track of longest
        // totalTime += duration.count(); // Alternative: sum for average

        delete[] arr; // Free array generated in this iteration
    }
    cout << "after heap sort (worst case) memory info: " << endl;
    size_t after = showMemUsage();
    // Reporting longest time observed on random data. Average might also be interesting.
    cout << "heap sort (longest random case) using: " << longestTime << "ms" << ", memory usage: " << (after > before ? (after - before) / 1024 : 0) << "KB" << endl;
    // cout << "heap sort (average random case) using: " << totalTime / repeat << "ms" << ", memory usage: " << (after > before ? (after - before) / 1024 : 0) << "KB" << endl; // Alternative output
    cout << "==========================================================" << endl;
}

int main()
{
    // Note: Larger N might require significant memory and time with C-style arrays
    // especially with frequent allocations/deallocations in loops.
    uint16_t noe[] = {500, 1000, 2000, 3000, 4000, 5000}; // Keep N moderate
    uint16_t repeat = 100; // Reduce repeat count if it's too slow
    for (uint16_t n : noe)
    {
        //insertionSortTest(n, repeat);
        //mergeSortTest(n, repeat);
        quickSortTest(n, repeat);
        //heapSortTest(n, repeat);
    }
    return 0;
}
