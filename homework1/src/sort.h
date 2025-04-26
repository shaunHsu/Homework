#ifndef SORT_H
#define SORT_H

#include "insertionSort.cpp"
#include "quickSort.cpp"
#include "mergeSort.cpp"
#include "heapSort.cpp"
#include "genWrostCase.cpp"

template <class T>
void insertionSort(std::vector<T>& arr);

template <class T>
void quickSort(std::vector<T>& arr, int left, int right);

template <class T>
void mergeSort(std::vector<T>& arr, int left, int right);

template <class T>
void heapSort(std::vector<T>& arr);

void genWorstCase(std::vector<int>& arr) ;

#endif