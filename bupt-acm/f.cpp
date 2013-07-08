#include <iostream>

using namespace std;

int match8digits(int* a, int number)
{
	int used_a[8] = {0};
	bool result = 1;
	int num = number;
	for (int i = 0; i < 8; i++)
	{
		num = number;
		while (num) {
			if (!used_a[i] && (num % 10 == a[i])) {
				used_a[i] = 1;
				break;
			}
			num /= 10;
		}
		result = result && used_a[i];
	}
	
	return result;
}

int main()
{
	int T;
	cin >> T;
	for (int i = 0; i < T; i++)
	{
		int a[8] = {0};
		int x;
		bool find = false;
		for (int j = 0; j < 8; j++)
			cin >> a[j];
		cin >> x;
		
		int temp;
		for (int k = 10000000 / x; ; k++)
		{
			temp = x * k;
			if (temp < 10000000)
				continue;
			else if (temp > 99999999)
				break;
			
			if (match8digits(a, temp))
			{
				cout << "Yes" << endl;
				find = true;
				break;
			}			
		}
		if (!find)
			cout << "No" << endl;
	}
	return 0;
}