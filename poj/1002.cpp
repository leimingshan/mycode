#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>

using namespace std;

int cmp(const void *a,const void *b)
{
     return(strcmp((char*)a,(char*)b));
}

char map[26] = {'2', '2', '2', '3', '3', '3', '4', '4', '4',
				'5', '5', '5', '6', '6', '6', '7', '0', '7', '7',
				'8', '8', '8', '9', '9', '9', '0'};
			
int main()
{
	char phone_num[100000][50];
	char buf[50];
	int count;
	int i, j, k, x;
	
	memset(phone_num, 0, sizeof(phone_num));  
	
	scanf("%d", &count);
	for (i = 0; i < count; i++)
	{
		scanf("%s", buf);
		x = 0;
		for (int j = 0; buf[j]; j++)
		{
			if (buf[j] == '-')
				continue;
			
			if (buf[j] >= 'A' && buf[j] <= 'Z')
				buf[j] = map[buf[j] - 'A'];
				
			phone_num[i][x++] = buf[j];
			if (x == 3)
				phone_num[i][x++] = '-';
		}
	}
	
	qsort(phone_num, count, 50, cmp);
	
	int c = 1, z = 0;
	for (i = 0; i < count - 1; i++)
	{
		if (strcmp(phone_num[i], phone_num[i+1])) {
			if (c != 1) {
				printf("%s %d\n", phone_num[i], c);
				z = 1;
			}
			c = 1;
		} else {
			c++;
		}
	}
	if (c != 1) {
		printf("%s %d\n", phone_num[i], c);
		z = 1;
	}
	if (!z)
		printf("No duplicates.\n");
	
	return 0;
}