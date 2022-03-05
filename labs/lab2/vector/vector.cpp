#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <vector>

bool CopyStreamOfDoubleIntoVector(std::istream& fIn, std::vector<double>& vec);
void ProcessDoubleVectorByTask(std::vector<double>& vec);
void PrintDoubleVector(const std::vector<double>& vec);

int main()
{
	std::vector<double> vec{};
	if (!CopyStreamOfDoubleIntoVector(std::cin, vec))
	{
		std::cout << "An error occured while processing input" << std::endl;
		return 1;
	}

	if (std::size(vec) == 0)
	{
		std::cout << "Nothing to process" << std::endl;
		return 1;
	}

	std::cout << "Vector was:" << std::endl;
	PrintDoubleVector(vec);

	ProcessDoubleVectorByTask(vec);

	std::cout << std::endl
			  << "Vector now:" << std::endl;
	PrintDoubleVector(vec);

	return 0;
}

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

	std::cout << "Please enter values (to stop enter Q or q):" << std::endl;
	std::istream_iterator<std::string> it{ fIn }, end;

	double valInProcess;
	for (; it != end; it++)
	{
		if (*it == "Q" || *it == "q")
		{
			break;
		}

		if (!CopyStringToDouble((*it), valInProcess))
		{
			isOk = false;
			break;
		}

		res.push_back(valInProcess);
	}

	vec = std::move(res);
	vec.shrink_to_fit();

	return isOk;
}

void ProcessDoubleVectorByTask(std::vector<double>& vec)
{
	if (std::size(vec) == 0)
	{
		return;
	}
	std::vector<double>::const_iterator minElementIt = std::min_element(std::begin(vec), std::end(vec));

	std::cout.precision(4);
	std::cout << "minValue:" << *minElementIt << std::endl;

	for (auto& val : vec)
	{
		val *= *minElementIt;
	}
}

constexpr auto OUTPUT_WIDTH = 10;
constexpr auto OUTPUT_PRECISION = 4;

void PrintDoubleVector(const std::vector<double>& vec)
{
	if (std::size(vec) == 0)
	{
		return;
	}
	for (auto i = std::begin(vec); i != std::end(vec); i++)
	{
		std::cout << "|";
		std::cout.width(OUTPUT_WIDTH);
		std::cout.precision(OUTPUT_PRECISION);
		std::cout.right;
		std::cout << *i;
		std::cout << "|" << std::endl;
	}
	std::cout << std::endl;
}
