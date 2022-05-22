#include "../pch.h"

#include "../../../../labs/lab7/find_max_ex/headers/FindMaxEx/FindMaxEx.hpp"
#include <functional>

TEST_CASE("FindMax test on int array")
{
	using Data = int;

	const Data expectedMaxValue = 1010;
	const std::vector<Data> vec{ -100, 200, 12, 99, 156, -1000, expectedMaxValue };
	const std::vector<Data> emptyVec{};
	Data result = 0;

	REQUIRE_FALSE(FindMax<Data>(emptyVec, result));
	REQUIRE(result == 0);

	REQUIRE(FindMax<Data>(vec, result));
	REQUIRE(result == expectedMaxValue);
}

TEST_CASE("FindMax test on double array")
{
	using Data = double;

	const Data expectedMaxValue = 1010.11;
	const std::vector<Data> vec{ -100, 200.123123, 12, 99, 156, -1000e25, expectedMaxValue };
	const std::vector<Data> emptyVec{};
	Data result = 0;

	REQUIRE_FALSE(FindMax<Data>(emptyVec, result));
	REQUIRE(result == 0);

	REQUIRE(FindMax<Data>(vec, result));
	REQUIRE(result == expectedMaxValue);
}

TEST_CASE("FindMax test on string array")
{
	using Data = std::string;

	const Data expectedMaxValue = "9876543210";
	const std::vector<Data> vec{ "", "0", "01234567890", "123", expectedMaxValue };
	const std::vector<Data> emptyVec{};
	Data result = "";

	REQUIRE_FALSE(FindMax<Data>(emptyVec, result));
	REQUIRE(result == "");

	REQUIRE(FindMax<Data>(vec, result));
	REQUIRE(result == expectedMaxValue);
}

TEST_CASE("FindMax test on char* array")
{
	using Data = const char*;

	const Data expectedMaxValue = "9876543210";
	const std::vector<Data> vec{ "", "0", "01234567890", "123", expectedMaxValue };
	const std::vector<Data> emptyVec{};
	Data result = "";

	REQUIRE_FALSE(FindMax<Data>(emptyVec, result));
	REQUIRE(result == "");

	REQUIRE(FindMax<Data>(vec, result));
	REQUIRE(result == expectedMaxValue);
}

class Sportsman
{
public:
	Sportsman(const std::string& name, unsigned short height, unsigned short weight)
		: m_name(name)
		, m_height(height)
		, m_weight(weight)
	{
	}

	std::string m_name;
	unsigned short m_height;
	unsigned short m_weight;
};

static inline bool SportsmenWeightMaxCmp(const Sportsman& lhs, const Sportsman& rhs)
{
	return lhs.m_weight < rhs.m_weight;
}

static inline bool SportsmenHeightMaxCmp(const Sportsman& lhs, const Sportsman& rhs)
{
	return lhs.m_height < rhs.m_height;
}

TEST_CASE("FindMaxEs test")
{
	using ComporatorType = std::function<bool(const Sportsman&, const Sportsman&)>;

	const std::string expectedWithMaximumHeight = "John Doe4";
	const unsigned short expectedMaxHeightSportsmanHeight = 200;
	const unsigned short expectedMaxHeightSportsmanWeight = 105;
	const std::string expectedWithMaximumWeight = "John Doe1";
	const unsigned short expectedMaxWeightSportsmanHeight = 190;
	const unsigned short expectedMaxWeightSportsmanWeight = 110;
	const std::vector<Sportsman> sportsmen{
		{ expectedWithMaximumWeight, expectedMaxWeightSportsmanHeight, expectedMaxWeightSportsmanWeight },
		{ "John Doe2", 150, 100 },
		{ "John Doe3", 160, 50 },
		{ expectedWithMaximumHeight, expectedMaxHeightSportsmanHeight, expectedMaxHeightSportsmanWeight }
	};
	const std::vector<Sportsman> emptyVec{};

	Sportsman result = { "", 0, 0 };
	REQUIRE_FALSE(FindMax<Sportsman, ComporatorType>(emptyVec, result, SportsmenWeightMaxCmp));
	REQUIRE_FALSE(FindMax<Sportsman, ComporatorType>(emptyVec, result, SportsmenHeightMaxCmp));
	REQUIRE(result.m_name == "");
	REQUIRE(result.m_height == 0);
	REQUIRE(result.m_weight == 0);

	REQUIRE(FindMax<Sportsman, ComporatorType>(sportsmen, result, SportsmenWeightMaxCmp));
	REQUIRE(result.m_name == expectedWithMaximumWeight);
	REQUIRE(result.m_height == expectedMaxWeightSportsmanHeight);
	REQUIRE(result.m_weight == expectedMaxWeightSportsmanWeight);
	
	REQUIRE(FindMax<Sportsman, ComporatorType>(sportsmen, result, SportsmenHeightMaxCmp));
	REQUIRE(result.m_name == expectedWithMaximumHeight);
	REQUIRE(result.m_height == expectedMaxHeightSportsmanHeight);
	REQUIRE(result.m_weight == expectedMaxHeightSportsmanWeight);
}
