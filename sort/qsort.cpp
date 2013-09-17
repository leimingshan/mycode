#include "array.h"
#include <iostream>
#include <algorithm>

using namespace std;

//qsort -- quick sort
int partition(int *a, int p, int r)
{
    int x = a[r];
    int i = p - 1, j;

    for (j = p; j < r; j++) {
        if (a[j] <= x) {
            i++;
            int temp = a[i];
            a[i] = a[j];
            a[j] = temp;
        }
    }
    int temp = a[i + 1];
    a[i + 1] = a[r];
    a[r] = temp;
    return i + 1;
}

void qsort(int *a, int p, int r)
{
    if (p < r) {
        int q = partition(a, p, r);
        qsort(a, p, q - 1);
        qsort(a, q + 1, r);
    }
}

int main()
{
    InitArray(arr, COUNT_MAX);
    cout << "Array:" << endl;
    PrintArray(arr, COUNT_MAX);

    qsort(arr, 0, COUNT_MAX - 1);

    cout << "Array Afer Qsort:" << endl;
    PrintArray(arr, COUNT_MAX);

    return 0;
}
