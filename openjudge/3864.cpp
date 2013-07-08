#include <iostream>

using namespace std;

int relation7(int num)
{
	if (num % 7 == 0)
		return 1;
	while (num)
	{
		if (num % 10 == 7)
			return 1;
		else
			num /= 10;
	}
	return 0;
}

int main()
{
	int n;
	cin >> n;
	int re = 0;
	for (int i = 1; i < n + 1; i++)
		if (relation7(i) == 0)
			re += i * i;
	cout << re << endl;
}
