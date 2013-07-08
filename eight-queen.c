#include <stdio.h>
#include <stdlib.h>

static int total = 0;

void print_square(int **square)
{
	int i, j;
	for (i = 0; i < 8; i++) {
		for (j = 0; j < 8; j++) {
			printf("%d ", square[i][j]);
		}
		printf("\n");
	}
}

int settable(int **square, int m, int n)
{
	int i, j, temp;

	temp = 0;
	for (j = 0; j < 8; j++)
		temp += square[m][j];
	if (temp != 0)
		return 0;

	temp = 0;
	for (i = 0; i < 8; i++)
		temp += square[i][n];
	if (temp != 0)
		return 0;

	temp = 0;
	i = m;
	j = n;
	while (i >= 0 && j >= 0) {
		temp += square[i][j];
		i--;
		j--;
	}
	if (temp != 0)
		return 0;

	i = m;
	j = n;
	while (i >= 0 && j < 8) {
		temp += square[i][j];
		i--;
		j++;
	}
	if (temp != 0)
		return 0;

	i = m;
	j = n;
	while (i < 8 && j >= 0) {
		temp += square[i][j];
		i++;
		j--;
	}
	if (temp != 0)
		return 0;

	i = m;
	j = n;
	while (i < 8 && j < 8) {
		temp += square[i][j];
		i++;
		j++;
	}
	if (temp != 0)
		return 0;
	return 1;

}

void eight_queen(int **square, int d)
{
	int i;
	if (d == 8) {
		total++;
		print_square(square);
		printf("\n");
		return;
	}
	for (i = 0; i < 8; i++) {
		if (settable(square, d, i)) {
			square[d][i] = 1;
			eight_queen(square, d + 1);
			square[d][i] = 0;
		}
	}
}

void clean_square(int **square) {
	int i, j;
	printf("insize clean_square\n");
	for(i = 0; i < 8; i++)
		for(j = 0; j < 8; j++)
			square[i][j] = 0;
	printf("quick clean_square\n");
}

int main()
{
	int **square, i;
	square = (int **)malloc(sizeof(int*) * 8);
	for (i = 0; i < 8; i++)
		square[i] = (int*) malloc(sizeof(int) * 8);
	clean_square(square);
	eight_queen(square, 0);
	printf("There are total:%d\n", total);
	return 0;
}
