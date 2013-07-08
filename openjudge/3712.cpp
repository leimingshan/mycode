#include <iostream>
#include <string>
#include <map>

using namespace std;
map<int, int> mapint;

int compare(string s1, string s2)
{
	if (s1.size() != s2.size())
		return 0;
	int i;
	for (i = 0; i < s1.size(); i++)
		if (mapint.find(s1[i])->second != s2[i] - '0') 
			return 0;
	if (i == s1.size())
		return 1;
}

void mapint_init()
{	
	char ch;
	ch = 'a';
	int i = 2;
	while (ch <= 'w')
	{
		mapint.insert(pair<int, int>(ch, i));
		mapint.insert(pair<int, int>(ch + 1, i));
		mapint.insert(pair<int, int>(ch + 2, i));
		
		mapint.insert(pair<int, int>(ch - 32, i));
		mapint.insert(pair<int, int>(ch - 31, i));
		mapint.insert(pair<int, int>(ch - 30, i));
		
		if (ch == 'p' || ch == 'w') {
			mapint.insert(pair<int, int>(ch + 3, 7));
			mapint.insert(pair<int, int>(ch - 29, 7));
			ch++;
		}
		ch += 3;
		i++;
	}

	return;
}

int main()
{
	int n;
	cin >> n;
	mapint_init();
	for (int i = 0; i < n; i++) {
		string s1, s2;
		cin >> s1 >> s2;
		
		if (compare(s1, s2))
			cout<<'Y'<<endl;
		else
			cout<<'N'<<endl;
	}
	
}