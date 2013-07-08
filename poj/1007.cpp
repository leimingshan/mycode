#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

typedef struct
{
	int count;
	string str;
} DNA;

bool cmp(DNA a, DNA b)
{
	return a.count < b.count;
}

int reverse_count(string& str, int length)
{
	int re = 0;
	for(int i = 0; i < length; i++)
		for(int j = i + 1; j < length; j++)
			if(str[i] > str[j])
				re++;
	return re;
}

int main()
{
	int n, m;
	cin >> n >> m;
	DNA d[m];
	for(int i = 0; i < m; i++)
	{
		cin >> d[i].str;
		d[i].count = reverse_count(d[i].str, n);
	}
	stable_sort(d, d + m, cmp);
	for(int i = 0; i < m; i++)
		cout<<d[i].str<<endl;
	return 0;
}