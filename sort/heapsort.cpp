#include "array.h"
#include <iostream>
#include <cmath>

using namespace std;

// heap index from 0
inline int parent(int i)
{
    return (int)floor((i - 1) / 2);
}

inline int left(int i)
{
    return 2 * i + 1;
}

inline int right(int i)
{
    return 2 * i + 2;
}

void MaxHeapify(int A[], int i, int heap_size)
{
    int l = left(i);
    int r = right(i);
    int largest, temp;

    if (l < heap_size && A[l] > A[i])
        largest = l;
    else
        largest = i;
    if (r < heap_size && A[r] > A[largest])
        largest = r;

    if (largest != i) {
        // exchange A[i] and A[largest]
        temp = A[i];
        A[i] = A[largest];
        A[largest] = temp;

        MaxHeapify(A, largest, heap_size);
    }
}

void MaxHeapify_NonRecursive(int A[], int i, int heap_size)
{
    int l = 2 * i + 1;
    int r;

    while (l < heap_size) {
        if ((l + 1) < heap_size && A[l] < A[l + 1])
            l++;
        if (A[i] > A[l])
            break;
        else {
            int temp = A[i];
            A[i] = A[l];
            A[l] = temp;

            i = l;
            l = 2 * i + 1;
        }
    }

    return;
}

void BuildMaxHeap(int A[], int heap_size)
{
    for (int i = (heap_size - 2) / 2; i >= 0; i--)
        MaxHeapify(A, i, heap_size);
}

void HeapSort(int A[], int heap_size)
{
    BuildMaxHeap(A, heap_size);
    int temp;

    for (int i = heap_size - 1; i >= 1; i--) {
        // exchange A[0] and the last one
        temp = A[0];
        A[0] = A[i];
        A[i] = temp;

        MaxHeapify(A, 0, i);
    }
}

int main()
{
    InitArray(arr, COUNT_MAX);
    cout << "Array:" << endl;
    PrintArray(arr, COUNT_MAX);

    HeapSort(arr, COUNT_MAX);

    cout << "Array After HeapSort:" << endl;
    PrintArray(arr, COUNT_MAX);

    return 0;
}
