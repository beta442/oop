#include "../pch.h"

#include "../../../../labs/lab7/my_list/headers/MyList/MyList.hpp"

using Data = std::string;

TEST_CASE("MyList. PushBack() test")
{
	MyList<Data> list;

	REQUIRE(list.Size() == 0);
	REQUIRE(list.Empty());

	list.PushBack("1");
	Data s = "2";
	const Data cs = "3";
	list.PushBack(s);
	list.PushBack(cs);

	REQUIRE(list.Size() == 3);
	REQUIRE_FALSE(list.Empty());

	const MyListIterator it1 = list.begin(),
					   it2 = ++list.begin(),
					   it3 = --list.end();

	REQUIRE(*it1 == "1");
	REQUIRE(*it2 == s);
	REQUIRE(*it3 == cs);
}

TEST_CASE("MyList. PushFront() test")
{
	MyList<Data> list;

	REQUIRE(list.Size() == 0);
	REQUIRE(list.Empty());

	list.PushFront("3");
	Data s = "2";
	const Data cs = "1";
	list.PushFront(s);
	list.PushFront(cs);

	REQUIRE(list.Size() == 3);
	REQUIRE_FALSE(list.Empty());

	const MyListIterator it1 = list.begin(),
					   it2 = ++list.begin(),
					   it3 = --list.end();

	REQUIRE(*it1 == cs);
	REQUIRE(*it2 == s);
	REQUIRE(*it3 == "3");
}

TEST_CASE("MyList. Clear() test")
{
	MyList<Data> list;

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

TEST_CASE("MyList. Removing element with iterator test")
{
	MyList<Data> list;

	const Data erasingEl = "3";
	list.PushBack("1");
	list.PushBack("2");
	list.PushBack(erasingEl);
	list.PushBack("4");
	list.PushBack("5");

	const MyListIterator it3 = ++(++(list.begin()));

	REQUIRE(list.Size() == 5);
	const auto it = list.Erase(it3);
	REQUIRE(list.Size() == 4);

	for (auto it = std::begin(list), end = std::end(list); it != end; ++it)
	{
		REQUIRE_FALSE(*it == erasingEl);
	}

	REQUIRE(*it == "4");
}

TEST_CASE("MyList. Emplacing element with iterator test")
{
	MyList<Data> list;

	const Data emplacingEl = "0";
	list.PushBack("1");
	list.PushBack("2");
	list.PushBack("3");
	list.PushBack("4");
	list.PushBack("5");

	const MyListIterator it3 = ++(++(list.begin()));

	REQUIRE(list.Size() == 5);
	auto it = list.Emplace(it3, emplacingEl);
	REQUIRE(list.Size() == 6);

	REQUIRE(*(++it) == "3");
	REQUIRE(*(--it) == emplacingEl);
	REQUIRE(*(--it) == "2");
}

TEST_CASE("MyList. Exceptions test")
{
	MyList<Data> list;

	const size_t listSize = 100;
	for (size_t i = 0; i < listSize; ++i)
	{
		list.PushBack(std::to_string(i));
	}

	REQUIRE_THROWS_AS(list.Emplace(--std::begin(list), "1"), std::out_of_range);
	REQUIRE_THROWS_AS(list.Erase(--std::begin(list)), std::out_of_range);
	REQUIRE_THROWS_AS(list.Erase(std::end(list)), std::out_of_range);
}

TEST_CASE("List. Move constructor")
{
	MyList<Data> list;

	const size_t listSize = 10;
	for (size_t i = 0; i < listSize; ++i)
	{
		list.PushBack(std::to_string(i));
	}

	REQUIRE(list.Size() == listSize);
	REQUIRE_FALSE(list.Empty());

	MyList<Data> newList{ std::move(list) };

	REQUIRE(list.Size() == 0);
	REQUIRE(list.Empty());

	REQUIRE(newList.Size() == listSize);
	REQUIRE_FALSE(newList.Empty());
}

TEST_CASE("List. Copy constructor")
{
	MyList<Data> list;

	const size_t listSize = 10;
	for (size_t i = 0; i < listSize; ++i)
	{
		list.PushBack(std::to_string(i));
	}

	REQUIRE(list.Size() == listSize);
	REQUIRE_FALSE(list.Empty());

	MyList<Data> newList{ list };

	REQUIRE(list.Size() == listSize);
	REQUIRE_FALSE(list.Empty());

	REQUIRE(newList.Size() == listSize);
	REQUIRE_FALSE(newList.Empty());
}
