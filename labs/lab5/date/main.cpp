#include "headers/stdafx.h"

#include "headers/date/CDate.h"

int main()
{
	Date date{ 728 };
	unsigned year = date.GetYear();
	Date::Month month = date.GetMonth();
	unsigned monthDay = date.GetDay();

	std::cout << monthDay << '.' << static_cast<int>(month) << '.' << year << std::endl;

	return 0;
}
