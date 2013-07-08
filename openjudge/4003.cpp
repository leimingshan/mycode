#include <iostream>
#include <cstring>

using namespace std;

int hextodec(char h)
{
	if (h >=65 && h <= 70)
		return h - 55;
	else
		return h -48;
}

int main()
{
	int T;
	cin >> T;
	
	for (int i = 0; i < T; i++)
	{
		int re = 0;
		int len = 0;
		char a[8];
		cin >> a;
		len = strlen(a);
		
		for (int j = 0; j < len; j++)
		{
			re = re * 16 + hextodec(a[j]);
		}
		cout << re << endl;		
	}
	
	
	return 0;
}