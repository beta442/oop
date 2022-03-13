#pragma once

#include <set>
#include <vector>

std::set<int> GeneratePrimeNumbersSet(int upperBound)
{
	if (upperBound <= 0)
	{
		return std::set<int>{};
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

