#include "headers/std_lib.h"

#include "headers/prime_generator.h"

std::optional<int> ParseArgs(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cout << "Invalid usage:" << std::endl
				  << "PROGRAM.exe <uppervalue> | uppervalue is positive integer up to 1e8" << std::endl;
		return std::nullopt;
	}

	std::stringstream ss{ argv[1] };
	int upperValue;
	ss >> upperValue;
	if (ss.fail())
	{
		std::cout << "Invalid argument value" << std::endl
				  << "Usage:" << std::endl
				  << "PROGRAM.exe <uppervalue> | uppervalue is positive integer up to 1e8" << std::endl;
		return std::nullopt;
	}

	return std::optional<int>{ upperValue };
}

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
