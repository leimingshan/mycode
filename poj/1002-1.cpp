#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>

using namespace std;

int cmp(const void *a,const void *b)
{
     return *(int*)a - *(int*)b;
}

int map[26] = {2, 2, 2, 3, 3, 3, 4, 4, 4,
				5, 5, 5, 6, 6, 6, 7, 0, 7, 7,
				8, 8, 8, 9, 9, 9, 0};
			
int main()
{
	int *num;
	char buf[50];
	int count;
	int i, j, k, x, t;
	
	scanf("%d", &count);
	num = new int[count];
	
	for (i = 0; i < count; i++)
	{
		scanf("%s", buf);
		t = 0;
		for (int j = 0; buf[j]; j++)
		{
			if (buf[j] == '-')
				continue;
			
			if (buf[j] >= 'A' && buf[j] <= 'Z')
				t = t * 10 + map[buf[j] - 'A'];
			else
				t = t * 10 + buf[j] - '0';
		}
		num[i] = t;
	}
	
	qsort(num, count, sizeof(int), cmp);
	
	int c = 1, z = 0;
	for (i = 0; i < count - 1; i++)
	{
		if (num[i] != num[i+1]) {
			if (c != 1) {
				printf("%03d-%04d %d\n", num[i] / 10000, num[i] % 10000, c);
				z = 1;
			}
			c = 1;
		} else {
			c++;
		}
	}
	if (c != 1) {
		printf("%03d-%04d %d\n", num[i] / 10000, num[i] % 10000, c);
		z = 1;
	}
	if (!z)
		printf("No duplicates.\n");
	delete [] num;
	
	return 0;
}