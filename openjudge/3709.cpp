#include <iostream>
#include <string>
#include <stack>
using namespace std;

int main()
{
	int n;
	cin >> n;
	stack<int> st;
	for (int i = 0; i < n; i++)
	{
		string s;
		cin >> s;
		int temp = 0;
		for (int j = 0; j < s.size(); j++)
			temp = temp * 2 + s[j] - '0';
		
		while (temp / 3 != 0)
		{
			st.push(temp % 3);
			temp /= 3;
		}
		st.push(temp % 3);
		while (!st.empty())
		{
			cout << st.top();
			st.pop();
		}
		cout <<endl;
	}
	return 0;
}