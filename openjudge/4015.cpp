#include <iostream>
#include <cstring>

using namespace std;

int main()
{
	char str[101];
	int len = 0;
	int flag = 0;
	int success = 0;
	while (cin >> str)
	{
		len = strlen(str);
		if (str[0] == '.' || str[0] == '@')
		{
			cout << "NO" <<endl;
			continue;
		}
		if (str[len - 1] == '.' || str[len - 1] == '@')
		{
			cout << "NO" <<endl;
			continue;
		}
		
		for (int i = 0; i < len; i++)
		{
			if (flag) {
				if (str[i] == '@') {
					success = 0;
					break;
				} else if (str[i] == '.')
					success = 1;
			} else {
				if (str[i] == '@' && str[i + 1] == '.') {
					break;
				} else if (str[i] == '@' && str[i - 1] == '.')
					break;
				else if (str[i] == '@')
					flag = 1;
			}
		}
		if (flag == 0) 
			success = 0;
		if (success)
			cout << "YES" <<endl;
		else 
			cout << "NO" <<endl;
		
		flag = 0;
		success = 0;
	}
}