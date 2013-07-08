#include <iostream>
#include <cstdio>

using namespace std;

int mod(int n, int m)
{
	return n - (n / m) * m;
}

int main()
{
	int a, b;
	while(scanf("%d %d", &a, &b) != EOF)
		printf("%d\n", mod(a, b));
		
	return 0;
}