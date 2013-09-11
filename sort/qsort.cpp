#include <iostream>
#include <cstdlib>
#include <algorithm>

#define COUNT_MAX 32
using namespace std;

int a[COUNT_MAX];

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
    InitArray(a, COUNT_MAX);
    cout << "Array:" << endl;
    PrintArray(a, COUNT_MAX);

    qsort(a, 0, COUNT_MAX - 1);

    PrintArray(a, COUNT_MAX);

    return 0;
}