#include <iostream>

using namespace std;

int main()
{
    int k;
    cin >> k;
    for (int i = 0; i < k; i++) {
        int n, m, a;
        cin >> n >> m;
        int success = 0;
        for (a = 1; a <= m -a; a++) {
            if (n % a == 0 && n % (m - a) == 0) {
                success = 1;
                break;
            }
        }
        
        if (success)
            cout << a << endl;
        else
            cout << -1 << endl;
        success = 0;
    }
}
