#include <iostream>

using namespace std;

int main()
{
    int N;
    cin >> N;

    while(N--)
    {
        int n;
        cin >> n;
        int a[101] = {0};

        for(int i = 1; i < n+1; i++)
        {
            for(int j = i; j < n+1; j+=i)
                a[j] = 1 - a[j];
        }
        int count = 0;
        for(int i = 1; i < n+1; i++)
        {
            if(a[i])
                count++;
        }
        cout << count << endl;
    }
    return 0;
}
