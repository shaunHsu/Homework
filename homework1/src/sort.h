#ifndef SORT_H
#define SORT_H

#include <vector>  
#include <cstddef> 
#include <cstdint> 
#include "insertionSort.cpp"
#include "quickSort.cpp"
#include "mergeSort.cpp"
#include "heapSort.cpp"
#include "compositeSort.cpp"

template <class T>
void insertionSort(std::vector< T>& arr, int left, int right);

template <class T>
void quickSort(std::vector<T>& arr, int left, int right);

template <class T>
void mergeSort(std::vector<T>& arr, int left, int right);

template <class T>
void heapSort(std::vector<T>& arr); 

template<class T>
void compositeSort(std::vector<T>& arr);

#endif
