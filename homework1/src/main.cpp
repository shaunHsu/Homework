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
    // Get vector
    std::vector<uint16_t> arr = genInsertSortWorstCase(n);
    if (arr.empty() && n > 0)
    { // Check if generation failed (returned empty for n>0)
        cout << "Failed to generate data for insertion sort test (n=" << n << ")" << endl;
        return;
    }
    if (n == 0)
    { // Handle n=0 case if needed, though sort won't do much
        cout << "Skipping insertion sort test for n=0" << endl;
        return;
    }
    cout << format("============Insertion Sort n={:<4d} (worst case) Test=======", n) << endl;
    cout << "before insertion sort (worst case) memory info: " << endl;
    size_t before = showMemUsage();
    long long totalTime = 0;
    for (uint16_t i = 0; i < repeat; i++)
    {
        // Create a copy using vector's copy constructor
        std::vector<uint16_t> t = arr;

        auto start = std::chrono::high_resolution_clock::now();
        insertionSort(t); // Pass vector by reference
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

        totalTime += duration.count();
        // No delete[] t needed
    }
    cout << "after insertion sort (worst case) memory info: " << endl;
    size_t after = showMemUsage();
    cout << "insertion sort (worst case) avgerage using: " << totalTime / repeat << "ms" << ", memory usage: " << (after > before ? (after - before) / 1024 : 0) << "KB" << endl; // Avoid potential negative if memory decreased
    cout << "==========================================================" << endl;
    // No delete[] arr needed
}

void mergeSortTest(uint16_t n, uint16_t repeat)
{
    // Get vector
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
        // Create a copy
        std::vector<uint16_t> t = arr;

        auto start = std::chrono::high_resolution_clock::now();
        // Pass vector by reference and bounds
        mergeSort(t, 0, t.size() - 1);
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

        totalTime += duration.count();
        // No delete[] t needed
    }
    cout << "after merge sort (worst case) memory info: " << endl;
    size_t after = showMemUsage();
    cout << "merge sort (worst case) avgerage using: " << totalTime / repeat << "ms" << ", memory usage: " << (after > before ? (after - before) / 1024 : 0) << "KB" << endl;
    cout << "==========================================================" << endl;
    // No delete[] arr needed
}

void quickSortTest(uint16_t n, uint16_t repeat)
{
    // Generate random data inside the loop for quick sort worst-case (often random)
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
        // Generate vector inside loop
        std::vector<uint16_t> arr = genRandom(n);
        if (arr.empty() && n > 0)
        {
            cout << "Failed to generate data for quick sort test (n=" << n << ", iter=" << i << ")" << endl;
            continue; // Skip this iteration
        }
        if (arr.empty())
            continue; // Skip if n=0 generated empty vector

        auto start = std::chrono::high_resolution_clock::now();
        // Pass vector by reference and bounds
        quickSort(arr, 0, arr.size() - 1);
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

        if (duration.count() > longestTime)
            longestTime = duration.count();
        // No delete[] arr needed
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
    if (n == 0)
    {
        cout << "Skipping heap sort test for n=0" << endl;
        return;
    }
    cout << format("===============Heap Sort n={:<4d} (worst case) Test=========", n) << endl;
    cout << "before heap sort (worst case) memory info: " << endl;
    size_t before = showMemUsage();
    long long longestTime = 0; // Or use totalTime / repeat for average
    // long long totalTime = 0; // Alternative: calculate average
    for (uint16_t i = 0; i < repeat; i++)
    {
        // Generate vector inside loop
        std::vector<uint16_t> arr = genRandom(n);
        if (arr.empty() && n > 0)
        {
            cout << "Failed to generate data for heap sort test (n=" << n << ", iter=" << i << ")" << endl;
            continue; // Skip this iteration
        }
        if (arr.empty())
            continue; // Skip if n=0 generated empty vector

        auto start = std::chrono::high_resolution_clock::now();
        heapSort(arr); // Pass vector by reference
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

        if (duration.count() > longestTime)
            longestTime = duration.count(); // Keep track of longest
        // totalTime += duration.count(); // Alternative: sum for average

        // No delete[] arr needed
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
    // Note: Vector usage might slightly change memory footprint compared to raw arrays.
    uint16_t noe[] = {500, 1000, 2000, 3000, 4000, 5000}; // Keep N moderate
    uint16_t repeat = 5000;                                // Reduce repeat count if it's too slow
    for (uint16_t n : noe)
    {
        insertionSortTest(n, repeat);
        mergeSortTest(n, repeat);
        quickSortTest(n, repeat);
        heapSortTest(n, repeat);
    }
    showMemUsage();
    return 0;
}
