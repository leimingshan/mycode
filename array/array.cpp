#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>

#define COUNT_MAX 32
using namespace std;

int a[COUNT_MAX];

// 注：以下函数主要偏重于方法的实现，故不再考虑复杂的错误处理。
// 例如数组名作为指针参数传入的时候，不再判断为NULL的情况，以及函数过程中错误的情况。
// 又例如GetMaxMin函数，结果通过参数传引用传递，则返回值可以返回函数执行状况，这里也不再详细考虑。
// 即默认a是定义好的数组，且定义好了数组的大小。

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

int GetMaxNum(int *a, int len)
{
    int max = a[0];
    for (int i = 1; i < len; i++) {
        if (a[i] > max)
            max = a[i];
    }
    return max;
}

int Sum(int *a, int len)
{
    int re = 0;
    for (int i = 0; i < len; i++)
        re += a[i];
    return re;
}
int SumRecursive(int *a, int len)
{
    return (len == 0) ? 0 : a[len - 1] + SumRecursive(a, len -1);
}

void GetMaxMinNum(int *a, int len, int &max, int &min)
{
    if (len & 1) // 奇数个元素
        max = min = a[0];
    else {
        max = a[0] > a[1] ? a[0] : a[1];
        min = a[0] > a[1] ? a[1] : a[0];
    }
    for (int i = 2; i < len; i += 2) {
        if (a[i] > a[i + 1]) {
            if (a[i] > max)
                max = a[i];
            if (a[i + 1] < min)
                min = a[i + 1];
        } else {
            if (a[i] < min)
                min = a[i];
            if (a[i + 1] > max)
                max = a[i + 1];
        }
    }
}

int main()
{
    InitArray(a, COUNT_MAX);
    cout << "Array:" << endl;
    PrintArray(a, COUNT_MAX);

    cout << "Max: " << GetMaxNum(a, COUNT_MAX) << endl;
    cout << "Sum: " << Sum(a, COUNT_MAX) << endl;
    cout << "SumRecursive: " << SumRecursive(a, COUNT_MAX) << endl;

    int max_num, min_num;
    GetMaxMinNum(a, COUNT_MAX, max_num, min_num);
    cout << "MaxMin: " << max_num << ' ' << min_num << endl;

    return 0;
}