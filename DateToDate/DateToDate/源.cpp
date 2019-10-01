#include<iostream>
#include<windows.h>
using namespace std;

int GetDayOfMonth(int year, int month)
{
	int days[] = { 0 ,31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	if ((0 == year % 4 && 0 != year % 100) || 0 == year % 400)
	{
		days[2] += 1;
	}
	return days[month];
}

bool IsValidDay(int year, int month, int day)
{
	if (year > 0 && (month > 0 && month < 13) && (day>0 && day <= GetDayOfMonth(year, month)))
	{
		return true;
	}
	return false;
}
int main()
{
	int year, month, day;
	size_t totalDays = 0;
	cin >> year >> month >> day;
	if (IsValidDay(year, month, day))
	{
		for (size_t i = 1; i < month; ++i)
		{
			totalDays += GetDayOfMonth(year, i);
		}
			totalDays += day;
			cout << totalDays << endl;
	}
	else
	{
		return -1;
	}
	system("pause");
	return 0;
}