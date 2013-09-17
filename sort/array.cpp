#include "array.h"
#include <iostream>
#include <cstdlib>

using namespace std;

int arr[COUNT_MAX];

void InitArray(int *a, int len)
{
    srand(time(NULL));

    for (int i = 0; i < len; i++)
        a[i] = rand() % 100 + 1;
}

void PrintArray(int *a, int len)
{
    for (int i = 0; i < len; i++)
        cout << a[i] << ' ';
    cout << endl;
}