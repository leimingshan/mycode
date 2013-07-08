#include <iostream>

using namespace std;

int JosephRight(int k, int m)
{
	int index = 0;
	int round = 0;
	int n = 2 * k;
	while (round < k)
	{
		index = (index + m - 1) % n;
		if (index < k)
			return 0;
		
		round++;
		n--;
	}
	return 1;
}

int main()
{
	int k;
	
	int m;
	int result[14];
	for (int k = 1; k < 14; k++)
	{
		for (int i = 1; ; i++)
		{
			m = (k + 1) * i;
			if (JosephRight(k, m))
			{
				result[k] = m;
				break;
			}
			else
			{
				m++;
				if (JosephRight(k, m))
				{
					result[k] = m;
					break;
				}
			}
		}
	}
	int input;
	cin >> input;
	while(input) 
	{
		cout << result[input] << endl;
		cin >> input;
	}
	return 0;		
}
