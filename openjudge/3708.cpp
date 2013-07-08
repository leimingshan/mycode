#include <iostream>
#include <cstring>

using namespace std;

int main()
{
	int N;
	cin >> N;
	
	for (int i = 0; i < N; i++)
	{
		int num;
		cin >> num;
		int re = 0;
		while (num)
		{
			if (num & 1)
				re++;
			num>>=1;
		}
		cout << re << endl;
	}
}