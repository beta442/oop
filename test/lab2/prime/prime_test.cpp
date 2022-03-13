#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"

#include "prime.h"

SCENARIO("Trying generate set of positive primes with different function's upperBound param")
{
	WHEN("Given value is lower than 0")
	{
		const std::set<int> set = GeneratePrimeNumbersSet(-10);
		THEN("Set is empty")
		{
			REQUIRE(set.empty());
		}
	}

	WHEN("Given value is 0")
	{
		const std::set<int> set = GeneratePrimeNumbersSet(0);
		THEN("Set is empty")
		{
			REQUIRE(set.empty());
		}
	}

	WHEN("Given value is 1e8")
	{
		const std::set<int> set = GeneratePrimeNumbersSet(100000000);
		THEN("Set has exactly 5761455 prime numbers")
		{
			REQUIRE(set.size() == 5761455);
		}
	}
}
