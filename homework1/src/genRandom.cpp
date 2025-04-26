#include "header.h"
#include <cstdint>   // For uint16_t
#include <numeric>   // For std::iota (can be replaced)
#include <algorithm> // For std::shuffle
#include <random>    // For std::mt19937
#include <chrono>    // For seed
#include <new>       // For new

uint16_t* genRandom(uint16_t n){ // Return pointer
    if (n == 0) return nullptr;
    uint16_t* arr = new uint16_t[n]; // Allocate memory

    // 1. Fill with 0, 1, ..., n-1
    // std::iota(arr, arr + n, 0); // std::iota works with pointers
    // Or replace std::iota with a loop:
    for(uint16_t i = 0; i < n; ++i) {
        arr[i] = i;
    }

    // 2. Fisher-Yates shuffle
    unsigned seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    std::mt19937 engine(seed);
    std::shuffle(arr, arr + n, engine); // std::shuffle works with pointers

    return arr; // Return the pointer
}
