#include <iostream>
#include <optional>
#include <set>
#include <sstream>
#include <string>
#include <vector>

std::optional<int> ParseArgs(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cout << "Invalid usage:" << std::endl
				  << "PROGRAM.exe <uppervalue> | uppervalue is positiv integer up to 1e8" << std::endl;
		return std::nullopt;
	}

	std::stringstream ss{ argv[1] };
	int upperValue;
	ss >> upperValue;
	if (ss.fail())
	{
		std::cout << "Invalid argument value" << std::endl
				  << "Usage:" << std::endl
				  << "PROGRAM.exe <uppervalue> | uppervalue is positiv integer up to 1e8" << std::endl;
		return std::nullopt;
	}

	return std::optional<int>{ upperValue };
}

std::set<int> GeneratePrimeNumbersSet(int upperBound);

int main(int argc, char* argv[])
{
	std::optional<int> oUpperValue = ParseArgs(argc, argv);
	if (!oUpperValue)
	{
		return 1;
	}
	int upperValue = oUpperValue.value();

	std::cout << GeneratePrimeNumbersSet(upperValue).size() << std::endl;

	return 0;
}

std::set<int> GeneratePrimeNumbersSet(int upperBound)
{
	if (upperBound <= 0)
	{
		return std::set<int>{ 0 };
	}
	std::set<int> res;

	std::vector<bool> temp = std::vector<bool>(upperBound, true);
	for (size_t i = 0; i < temp.size(); i = i + 2)
	{
		temp[i] = 0;
	}

	for (size_t i = 3; i * i < temp.size(); i++)
	{
		if (temp[i])
		{
			for (size_t j = i + i; j < temp.size(); j = j + i)
			{
				temp[j] = false;
			}
		}
	}

	for (size_t i = 0; i < temp.size(); i++)
	{
		if (temp[i])
		{
			res.emplace(i);
		}
	}

	return res;
}
