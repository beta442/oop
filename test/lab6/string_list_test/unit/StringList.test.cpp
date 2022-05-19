#include "../pch.h"

#include "../../../../labs/lab6/string_list/headers/List/List.hpp"

using Data = std::string;

TEST_CASE("List. PushBack() test")
{
	List<Data> list;

	REQUIRE(list.Size() == 0);
	REQUIRE(list.Empty());

	list.PushBack("1");
	Data s = "2";
	const Data cs = "3";
	list.PushBack(s);
	list.PushBack(cs);

	REQUIRE(list.Size() == 3);
	REQUIRE_FALSE(list.Empty());

	const ListIterator it1 = list.begin(),
					   it2 = ++list.begin(),
					   it3 = --list.end();

	REQUIRE(*it1 == "1");
	REQUIRE(*it2 == s);
	REQUIRE(*it3 == cs);
}

TEST_CASE("List. PushFront() test")
{
	List<Data> list;

	REQUIRE(list.Size() == 0);
	REQUIRE(list.Empty());

	list.PushFront("3");
	Data s = "2";
	const Data cs = "1";
	list.PushFront(s);
	list.PushFront(cs);

	REQUIRE(list.Size() == 3);
	REQUIRE_FALSE(list.Empty());

	const ListIterator it1 = list.begin(),
					   it2 = ++list.begin(),
					   it3 = --list.end();

	REQUIRE(*it1 == cs);
	REQUIRE(*it2 == s);
	REQUIRE(*it3 == "3");
}

TEST_CASE("List. Clear() test")
{
	List<Data> list;

	const size_t listSize = 1000000;
	for (size_t i = 0; i < listSize; ++i)
	{
		list.PushBack("0");
	}

	REQUIRE_FALSE(list.Empty());
	REQUIRE(list.Size() == listSize); 

	list.Clear();

	REQUIRE(list.Empty());
	REQUIRE(list.Size() == 0);
}

TEST_CASE("List. Removing element with iterator test")
{
	List<Data> list;

	const Data erasingEl = "3";
	list.PushBack("1");
	list.PushBack("2");
	list.PushBack(erasingEl);
	list.PushBack("4");
	list.PushBack("5");

	const ListIterator it3 = ++(++(list.begin()));

	REQUIRE(list.Size() == 5);
	const auto it = list.Erase(it3);
	REQUIRE(list.Size() == 4);

	for (auto it = std::begin(list), end = std::end(list); it != end; ++it)
	{
		REQUIRE_FALSE(*it == erasingEl);
	}

	REQUIRE(*it == "4");
}
