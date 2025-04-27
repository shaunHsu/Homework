#include "header.h"
#include "sort.h" // Should now correctly include/declare everything needed

// Include implementations for non-template functions if not linking separately
#include "genInsertSortWorstCase.cpp"
#include "genMergeSortWorstCase.cpp"
#include "genRandom.cpp"

// 需要 <format> 函式庫，確保你的編譯器支援 C++20 或更高版本
// 如果不支援，可以替換為 sprintf 或簡單的 << 輸出
#include <format>
#include <chrono>
#include <vector>

// Windows specific headers for memory monitoring
#include <windows.h>
#include <psapi.h>

using namespace std;

// 定義一個結構體來存放記憶體資訊
struct MemInfo {
    SIZE_T workingSetSize;
    SIZE_T peakWorkingSetSize;
    SIZE_T pagefileUsage; // 也一併包含 pagefile usage
};

// --- Merge Sort Implementation (from previous example, using std::vector) ---

MemInfo showMemUsage(const char* stage)
{
    PROCESS_MEMORY_COUNTERS pmc;
    MemInfo info = {0, 0, 0}; // 初始化

    HANDLE hProcess = GetCurrentProcess();

    if (NULL == hProcess) {
        cerr << "Error: Could not get process handle." << endl;
        return info; // 返回空的結構體
    }

    if (GetProcessMemoryInfo(hProcess, &pmc, sizeof(pmc))) {
        info.workingSetSize = pmc.WorkingSetSize;
        info.peakWorkingSetSize = pmc.PeakWorkingSetSize;
        info.pagefileUsage = pmc.PagefileUsage;

        cout << "----------------------------------------------------------" << endl
             << stage << " Memory Usage Information:" << endl
             << "  Working Set Size    : " << info.workingSetSize / 1024 << " KB" << endl
             << "  Peak Working Set Size : " << info.peakWorkingSetSize / 1024 << " KB" << endl // 顯示 Peak Working Set Size
             << "  Pagefile Usage      : " << info.pagefileUsage / 1024 << " KB" << endl
             << "----------------------------------------------------------" << endl;
    } else {
        cerr << "Error: GetProcessMemoryInfo failed." << endl;
    }

    CloseHandle(hProcess); // 關閉句柄
    return info;
}

// 其他排序測試函式保持不變或類似修改

void mergeSortTest(uint16_t n, uint16_t repeat)
{
    // Get vector (arr) - created once before the repeat loop
    std::vector<uint16_t> arr = genMergeSortWorstCase(n);
    if (arr.empty() && n > 0)
    { // Check if generation failed (returned empty for n>0)
        cout << "Failed to generate data for merge sort test (n=" << n << ")" << endl;
        return;
    }
    if (n == 0)
    { // Handle n=0 case if needed, though sort won't do much
        cout << "Skipping merge sort test for n=0" << endl;
        return;
    }
    cout << format("==============Merge Sort n={:<4d} (worst case) Test=========", n) << endl;

    // --- 測量 1: 迴圈開始前的基線記憶體 ---
    // 這包含了程式、已載入的函式庫、主堆疊以及 arr 的記憶體
    MemInfo before_loop_mem = showMemUsage("Before Repeat Loop");

    long long totalTime = 0;
    MemInfo after_input_copy_mem_first_iter = {0, 0, 0}; // 記錄第一次迴圈的 after input copy 記憶體

    for (uint16_t i = 0; i < repeat; i++)
    {
        // Create a copy (t) - O(N * sizeof(uint16_t)) space created inside the loop
        // 這是每次排序操作的輸入向量，是測試空間複雜度的主要對象
        std::vector<uint16_t> t = arr;

        // --- 測量 2: 複製輸入向量後，排序前 ---
        // 這包含了 arr + t + 其他基線記憶體。t 的大小是 O(N)。
        // 這裡記錄第一次迴圈的狀態，以大致展示輸入向量的空間影響
        if (i == 0) {
             after_input_copy_mem_first_iter = showMemUsage("Inside Loop: After Input Copy (1st iter)");
        }

        auto start = std::chrono::high_resolution_clock::now();
        // Pass vector by reference and bounds
        // Merge Sort 在執行期間會在 merge 函式中使用臨時輔助空間 (O(N))
        mergeSort(t, 0, t.size() - 1); // Sort happens here. Temporary O(N) space used in merge.
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

        totalTime += duration.count();
        // 't' 在此迴圈迭代結束時超出作用域，其記憶體由 std::vector 自動釋放
        // 臨時合併空間 (在 merge 函式內) 在 merge 函式返回時已被釋放
    } // repeat loop ends

    // --- 測量 3: 整個迴圈結束後 ---
    // 每次迴圈內的 t 都已釋放。這裡測量的是迴圈結束後，Peak Working Set 應該記錄了迴圈中達到的最高點。
    MemInfo after_loop_mem = showMemUsage("After Repeat Loop Completed");

    // --- 輸出分析結果 ---
    cout << format("============Summary for n={:<4d}, repeat={:<4d}============", n, repeat) << endl;
    cout << "Time taken (average): " << totalTime / repeat << " ms" << endl;

    cout << "\nMemory Increase Analysis (relative to 'Before Repeat Loop'):" << endl;

    // 分析 Working Set 的增長
    // 工作集的增長反映了在測量點記憶體佔用的變化。由於臨時空間釋放，'After Loop' 可能不高。
    SIZE_T working_set_increase = 0;
    if (after_loop_mem.workingSetSize > before_loop_mem.workingSetSize) {
        working_set_increase = after_loop_mem.workingSetSize - before_loop_mem.workingSetSize;
    }
    cout << "  Working Set Increase (After Loop vs Before Loop): "
         << working_set_increase / 1024 << " KB" << endl;


    // 分析 Peak Working Set 的增長
    // Peak Working Set 記錄的是進程生命週期中工作集達到的最高峰值（直到測量點）。
    // 'After Loop' 的 Peak Working Set 應該包含了 Sorting 期間由於臨時輔助空間分配導致的峰值。
    SIZE_T peak_working_set_increase = 0;
     if (after_loop_mem.peakWorkingSetSize > before_loop_mem.peakWorkingSetSize) {
        peak_working_set_increase = after_loop_mem.peakWorkingSetSize - before_loop_mem.peakWorkingSetSize;
    }
    cout << "  Peak Working Set Increase (After Loop vs Before Loop): "
         << peak_working_set_increase / 1024 << " KB" << endl;
    cout << "  (This Peak increase *roughly* indicates max memory surge during sort, including temporary space)" << endl;


    // 分析第一次迴圈中，創建輸入向量後的記憶體增長 (大致反映輸入資料空間 O(N))
    SIZE_T input_copy_increase_ws = 0;
     if (after_input_copy_mem_first_iter.workingSetSize > before_loop_mem.workingSetSize) {
        input_copy_increase_ws = after_input_copy_mem_first_iter.workingSetSize - before_loop_mem.workingSetSize;
    }
     cout << "  Working Set Increase (After Input Copy, 1st iter vs Before Loop): "
         << input_copy_increase_ws / 1024 << " KB" << endl;
     cout << "  (This reflects the O(N) space for the input vector 't' in one iteration)" << endl;


    cout << "==========================================================" << endl;

    // No delete[] arr needed
}

int main()
{
    // Note: Vector usage might slightly change memory footprint compared to raw arrays.
    // 使用 uint16_t 是 2 Bytes，所以 N 個元素理論上佔用 N * 2 Bytes
    uint16_t noe[] = {500, 1000, 2000, 3000, 4000, 5000, 10000, 20000, 50000}; // 增加 N 的範圍
    uint16_t repeat = 50;                                // 適當調整重複次數以平衡時間和測量穩定性

    // 測量程式運行初期的基線記憶體
    cout << "--- Initial Program Baseline Measurement ---" << endl;
    MemInfo initial_baseline = showMemUsage("Initial Program Baseline");
    cout << "------------------------------------------" << endl;


    for (uint16_t n : noe)
    {
        mergeSortTest(n, repeat);
    }

    // 程式結束前的記憶體狀態
    cout << "\n--- Before Program Exit Measurement ---" << endl;
    showMemUsage("Before Program Exit");
    cout << "-------------------------------------" << endl;

    return 0;
}