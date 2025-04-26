#ifndef SORT_H
#define SORT_H

#include <cstddef> // For size_t
#include <cstdint> // For uint16_t

// Forward declarations for non-template functions
uint16_t* genInsertSortWorstCase(uint16_t n);
uint16_t* genMergeSortWorstCase(uint16_t n);
uint16_t* genRandom(uint16_t n);

// Template function declarations
template <class T>
void insertionSort(T* arr, size_t n);

template <class T>
void quickSort(T* arr, int left, int right); // Size implicit via left/right after initial call

template <class T>
void mergeSort(T* arr, int left, int right); // Size implicit via left/right after initial call

template <class T>
void heapSort(T* arr, size_t n);


// Include template implementations (common practice, though not ideal)
// Or compile them separately and link if preferred.
// Keeping original structure for now.
#include "insertionSort.cpp"
#include "quickSort.cpp"
#include "mergeSort.cpp"
#include "heapSort.cpp"


#endif
