#include <iostream>

using namespace std;

int a[100];
int len = 0;

int issum(int index)
{
	int i = 0, j = 1;
	
	for (i = 0; i < len; i++)
	{
		if (i == index)
			continue;
		for (j = i + 1; j < len; j++)
		{
			if (j == index)
				continue;
			if (a[index] == a[i] + a[j])
				return 1;
		}	
	}
	return 0;
}

int main()
{
	int T = 0;
	cin >> T;
	int result = 0;
	for (int i = 0; i < T; i++)
	{
		cin >> len;
		for (int j = 0; j < len; j++)
			cin >> a[j];
		for (int j = 0; j < len; j++)
			if (issum(j))
				result++;
			
		cout << result <<endl;
		result = 0;
	}
}