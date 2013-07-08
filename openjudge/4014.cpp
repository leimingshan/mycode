#include <iostream>
#include <cstring>

using namespace std;

int main()
{
	char str[32];
	int order[32] = {0};
	char result[32];
	int k;
	while (cin >> str)
	{
		cin >> k;
		for (int i = 0; i < strlen(str); i++)
		{
			cin >> order[i];
			str[i] += k;
			if (str[i] > 90)
				str[i] -= 26;
			
			result[order[i] - 1] = str[i];
		}
		
		for (int i = 0; i < strlen(str); i++)
			result[i] = str[order[i] - 1];
				
		result[strlen(str)] = '\0';
		cout << result << endl;
	}
	return 0;
}