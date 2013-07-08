#include <iostream>

using namespace std;

int main()
{
	int reader[200] = {0};
	int book[200] = {0};
	
	int N, M;
	cin >> N >> M;
	
	for (int i = 0; i < N; i++)
	{
		int num;
		cin >> num;
		book[num]++;
		reader[i] = num;
	}
	
	for (int i = 0; i < N; i++)
	{
		if (book[reader[i]] != 1)
			cout << book[reader[i]] - 1 << endl;
		else
			cout << "BeiJu" <<endl;
	}
	
	return 0;
}