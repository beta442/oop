#include "../pch.h"

#include "../../../../labs/lab6/string_list/headers/List/List.hpp"

using Data = std::string;

TEST_CASE("ListIterator tests")
{
	List<Data> list;

	const size_t listSize = 100;
	for (size_t i = 0; i < listSize; ++i)
	{
		list.PushBack(std::to_string(i));
	}

	size_t i = 0;
	for (auto it = std::begin(list), end = std::end(list); it != end; ++it, ++i)
	{
		REQUIRE(*it == std::to_string(i));
	}

	i = list.Size() - 1;
	for (auto it = std::rbegin(list), end = std::rend(list); it != end; ++it, --i)
	{
		REQUIRE(*it == std::to_string(i));
	}

	i = 0;
	for (auto& s : list)
	{
		REQUIRE(s == std::to_string(i++));
	}
}

TEST_CASE("ListIterator exception tests")
{
	List<Data> list;

	const size_t listSize = 100;
	for (size_t i = 0; i < listSize; ++i)
	{
		list.PushBack(std::to_string(i));
	}

	REQUIRE_THROWS_AS(*(--list.begin()), std::out_of_range);
	REQUIRE_THROWS_AS(*list.end(), std::out_of_range);
	REQUIRE_THROWS_AS((--list.begin()).operator->(), std::out_of_range);
	REQUIRE_THROWS_AS(list.end().operator->(), std::out_of_range);

	auto headIt = --std::begin(list);
	REQUIRE_THROWS_AS(--(headIt), std::out_of_range);
	REQUIRE_THROWS_AS(++list.end(), std::out_of_range);
}
