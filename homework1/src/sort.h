#ifndef SORT_H
#define SORT_H

#include <vector>  // Include vector here as it's used in declarations
#include <cstddef> // For size_t
#include <cstdint> // For uint16_t

// Forward declarations for non-template functions (updated return type)
std::vector<uint16_t> genInsertSortWorstCase(uint16_t n);
std::vector<uint16_t> genMergeSortWorstCase(uint16_t n);
std::vector<uint16_t> genRandom(uint16_t n);

// Template function declarations (updated parameter type)
template <class T>
void insertionSort(std::vector< T>& arr, int left, int right); // Pass by reference

template <class T>
// Pass by reference, indices define the sub-vector range
void quickSort(std::vector<T>& arr, int left, int right);

template <class T>
// Pass by reference, indices define the sub-vector range
void mergeSort(std::vector<T>& arr, int left, int right);

template <class T>
void heapSort(std::vector<T>& arr); // Pass by reference


// Include template implementations (common practice, though not ideal)
// Or compile them separately and link if preferred.
// Keeping original structure for now.
#include "insertionSort.cpp"
#include "quickSort.cpp"
#include "mergeSort.cpp"
#include "heapSort.cpp"


#endif
