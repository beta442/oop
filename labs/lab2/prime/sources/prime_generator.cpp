#include "../headers/prime_generator.h"

std::set<int> GeneratePrimeNumbersSet(const int upperBound)
{
	if (upperBound <= 0)
	{
		return std::set<int>{};
	}

	std::vector<bool> temp = std::vector<bool>(upperBound, true);
	temp[0] = false;
	temp[1] = false;

	size_t multiplierUpperBound = static_cast<size_t>(std::trunc(std::sqrt(std::size(temp))));
	for (size_t i = 0; i < multiplierUpperBound; i++)
	{
		if (temp[i])
		{
			for (size_t j = i + i; j < temp.size(); j += i)
			{
				temp[j] = false;
			}
		}
	}

	std::set<int> res;
	for (size_t i = 0; i < temp.size(); i++)
	{
		if (temp[i])
		{
			res.emplace(static_cast<int>(i));
		}
	}

	return res;
}
