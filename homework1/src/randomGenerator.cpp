#include "header.h"
void randomGenerator(std::vector<int>& arr, bool saveAsFile = false, const std::string& filename = "random_data.txt") {
    if (arr.empty()) {
        return; // 如果向量是空的，則不執行任何操作
    }

    // 1. 使用 std::iota 填充向量為 0, 1, 2, ..., n-1
    std::iota(arr.begin(), arr.end(), 0);

    // 2. 使用 <random> 進行 Fisher-Yates shuffle
    // 創建一個隨機數引擎，並使用目前時間作為種子
    std::mt19937 engine(static_cast<unsigned int>(std::time(nullptr)));
    // 使用引擎進行隨機打亂
    std::shuffle(arr.begin(), arr.end(), engine);

    // 3. (可選) 將產生的資料儲存到檔案
    if (saveAsFile) {
        std::ofstream outfile(filename); // 開啟檔案以供寫入
        if (outfile.is_open()) { // 檢查檔案是否成功開啟
            for (size_t i = 0; i < arr.size(); ++i) {
                outfile << arr[i] << (i == arr.size() - 1 ? "" : " "); // 寫入數字，以空格分隔 (最後一個除外)
            }
            outfile.close(); // 關閉檔案
        } else {
            std::cerr << "錯誤：無法開啟檔案 " << filename << " 進行寫入。" << std::endl;
        }
    }
}