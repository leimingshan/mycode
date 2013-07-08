#include <iostream>

using namespace std;

int two_remain[] = {0, 5, 3, 1};

int main()
{
    int a[7];
    
    while (1)
    {
        int count = 0;
        int twos = 0, ones = 0;
        int i;
        for (i = 1; i < 7; i++)
            cin >> a[i];
        for (i = 1; i < 7; i++)
            if (a[i])
                break;
        if (i == 7)
            break;

        count += a[4] + a[5] + a[6] + (a[3] + 3) / 4;
        twos += 5 * a[4] + two_remain[a[3] % 4];
        
        if (a[2] > twos)
            count += (a[2] - twos + 8) / 9;

        ones = 36 * count - 36 * a[6] - 25 * a[5] - 16 * a[4] - 9 * a[3] - 4* a[2];
        if (a[1] > ones)
            count += (a[1] - ones + 35) / 36;

        cout << count << endl;
    }
}
