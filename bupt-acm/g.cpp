#include <iostream>
#include <iomanip>
#include <cmath>  
#include <cstdio>  
  
using namespace std;  
double sswr(double x, double k)  
{  
    return floor(pow(10, k)*x  + 0.5) / pow(10, k);  
}

int main()
{
	int i, j;
	int count[8][43] = {0};
	for (j = 1; j <= 6; j++)
		count[1][j] = 1;
	
	for (i = 2; i <= 7; i++)
		for (j = i; j <= 6*i; j++)
		{
			for (int k = 1; k <= 6 && k <= j; k++)
				count[i][j] += count[i-1][j-k];
		}
	int total = 6*6*6*6*6*6*6;
	int n;
	cout.precision(4);
	while (cin >> n)
		cout << count[7][n] << endl << (double)count[7][n] / total << endl;
	return 0;
}
