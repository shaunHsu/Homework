#include "header.h"
#include <cstdint>   // For uint16_t
#include <numeric>   // For std::iota
#include <algorithm> // For std::reverse
#include <vector>    // Include vector header

// Return a std::vector<uint16_t>
std::vector<uint16_t> genInsertSortWorstCase(uint16_t n) {
    if (n == 0) return {}; // Return an empty vector
    std::vector<uint16_t> arr(n); // Create a vector of size n

    // Fill with 0, 1, ..., n-1
    std::iota(arr.begin(), arr.end(), 0); // Use iterators

    // Reverse the vector
    std::reverse(arr.begin(), arr.end()); // Use iterators

    return arr; // Return the vector by value (move semantics likely apply)
}
