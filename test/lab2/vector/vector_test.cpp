#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"

#include "vector.h"

SCENARIO("Trying to read double from stream, that contains bad values, into vector does nothing to vector")
{
	std::vector<double> vec;
	vec.reserve(1);
	vec.push_back(12);

	WHEN("Istream is empty")
	{
		std::istringstream istream;
		CopyStreamOfDoubleIntoVector(istream, vec);

		REQUIRE(std::size(vec) == 1);
		REQUIRE(vec[0] == 12);
		REQUIRE(istream.eof());
	}

	WHEN("Istream contains only bad(not double) values")
	{
		std::istringstream istream{ 'a' };
		THEN("Vector is still the same")
		{
			CopyStreamOfDoubleIntoVector(istream, vec);

			REQUIRE(std::size(vec) == 1);
			REQUIRE(vec[0] == 12);
		}
	}

	WHEN("Istream contains good and bad values")
	{
		std::istringstream istream{ "1, 45 90 a 60" };

		THEN("Vector is still the same")
		{
			CopyStreamOfDoubleIntoVector(istream, vec);

			REQUIRE(std::size(vec) == 1);
			REQUIRE(vec[0] == 12);
			REQUIRE(!istream.eof());
		}
	}

	WHEN("Istream contains too big double")
	{
		std::istringstream istream{ "4e9999" };

		THEN("Vector is still the same")
		{
			CopyStreamOfDoubleIntoVector(istream, vec);

			REQUIRE(std::size(vec) == 1);
			REQUIRE(vec[0] == 12);
		}
	}
}

SCENARIO("If istream contains good values (convertable to double type)")
{
	std::vector<double> vec;

	WHEN("Istream contains only one number")
	{
		std::istringstream istream{ "999" };

		THEN("Vector contains istream's number")
		{
			CopyStreamOfDoubleIntoVector(istream, vec);

			REQUIRE(std::size(vec) == 1);
			REQUIRE(vec[0] == 999);
			REQUIRE(istream.eof());
		}
	}

	WHEN("Istream contains numbers with float point")
	{
		std::istringstream istream{ "999.15 -564.3" };

		THEN("Vector contains istream's float numbers")
		{
			CopyStreamOfDoubleIntoVector(istream, vec);

			REQUIRE(std::size(vec) == 2);
			REQUIRE(vec[0] == 999.15);
			REQUIRE(vec[1] == -564.3);
			REQUIRE(istream.eof());
		}
	}

	WHEN("Istream contains value in scientific notation")
	{
		std::istringstream istream{ "999e20" };

		THEN("Vector contains istream's float numbers")
		{
			CopyStreamOfDoubleIntoVector(istream, vec);

			REQUIRE(std::size(vec) == 1);
			REQUIRE(vec[0] == 999e20);
			REQUIRE(istream.eof());
		}
	}
}
