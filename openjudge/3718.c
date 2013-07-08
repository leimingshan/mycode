#include <stdio.h>

int main()
{
	unsigned short a, b;
	int i, j, n;
	int bits = 8 * sizeof(a);
	scanf("%d", &n);
	
	for (i = 0; i < n; i++)
	{
		scanf("%hd %hd", &a, &b);
		if (a == b) {
			printf("YES\n");
			continue;
		}
		
		for (j = 1; j < bits; j++)
		{
			__asm__ __volatile__("rol $0x1, %0"
								:"=r"(a)
								:"0"(a)
								);
			printf("%hd ", a);
			if (a == b)
				break;
		}
		if (bits == j)
			printf("NO\n");
		else
			printf("YES\n");
	}
	return 0;
}