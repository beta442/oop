#pragma once

#include <iostream>
#include <string>
#include <sstream>

inline void PrintConvertationErr(const std::string& s)
{
	std::cout << "An error occured while converting " << s << std::endl;
	std::cout << "Maybe " << s << " isn't a number";
}

inline double ConvertToDouble(const std::string& s)
{
	std::istringstream i(s);
	double x;
	if (!(i >> x))
	{
		PrintConvertationErr(s);
	}
	return x;
}
