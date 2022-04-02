#include "../headers/std_lib.h"

bool CopyStringToDouble(const std::string& str, double& val)
{
	bool isOk = true;

	std::stringstream ss{};
	ss << str;
	ss >> val;
	if (ss.fail())
	{
		return !isOk;
	}

	return isOk;
}

bool CopyStreamOfDoubleIntoVector(std::istream& fIn, std::vector<double>& vec)
{
	bool isOk = true;
	std::vector<double> res{};

	double valInProcess;
	std::istream_iterator<std::string> it{ fIn }, end;
	if (it == end)
	{
		return isOk;
	}

	for (; it != end; it++)
	{
		isOk = CopyStringToDouble((*it), valInProcess);
		if (*it == "Q" || *it == "q" || !isOk)
		{
			return isOk;
		}

		res.push_back(valInProcess);
	}

	vec = std::move(res);
	vec.shrink_to_fit();

	return isOk;
}

constexpr auto OUTPUT_WIDTH = 10;
constexpr auto OUTPUT_PRECISION = 4;

void ProcessVectorOfDoubleByTask(std::vector<double>& vec)
{
	if (std::size(vec) == 0)
	{
		return;
	}
	double minElementIt = *(std::min_element(std::begin(vec), std::end(vec)));

	for (auto& val : vec)
	{
		val *= minElementIt;
	}
}

void PrintVectorOfDouble(const std::vector<double>& vec)
{
	if (std::size(vec) == 0)
	{
		return;
	}
	for (const auto& val : vec)
	{
		std::cout << "|";
		std::cout.width(OUTPUT_WIDTH);
		std::cout.precision(OUTPUT_PRECISION);
		std::cout.right;
		std::cout << val + 0.0;
		std::cout << "|" << std::endl;
	}
	std::cout << std::endl;
}
