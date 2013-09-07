#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>

#define COUNT_MAX 32
using namespace std;

int a[COUNT_MAX];

// 注：以下函数主要偏重于方法的实现，故不再考虑复杂的错误处理。
// 例如数组名作为指针参数传入的时候，不再判断为NULL的情况，以及函数过程中错误的情况。
// 又例如GetMaxMin函数，结果通过参数传引用传递，则返回值可以返回函数执行状况，这里不再详述。这些程序设计的技巧请读者自己考虑。
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

// Get sum by using recursive method
int SumRecursive(int *a, int len)
{
    return (len == 0) ? 0 : a[len - 1] + SumRecursive(a, len -1);
}

// Get both max and min value of the array in just one traversal
bool GetMaxMinNum(int *a, int len, int &max, int &min)
{
    if (a == NULL || len == 0)
        return false;

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
    return true;
}

// 2SUM Problem -- Given the sum, find two numbers
int cmp (const void *a , const void *b)
{ 
    return *(int *)a - *(int *)b;
}

bool Sum2Num(int *a, int len, int sum, int &num1, int &num2)
{
    if (a == NULL || len == 0)
        return false;
    qsort(a, len, sizeof(a[0]), cmp);
    int i = 0, j = len -1;
    while (i < j) {
        if ((a[i] + a[j]) < sum)
            i++;
        else if ((a[i] + a[j]) > sum)
            j--;
        else {
            num1 = a[i];
            num2 = a[j];
            return true;
        }
    }
    return false;
}

// 3SUM Problem -- Find if there are 3 integers a, b, c summing to 0
bool Sum3NumTo0(int *a, int len, int &num1, int &num2, int &num3)
{
    qsort(a, len, sizeof(a[0]), cmp);
    for (int i = 0; i < len -3; i++) {
        num1 = a[i];
        int k = i + 1;
        int l = len - 1;
        while (k < l) {
            num2 = a[k];
            num3 = a[l];
            if (num1 + num2 + num3 == 0)
                return true;
            else if (num1 + num2 + num3 < 0)
                k++;
            else
                l--;
        }
    }
    return false;
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

    for (int i = 0; i < COUNT_MAX; i++)
        a[i] -= 50;
    cout << "Array after - 50:" << endl;
    PrintArray(a, COUNT_MAX);

    int num1, num2;
    cout << "The sum is " << a[0] + a[COUNT_MAX - 4] << ':' << endl;
    if (Sum2Num(a, COUNT_MAX, a[0] + a[COUNT_MAX -4], num1, num2))
        cout << num1 << ' ' << num2 << endl;
    else
        cout << "False" << endl;

    InitArray(a, COUNT_MAX);
    cout << "Array:" << endl;
    for (int i = 0; i < COUNT_MAX; i++)
        a[i] -= 50;
    PrintArray(a, COUNT_MAX);
    int num3;
    cout << "The sum of these 3 numbers is 0:" << endl;
    if (Sum3NumTo0(a, COUNT_MAX, num1, num2, num3))
        cout << num1 << ' ' << num2 << ' ' << num3 << endl;
    else
        cout << "False" << endl;

    return 0;
}