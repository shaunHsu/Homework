#include "header.h"
#include <cstdint>   // For uint16_t
#include <numeric>   // For std::iota (can be replaced)
#include <cmath>     // For std::ceil
#include <cstring>   // For memcpy
#include <new>       // For new/delete

// Helper function using C-style arrays
uint16_t* generateWorstCaseRecursive(const uint16_t* sorted_segment, uint16_t n) {
    if (n == 0) {
        return nullptr;
    }
    if (n == 1) {
        uint16_t* result = new uint16_t[1];
        result[0] = sorted_segment[0];
        return result;
    }

    uint16_t n1 = static_cast<uint16_t>(std::ceil(n / 2.0));
    uint16_t n2 = n / 2; // Integer division gives floor

    uint16_t* left_part = new uint16_t[n1];
    uint16_t* right_part = new uint16_t[n2];

    uint16_t l_idx = 0;
    uint16_t r_idx = 0;
    for (uint16_t i = 0; i < n; i++) {
        if (i % 2 == 0) {
            left_part[l_idx++] = sorted_segment[i];
        } else {
            right_part[r_idx++] = sorted_segment[i];
        }
    }

    uint16_t* worst_left = generateWorstCaseRecursive(left_part, n1);
    uint16_t* worst_right = generateWorstCaseRecursive(right_part, n2);

    // We don't need the original parts anymore
    delete[] left_part;
    delete[] right_part;

    uint16_t* result = new uint16_t[n];

    // Combine results using memcpy
    if (worst_left) {
        memcpy(result, worst_left, n1 * sizeof(uint16_t));
        delete[] worst_left; // Free intermediate result
    }
     if (worst_right) {
        memcpy(result + n1, worst_right, n2 * sizeof(uint16_t)); // Copy to position after left part
        delete[] worst_right; // Free intermediate result
    }


    return result;
}

uint16_t* genMergeSortWorstCase(uint16_t n) { // Return pointer
    if (n == 0) {
        return nullptr;
    }

    uint16_t* initial_sorted = new uint16_t[n]; // Allocate
    // std::iota(initial_sorted, initial_sorted + n, 1); // Fill 1, 2, ..., n
     // Or replace std::iota with a loop:
    for(uint16_t i = 0; i < n; ++i) {
        initial_sorted[i] = i + 1;
    }

    uint16_t* result = generateWorstCaseRecursive(initial_sorted, n);

    delete[] initial_sorted; // Free the initial array

    return result; // Return the final worst-case array
}
