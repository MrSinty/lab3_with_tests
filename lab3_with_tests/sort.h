#pragma once

#include <iostream>
#include <utility> 

const int INSERTION_SORT_THRESHOLD = 22;

template <typename T>
void swap_(T& a, T& b) //TODO вместо swap использовать вариант с shift или типа того, вместо темпа там что-то сохранять
{
    T temp = std::move(a);
    a = std::move(b);
    b = std::move(temp);
}

template <typename T, typename Compare>
void insertionSort(T* first, T* last, Compare comp) {
    for (T* i = first + 1; i < last; ++i) {
        T temp = std::move(*i);
        T* j = i;
        while (j > first && comp(temp, *(j - 1))) {
            *j = std::move(*(j - 1));
            --j;
        }
        *j = std::move(temp);
    }
}

template <typename T, typename Compare>
T& medianOfThree(T* first, T* mid, T* last, Compare comp) {
    if (comp(*mid, *first)) swap_(*mid, *first);
    if (comp(*(last - 1), *first)) swap_(*(last - 1), *first);
    if (comp(*(last - 1), *mid)) swap_(*(last - 1), *mid);
    return *mid;
}

template <typename T, typename Compare>
T* partition(T* first, T* last, Compare comp) {

    T* middle = first + (last - first) / 2;
    T& pivot = medianOfThree(first, middle, last, comp);

    T* left = first;
    T* right = last - 1;

    while (left <= right) {
        while (comp(*left, pivot)) left++;
        while (comp(pivot, *right)) right--;
        if (left <= right) {
            swap_(*left, *right);
            left++;
            right--;
        }
    }
    return right;
}

template <typename T, typename Compare>
void quickSort(T* first, T* last, Compare comp) {
    if (first < last) {
        if (last - first <= INSERTION_SORT_THRESHOLD) {
            insertionSort(first, last, comp);
            return;
        }

        T* pivot = partition(first, last, comp);

        if (pivot - first < last - (pivot + 1)) {
            quickSort(first, pivot, comp);
            first = pivot + 1;
        }
        else {
            quickSort(pivot + 1, last, comp);
            last = pivot;
        }
    }
}

template <typename T, typename Compare>
void simpleQuickSort(T* first, T* last, Compare comp) {
    if (first < last - 1) {
        T* pivot = partition(first, last, comp);
        simpleQuickSort(first, pivot, comp);
        if (pivot - first < last - (pivot + 1)) {
            simpleQuickSort(first, pivot, comp);
            first = pivot + 1;
        }
        else {
            simpleQuickSort(pivot + 1, last, comp);
            last = pivot;
        }

    }
    else return;
}