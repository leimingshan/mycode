#include <iostream>
#include <string>

using namespace std;

class Employee
{
public:
	string name;
	int days;
}

class Date
{
public:
	int year;
	int month;
	int day;
	Date() { };
	Date(int y, int m, int d): year(y), month(m), day(d) { };
	static int sub(Date d1, Date d2);
	static int days_in_year(Date d);
	static int is_leap_year(int year);
};

int Date::is_leap_year(int year)
{
	if (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0))
		return 1;
	else
		return 0;
}

int Date::days_in_year(Date d)
{
	int days = 0;
	int year = d.year;
	int month = d.month;
	int day = d.day;
	for (int i = 1; i < month; i++)
	{
		if (i == 1 || i == 3 || i == 5 || i == 7 || i == 8 || i == 10 || i == 12)
			days += 31;
		else if (i == 2)
		{
			if (is_leap_year(year))
				days += 29;
			else
				days += 28;
		} else {
			days += 30;
		}
	}
	days += day;
	return days;
}

int Date::sub(Date d1, Date d2)
{
	int days = 0;
	for (int i = d1.year; i < d2.year; i++)
	{
		if (is_leap_year(i))
			days += 366;
		else
			days += 365;
	}
	days -= days_in_year(d1);
	days += days_in_year(d2);
	days++;
	return days;
}

int main()
{
	int n;
	cin >> n;
	Employee e[n];
	for (int i = 0; i < n; i++)
	{
		string name;
		Date d1, d2;
		cin >> name >> d1.year >> d1.month >> d1.day >> d2.year >> d2.month >> d2.day;
		cout << Date::sub(d1, d2) << endl;
	}
	
	return 0;
}