// Copyright (c) 2021 Dave Marsh. See LICENSE.
#pragma once

#include "base.h"

namespace glow
{
    template <typename T>
    void swap(T *arr, int i, int j)
    {
        T t = arr[i];
        arr[i] = arr[j];
        arr[j] = t;
    }

    template <typename T>
    bool less(T *arr, int i, int j)
    {
        return (arr[i] < arr[j]);
    }

    template <typename T>
    int partition(T *arr, int low, int high)
    {
        int pivot = high;
        int i = low - 1;

        for (int j = low; j < high; j++)
        {
            if (less(arr, j, pivot))
            {
                i++;
                swap(arr, i, j);
            }
        }

        i++;
        swap(arr, i, high);
        return i;
    }

    template <typename T>
    void quickSort(T *arr, int low, int high)
    {
        if (low < high)
        {
            int pi = partition(arr, low, high);
            quickSort(arr, low, pi - 1);
            quickSort(arr, pi + 1, high);
        }
    }

    template <typename T>
    void Sort(T *arr, int len)
    {
        quickSort(arr, 0, len - 1);
    }
}