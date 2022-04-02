#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"

#include "../../../labs/lab2/vector/headers/vector.h"

SCENARIO("Trying to read double from stream, that contains bad values, into vector does nothing to vector")
{
	std::vector<double> vec;
	vec.reserve(1);
	const double firstValue = 12;
	vec.push_back(firstValue);
	const std::size_t vecSize = std::size(vec);

	WHEN("Istream is empty")
	{
		std::istringstream istream;
		
		CopyStreamOfDoubleIntoVector(istream, vec);

		THEN("Vector is still the same")
		{
			REQUIRE(std::size(vec) == vecSize);
			REQUIRE(vec[0] == firstValue);
			REQUIRE(istream.eof());
		}
	}

	WHEN("Istream contains only bad(not double) values")
	{
		std::istringstream istream{ 'a' };

		CopyStreamOfDoubleIntoVector(istream, vec);

		THEN("Vector is still the same")
		{
			REQUIRE(std::size(vec) == vecSize);
			REQUIRE(vec[0] == firstValue);
		}
	}

	WHEN("Istream contains good and bad values")
	{
		std::istringstream istream{ "1, 45 90 a 60" };

		CopyStreamOfDoubleIntoVector(istream, vec);

		THEN("Vector is still the same")
		{
			REQUIRE(std::size(vec) == vecSize);
			REQUIRE(vec[0] == firstValue);
			REQUIRE(!istream.eof());
		}
	}

	WHEN("Istream contains too big double")
	{
		std::istringstream istream{ "4e9999" };

		CopyStreamOfDoubleIntoVector(istream, vec);

		THEN("Vector is still the same")
		{
			REQUIRE(std::size(vec) == vecSize);
			REQUIRE(vec[0] == firstValue);
		}
	}
}

SCENARIO("If istream contains good values (convertable to double type)")
{
	std::vector<double> vec;

	WHEN("Istream contains only one number")
	{
		std::istringstream istream{ "999" };

		CopyStreamOfDoubleIntoVector(istream, vec);

		THEN("Vector contains istream's number")
		{
			REQUIRE(std::size(vec) == 1);
			REQUIRE(vec[0] == 999);
			REQUIRE(istream.eof());
		}
	}

	WHEN("Istream contains numbers with float point")
	{
		std::istringstream istream{ "999.15 -564.3" };

		CopyStreamOfDoubleIntoVector(istream, vec);

		THEN("Vector contains istream's float numbers")
		{
			REQUIRE(std::size(vec) == 2);
			REQUIRE(vec[0] == 999.15);
			REQUIRE(vec[1] == -564.3);
			REQUIRE(istream.eof());
		}
	}

	WHEN("Istream contains value in scientific notation")
	{
		std::istringstream istream{ "999e20" };

		CopyStreamOfDoubleIntoVector(istream, vec);

		THEN("Vector contains istream's float numbers")
		{
			REQUIRE(std::size(vec) == 1);
			REQUIRE(vec[0] == 999e20);
			REQUIRE(istream.eof());
		}
	}
}

SCENARIO("We have vector filled with doubles and trying to process it by given task")
{
	std::vector<double> vec = { -2, -2, 0, 4, 9 };
	const std::size_t vecSize = std::size(vec);

	WHEN("We trying to multiply each element in vector by minElement(vec)")
	{
		ProcessVectorOfDoubleByTask(vec);

		THEN("Vector has correct size and values")
		{
			REQUIRE(vecSize == std::size(vec));
			REQUIRE(vec[0] == 4);
			REQUIRE(vec[1] == 4);
			REQUIRE(vec[2] == 0);
			REQUIRE(vec[3] == -8);
			REQUIRE(vec[4] == -18);
		}
	}
}

SCENARIO("We have empty vector and excpecting no changes while processing it by given task")
{
	std::vector<double> vec{};

	WHEN("We trying to multiply each element in vector by minElement(vec), but vector is empty")
	{
		ProcessVectorOfDoubleByTask(vec);

		THEN("Vector is empty")
		{
			REQUIRE(std::size(vec) == 0);
		}
	}
}
