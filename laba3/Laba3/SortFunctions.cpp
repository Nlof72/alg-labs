#ifndef SORT_H
#define SORT_H
#include <iostream>

constexpr int SWITCH_ON_QUICK_SORT = 30;

template<typename T>
void PrintArray(T* arrayPointerStart, T* arrayPointerEnd) 
{
    while (arrayPointerStart < arrayPointerEnd) {
        std::cout << *arrayPointerStart << " ";
        arrayPointerStart++;
    }
    std::cout << "\n";
}

template<typename T, typename Compare>
void InsertSort(T* arrayStartPointer, T* arrayEndPointer, Compare comp)
{
    if (arrayStartPointer == arrayEndPointer)
    {
        return;
    }

    for (T* i = arrayStartPointer + 1; i <= arrayEndPointer; i++) {
        T* currentElement = i - 1;
        T nextElement = *i;
        while (currentElement >= arrayStartPointer && comp(nextElement, *currentElement)) {
            *(currentElement + 1) = std::move(*currentElement);
            currentElement--;
        }
        *(currentElement + 1) = std::move(nextElement);
    }
}


template<typename T, typename Compare>
T* GetPivot(T* arrayStartPointer, T* arrayEndPointer, Compare comp)
{
    T* pivot = (arrayEndPointer - arrayStartPointer) / 2 + arrayStartPointer;

    if (comp(*arrayEndPointer, *arrayStartPointer)) std::swap(arrayEndPointer, arrayStartPointer);
    if (comp(*pivot, *arrayStartPointer)) std::swap(pivot, arrayStartPointer);
    if (comp(*arrayEndPointer, *pivot)) std::swap(arrayEndPointer, pivot);

    return arrayStartPointer;
}


template<typename T, typename Compare>
T* GetPartitionPointer(T* arrayStartPointer, T* arrayEndPointer, Compare comp)
{
    T* pivot = GetPivot(arrayStartPointer, arrayEndPointer, comp);

    T* partitionStart = arrayStartPointer + 1;
    T* partitionEnd = arrayEndPointer;


    while (true) {
        while (comp(*partitionStart, *pivot)) {
            partitionStart++;
        }
        while (comp(*pivot, *partitionEnd)) {
            partitionEnd--;
        }

        if (partitionStart >= partitionEnd)
            break;

        std::swap(partitionStart, partitionEnd);
        partitionStart++;
        partitionEnd--;
    }

    std::swap(partitionEnd, pivot);

    return partitionEnd;
}

template<typename T, typename Compare>
void OptimazedQuicSort(T* arrayStartPointer, T* arrayEndPointer, Compare comp)
{
    if (arrayStartPointer == arrayEndPointer)
    {
        return;
    }

    while (arrayEndPointer - arrayStartPointer > 0) {

        T* partitionEnd = GetPartitionPointer(arrayStartPointer, arrayEndPointer, comp);


        if (partitionEnd - arrayStartPointer > arrayEndPointer - partitionEnd) {
            OptimazedQuicSort(partitionEnd + 1, arrayEndPointer, comp);
            arrayEndPointer = partitionEnd - 1;
        }
        else {
            OptimazedQuicSort(arrayStartPointer, partitionEnd - 1, comp);
            arrayStartPointer = partitionEnd + 1;
        }
    }
}


template<typename T, typename Compare>
void Sort(T* arrayStartPointer, T* arrayEndPointer, Compare comp) 
{
    if (arrayStartPointer == arrayEndPointer)
    {
        return;
    }

    //std::cout << arrayEndPointer - arrayStartPointer;

    while (arrayEndPointer - arrayStartPointer > SWITCH_ON_QUICK_SORT) {

        T* partitionEnd = GetPartitionPointer(arrayStartPointer, arrayEndPointer, comp);

        if (partitionEnd - arrayStartPointer < arrayEndPointer - partitionEnd + 1) {
            Sort(arrayStartPointer, partitionEnd, comp);
            arrayStartPointer = partitionEnd + 1;
        }
        else {
            Sort(partitionEnd + 1, arrayEndPointer, comp);
            arrayEndPointer = partitionEnd;
        }
    }
    InsertSort(arrayStartPointer, arrayEndPointer, comp);
}

#endif