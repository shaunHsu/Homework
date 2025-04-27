#include "header.h"
#include <cstdint>   // For uint16_t
#include <numeric>   // For std::iota
#include <algorithm> // For std::shuffle
#include <random>    // For std::mt19937
#include <chrono>    // For seed
#include <vector>    // Include vector header

// Return a std::vector<uint16_t>
std::vector<uint16_t> genRandom(uint16_t n){
    if (n == 0) return {}; // Return empty vector
    std::vector<uint16_t> arr(n); // Create vector

    // 1. Fill with 0, 1, ..., n-1
    std::iota(arr.begin(), arr.end(), 0); // Use iterators

    // 2. Fisher-Yates shuffle
    unsigned seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    std::mt19937 engine(seed);
    std::shuffle(arr.begin(), arr.end(), engine); // Use iterators

    return arr; // Return the vector
}
