#include <iostream>
#include <cmath>

using namespace std;

int g_maxValue = 6;

void PrintSumProbabilityOfDices_2(int number)
 {
     double* pProbabilities[2];
     pProbabilities[0] = new double[g_maxValue * number + 1];
     pProbabilities[1] = new double[g_maxValue * number + 1];
     for(int i = 0; i < g_maxValue * number + 1; ++i)
     {
         pProbabilities[0][i] = 0;
         pProbabilities[1][i] = 0;
     }
  
     int flag = 0;
     for (int i = 1; i <= g_maxValue; ++i)
         pProbabilities[flag][i] = 1;
       
     for (int k = 2; k <= number; ++k)
     {
         for (int i = k; i <= g_maxValue * k; ++i)
         {
             pProbabilities[1 - flag][i] = 0;
             for(int j = 1; j <= i- k + 1 && j <= g_maxValue; ++j)
                 pProbabilities[1 - flag][i] += pProbabilities[flag][i - j];
         }
  
         flag = 1 - flag;
     }
  
     double total = pow((double)g_maxValue, number);
     for(int i = number; i <= g_maxValue * number; ++i)
     {
         double ratio = pProbabilities[flag][i] / total;
         cout<< i << ' ' << ratio <<endl;
     }
  
     delete[] pProbabilities[0];
     delete[] pProbabilities[1];
 }
 
int main()
{
	PrintSumProbabilityOfDices_2(7);
}