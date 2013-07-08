#include <cstdio>
#include <iostream>

using namespace std;

int shulundaoshu(int a, int b, int c)//a,b的最小公倍数的倍数中%c=1
{
	int t = a * b;
	for (int i = 1; ; i++)
	{
		if ((t * i) % c == 1)
			return t * i;
	}
}

int main()
{
	int p, e, i, d;
	int time = 0;
	int a = 23, b = 28, c = 33;
	int total = a * b * c;
	int a1 = shulundaoshu(b, c, a);
	int b1 = shulundaoshu(a, c, b);
	int c1 = shulundaoshu(b, a, c);
	while(1)
	{
		scanf("%d %d %d %d", &p, &e, &i, &d);
		if (p==-1 && e==-1 && i==-1 && d==-1)
			break;
		int result = (a1 * p + b1 * e + c1 * i - d + total) % total;
		if (result == 0)
			result = total;
		printf("Case %d: the next triple peak occurs in %d days.\n", ++time, result);
	}
	return 0;
}