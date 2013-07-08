#include <iostream>

using namespace std;

int main()
{
	int n;
	cin >> n;
	int result = 0;
	int temp;
	
	for (int i = 1; i < n + 1; i++)
	{
		if (i % 3 != 0 && i % 5 != 0)
		{
			temp = i;
			while (temp % 10 != 3 && temp % 10 !=5)
			{
				temp /= 10;
				if (temp == 0) {
					result += i * i;
					break;
				}
			}
			
		}
	}
	cout << result <<endl;
	
	return 0;
}