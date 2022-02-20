#include <algorithm>
#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>

std::vector<double> GetFromStreamDoubleVector(std::istream& fIn);
void MutateDoubleVectorByTask(std::vector<double>& vec);
void PrintVector(const std::vector<double>& vec);

int main()
{
	std::vector<double> vec = GetFromStreamDoubleVector(std::cin);
	std::cout << "Input arr:" << std::endl;
	PrintVector(vec);
	MutateDoubleVectorByTask(vec);
	std::cout << "Input arr now:" << std::endl;
	PrintVector(vec);
}

constexpr char DELIMETER = ' ';

std::vector<double> GetFromStreamDoubleVector(std::istream& fIn)
{
	std::vector<double> result{};
	std::istream_iterator<double> numbers{ fIn }, eof;

	std::copy(numbers, eof, std::back_inserter(result));

	if (!fIn.eof())
	{
		// TODO access to invalid value?
		std::cout << "Invalid value was given:" << std::endl;
		exit(EXIT_FAILURE);
	}

	return result;
}

void MutateDoubleVectorByTask(std::vector<double>& vec)
{
	if (vec.size() == 0)
	{
		return;
	}
	std::vector<double>::const_iterator minElementIt = std::min_element(vec.begin(), vec.end());

	std::cout << "minValue:" << *minElementIt << std::endl;

	for (auto& val : vec)
	{
		val *= *minElementIt;
	}
}

void PrintVector(const std::vector<double>& vec)
{
	std::vector<double> sortedVec = vec;
	std::sort(sortedVec.begin(), sortedVec.end());
	std::vector<double>::const_iterator it = sortedVec.begin();
	std::cout << "|";
	for (auto i = it; i != sortedVec.end(); i++)
	{
		printf("%+.3f|", *i);
	}
	std::cout << std::endl;
}
