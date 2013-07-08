#include <iostream>

using namespace std;

int main()
{
	int n;
	int a[1000] = {0}; 
	int c = 0;
	
	while (cin >> n)
	{
		if (n == 0)
			break;
		
		c = (n - 2) * 180;			
		for (int i = 0; i < n - 1; i++) {
			cin >> a[i];
			c -= a[i];
		}
		
		cout << c << endl;
		c = 0;
	}
}