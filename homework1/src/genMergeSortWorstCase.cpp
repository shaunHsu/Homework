#include "header.h"
#include <cstdint>   // For uint16_t
#include <numeric>   // For std::iota
#include <cmath>     // For std::ceil
#include <vector>    // Include vector header
#include <algorithm> // For std::copy, std::back_inserter

// Helper function using std::vector
std::vector<uint16_t> generateWorstCaseRecursive(const std::vector<uint16_t>& sorted_segment) {
    uint16_t n = sorted_segment.size();
    if (n <= 1) {
        return sorted_segment; // Base case: return a copy or the vector itself if n=0 or n=1
    }

    uint16_t n1 = static_cast<uint16_t>(std::ceil(n / 2.0));
    uint16_t n2 = n / 2; // Integer division gives floor

    std::vector<uint16_t> left_part;
    left_part.reserve(n1); // Reserve space for efficiency
    std::vector<uint16_t> right_part;
    right_part.reserve(n2); // Reserve space for efficiency

    // Distribute elements
    for (uint16_t i = 0; i < n; i++) {
        if (i % 2 == 0) {
            left_part.push_back(sorted_segment[i]);
        } else {
            right_part.push_back(sorted_segment[i]);
        }
    }

    // Recursively generate worst cases for sub-problems
    std::vector<uint16_t> worst_left = generateWorstCaseRecursive(left_part);
    std::vector<uint16_t> worst_right = generateWorstCaseRecursive(right_part);

    // Combine results
    std::vector<uint16_t> result;
    result.reserve(n); // Reserve space
    result.insert(result.end(), worst_left.begin(), worst_left.end());
    result.insert(result.end(), worst_right.begin(), worst_right.end());

    return result;
}

// Return a std::vector<uint16_t>
std::vector<uint16_t> genMergeSortWorstCase(uint16_t n) {
    if (n == 0) {
        return {}; // Return empty vector
    }

    std::vector<uint16_t> initial_sorted(n); // Create vector
    std::iota(initial_sorted.begin(), initial_sorted.end(), 1); // Fill 1, 2, ..., n

    // Generate the worst-case sequence recursively
    std::vector<uint16_t> result = generateWorstCaseRecursive(initial_sorted);

    return result; // Return the final worst-case vector
}
