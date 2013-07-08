/*
 * Source: http://poj.org/problem?id=3252
 * Description: Round numbers
 * tag: Dynamic Programming, combination 
 * author: wangkendy (wkendy@gmail.com)
 *
 */
#include <iostream>
using namespace std;

int C[35][35] = {0};

void cal_Cnk()
{
    for (int i = 0; i < 35; i++) {
        C[i][0] = 1;
    }

    C[1][1] = 1;
    for (int i = 2; i < 35; i++)
        for (int j = 1; j <= i; j++)
            C[i][j] = C[i-1][j] + C[i-1][j-1];
}

int calculate(int end) // < end
{
    int high = 0;
    int tmp = end;
    while (tmp) {
        high++;
        tmp >>= 1;
    }

    int res = 0;
    int max_k;
    for (int n = 2; n < high; n++) {
        max_k = (n - 2) / 2;
        for (int k = 0; k <= max_k; k++)
            res += C[n-1][k];
    }

    int b = 1;
    for (int i = high - 1; i >= 1; i--) {
        if (end & (1<<(i-1))) {
            for (int j = 0; j < i && b + j <= high - b - j; j++)
                res += C[i-1][j];
            b++;
        }
    }
    return res;
}

int main()
{
    int start, finish;
    cin >> start >> finish;
    cal_Cnk();
    int count1 = calculate(start);
    int count2 = calculate(finish + 1);
    cout << count2 - count1 << endl;
    return 0;
}
