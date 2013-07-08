#include <iostream>
#include <string>

using namespace std;

int find(string s1, string s2)
{
	s1 += s1;
	
	if (s1.find(s2) == string::npos)
		return 0;
	else 
		return 1;
}

int main()
{
	string s1, s2;
	int n;
	cin >> n;
	int result = 0;
	
	for (int i = 0; i < n; i++)
	{
		cin >> s1 >> s2;
		if (s1.size() >= s2.size())
			result = find(s1, s2);
		else
			result = find(s2, s1);
			
		if (result)
			cout << "true" << endl;
		else
			cout << "false" << endl;
	}

	return 0;
}