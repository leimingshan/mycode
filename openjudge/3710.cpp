#include <iostream>
#include <cstring>

using namespace std;

int main()
{
	int n;
	cin >> n;
	int result = 0;
	int a, b;
	
	for (int i = 0; i < n; i++)
	{
		cin >> a >> b;
		
		while (a != 0 || b != 0)
		{
			if (a % 2 != b % 2)
				result ++;
			a /= 2;
			b /= 2;
		}
		cout << result <<endl;
		
		result = 0;
	}
	
	return 0;
}