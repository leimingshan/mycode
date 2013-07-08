#include <iostream>
#include <stack>
#include <cstring>

using namespace std;

int main()
{
	stack<char> s1;
	stack<int> s2;
	char str[102];
	char re[102];
	
	for (int i = 0; i < 102; i++)
		re[i] = ' ';
	re[101] = '\0';
	while (cin.getline(str, 101))
	{
		cout << str << endl;
		for (int i = 0; i < strlen(str); i++)
		{			
			if (str[i] == ')') {					
				if (!s1.empty() && s1.top() == '(') {
					s1.pop();
					s2.pop();
				}
				else {
					s1.push(str[i]);
					s2.push(i);
				}
			} else if (str[i] == '(') {
				s1.push(str[i]);
				s2.push(i);
			}
		}
		
		if (!s1.empty()) {
			if (s1.top() == '(')
				re[s2.top()] = '$';
			else
				re[s2.top()] = '?';
			
			re[s2.top() + 1] = '\0';

			s1.pop();
			s2.pop();
		} else
			re[0] = '\0';
		
		
		while(!s1.empty())
		{
			if (s1.top() == '(')
				re[s2.top()] = '$';
			else
				re[s2.top()] = '?';
			
			s1.pop();
			s2.pop();
		}
		
		cout << re << endl;
		
		for (int i = 0; i < 102; i++)
			re[i] = ' ';
		re[101] = '\0';
	}

	return 0;
}