#include "array.h"
#include <iostream>

using namespace std;

// 将两个有序数列a[start...mid]和a[mid...end]合并。
static void merge(int a[], int start, int mid, int end)
{
    int *temp = new int[end - start + 1];
    int i = start;
    int j = mid + 1;
    int k = 0;
    while (i <= mid && j <= end) {
        if (a[i] < a[j])
            temp[k++] = a[i++];
        else
            temp[k++] = a[j++];
    }

    while (i <= mid)
        temp[k++] = a[i++];
    while (j <= end)
        temp[k++] = a[j++];

    for (i = 0; i < k; i++)
        a[start + i] = temp[i];

    return;
}

static void MergeSort(int a[], int start, int end)
{
    int mid = (start + end) / 2;
    if (start < end) {
        MergeSort(a, start, mid);
        MergeSort(a, mid + 1, end);
        merge(a, start, mid, end);
    }
}

int main()
{
    InitArray(arr, COUNT_MAX);
    cout << "Array:" << endl;
    PrintArray(arr, COUNT_MAX);

    MergeSort(arr, 0, COUNT_MAX - 1);

    cout << "Array Afer MergeSort:" << endl;
    PrintArray(arr, COUNT_MAX);

    return 0;
}
