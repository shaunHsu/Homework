#include "header.h"
#include <cstdint>   // For uint16_t
#include <numeric>   // For std::iota (can be replaced)
#include <algorithm> // For std::reverse
#include <new>       // For new

uint16_t* genInsertSortWorstCase(uint16_t n) { // Return pointer
    if (n == 0) return nullptr;
    uint16_t* arr = new uint16_t[n]; // Allocate memory
    // std::iota(arr, arr + n, 0); // std::iota works with pointers too
    // Or replace std::iota with a loop:
    for(uint16_t i = 0; i < n; ++i) {
        arr[i] = i;
    }
    std::reverse(arr, arr + n); // std::reverse works with pointers
    return arr; // Return the pointer
}
