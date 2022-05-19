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
