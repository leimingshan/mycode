#include <iostream>
#include <cstdio>

using namespace std;  
  
/*得到Haab历月份对应的数字*/  
int GetMonth(char* month)  
{  
    int ASCII_sum=0;  
    for(int i = 0; month[i]; i++)  
        ASCII_sum += month[i];  
  
    switch(ASCII_sum)  
    {  
        case 335:return 1;  //pop  
        case 221:return 2;  //no  
        case 339:return 3;  //zip  
        case 471:return 4;  //zotz  
        case 438:return 5;  //tzec  
        case 345:return 6;  //xul  
        case 674:return 7;  //yoxkin  
        case 328:return 8;  //mol  
        case 414:return 9;  //chen  
        case 338:return 10;  //yax  
        case 318:return 11;  //zac  
        case 304:return 12;  //ceh  
        case 305:return 13;  //mac  
        case 636:return 14;  //kankin  
        case 433:return 15;  //muan  
        case 329:return 16;  //pax  
        case 534:return 17;  //koyab  
        case 546:return 18;  //cumhu  
        case 552:return 19;  //uayet  
    }  
}

int HaabTotalDay(int day, int month, int year)
{
	return year * 365 + (month - 1) * 20 + day;
}

int main()
{
	char str[20][9] = {"imix","ik","akbal","kan","chicchan","cimi","manik","lamat","muluk","ok","chuen","eb","ben","ix","mem","cib","caban","eznab","canac","ahau"};
	int T;
	scanf("%d", &T);
	char month[10];
	int day, year;
	printf("%d\n", T);
	while(T--)
	{
		scanf("%d.%s %d", &day, month, &year);
		int days = HaabTotalDay(day, GetMonth(month), year);
		int day_a, month_a, year_a;
		year_a = days / 260;
		month_a = days % 20;
		day_a = days % 13 + 1;
		printf("%d %s %d\n", day_a, str[month_a], year_a);
	}
	return 0;
}