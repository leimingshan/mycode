#include <iostream>

using namespace std;

int Min(int a, int b)
{
    int min = (a < b) ? a : b;
    return min;
}

int GetUglyNumber(int base, int index)
{
    if(index <= 0)
        return 0;
    int *pUglyNumbers = new int[index];
    pUglyNumbers[0] = base;
	
    int nextUglyIndex = 1;
	
    int *pMultiply2 = pUglyNumbers;
    int *pMultiply3 = pUglyNumbers;
    
    while(nextUglyIndex < index)
    {
        int min = Min(*pMultiply2 * 2 + 1, *pMultiply3 * 3 + 1);
        pUglyNumbers[nextUglyIndex] = min;
        while(*pMultiply2 * 2 + 1 <= pUglyNumbers[nextUglyIndex])
            ++pMultiply2;
        while(*pMultiply3 * 3 + 1 <= pUglyNumbers[nextUglyIndex])
            ++pMultiply3;

        ++nextUglyIndex;
    }
    int ugly = pUglyNumbers[nextUglyIndex - 1];
    delete[] pUglyNumbers;
    return ugly;
}


int main()
{
	int base, n;
	
	while (cin >> base >> n)
		cout << GetUglyNumber(base, n) << endl;
		
	return 0;
}