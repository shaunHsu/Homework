#include "header.h"
void genWorstCase(std::vector<uint16_t>& arr) {
    std::iota(arr.begin(), arr.end(), 0);
    std::reverse(arr.begin(), arr.end());
}