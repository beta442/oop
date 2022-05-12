#include "../pch.h"

#include "../../../../labs/lab5/my_string/headers/string/CMyStringIterator.h"

TEST_CASE("MyStringConstIterator test")
{
	const MyString constString{ "0123456789" };
	auto beg = std::begin(constString), end = std::end(constString);
	REQUIRE(*beg == '0');
	REQUIRE(*end == '\0');
	REQUIRE(beg.operator->() == constString.GetStringData());
	REQUIRE(end.operator->() == constString.GetStringData() + constString.GetLength());

	auto temp = beg;
	{
		temp = beg;
		++temp;
		REQUIRE(*temp == '1');
		temp = end;
		--temp;
		REQUIRE(*temp == '9');
	}

	{
		temp = beg++;
		REQUIRE(*beg == '1');
		REQUIRE(*temp == '0');
		temp = end--;
		REQUIRE(*end == '9');
		REQUIRE(*temp == '\0');
		--beg;
		++end;
	}

	{
		temp = beg + 3;
		REQUIRE(*temp == '3');
		temp = end - 5;
		REQUIRE(*temp == '5');
	}

	{
		temp = beg;
		temp += 3;
		REQUIRE(*temp == '3');
		temp = end;
		temp -= 5;
		REQUIRE(*temp == '5');
	}

	{
		auto difference = end - beg;
		REQUIRE(difference == constString.GetLength());
	}

	{
		REQUIRE_FALSE(beg == end);
		REQUIRE(beg != end);
		REQUIRE(beg < end);
		REQUIRE_FALSE(beg > end);
		REQUIRE(beg <= end);
		REQUIRE(end <= end);
		REQUIRE_FALSE(beg > end);
		REQUIRE_FALSE(beg >= end);
		REQUIRE(end > beg);
		REQUIRE(end >= beg);
		REQUIRE(end >= end);
	}
}

TEST_CASE("MyStringIterator test")
{
	MyString string{ "0123456789" };
	auto beg = std::begin(string), end = std::end(string);
	REQUIRE(*beg == '0');
	REQUIRE(*end == '\0');
	REQUIRE(beg.operator->() == string.GetStringData());
	REQUIRE(end.operator->() == string.GetStringData() + string.GetLength());

	auto temp = beg;
	{
		temp = beg;
		++temp;
		REQUIRE(*temp == '1');
		temp = end;
		--temp;
		REQUIRE(*temp == '9');
	}

	{
		temp = beg++;
		REQUIRE(*beg == '1');
		REQUIRE(*temp == '0');
		temp = end--;
		REQUIRE(*end == '9');
		REQUIRE(*temp == '\0');
		--beg;
		++end;
	}

	{
		temp = beg + 3;
		REQUIRE(*temp == '3');
		temp = end - 5;
		REQUIRE(*temp == '5');
	}

	{
		temp = beg;
		temp += 3;
		REQUIRE(*temp == '3');
		temp = end;
		temp -= 5;
		REQUIRE(*temp == '5');
	}

	{
		auto difference = end - beg;
		REQUIRE(difference == string.GetLength());
	}

	{
		REQUIRE(beg[5] == '5');
		beg[5] = '0';
		REQUIRE(beg[5] == '0');
	}
}

TEST_CASE("MyStringConstReverseIterator test")
{
	const MyString constString{ "0123456789" };
	auto beg = std::rbegin(constString), end = std::rend(constString);
	REQUIRE(*beg == '9');
	REQUIRE(*(end - 1) == '0');
	REQUIRE(beg.operator->() == constString.GetStringData() + constString.GetLength() - 1);
	REQUIRE((end - 1).operator->() == constString.GetStringData());

	auto temp = beg;
	{
		temp = end;
		--temp;
		REQUIRE(*temp == '0');
		temp = beg;
		++temp;
		REQUIRE(*temp == '8');
	}

	{
		temp = beg++;
		REQUIRE(*beg == '8');
		REQUIRE(*temp == '9');
		temp = end--;
		REQUIRE(*end == '0');
		REQUIRE(*(temp - 1) == '0');
		--beg;
		++end;
	}

	{
		temp = beg + 3;
		REQUIRE(*temp == '6');
		temp = end - 5;
		REQUIRE(*temp == '4');
	}

	{
		temp = beg;
		temp += 3;
		REQUIRE(*temp == '6');
		temp = end;
		temp -= 5;
		REQUIRE(*temp == '4');
	}

	{
		auto difference = end - beg;
		REQUIRE(difference == constString.GetLength());
	}

	{
		REQUIRE_FALSE(beg == end);
		REQUIRE(beg != end);
		REQUIRE(beg < end);
		REQUIRE_FALSE(beg > end);
		REQUIRE(beg <= end);
		REQUIRE(end <= end);
		REQUIRE_FALSE(beg > end);
		REQUIRE_FALSE(beg >= end);
		REQUIRE(end > beg);
		REQUIRE(end >= beg);
		REQUIRE(end >= end);
	}
}

TEST_CASE("MyStringReverseIterator test")
{
	MyString string{ "0123456789" };
	auto beg = std::rbegin(string), end = std::rend(string);
	REQUIRE(*beg == '9');
	REQUIRE(*(end - 1) == '0');
	REQUIRE(beg.operator->() == string.GetStringData() + string.GetLength() - 1);
	REQUIRE((end - 1).operator->() == string.GetStringData());

	auto temp = beg;
	{
		temp = end;
		--temp;
		REQUIRE(*temp == '0');
		temp = beg;
		++temp;
		REQUIRE(*temp == '8');
	}

	{
		temp = beg++;
		REQUIRE(*beg == '8');
		REQUIRE(*temp == '9');
		temp = end--;
		REQUIRE(*end == '0');
		REQUIRE(*(temp - 1) == '0');
		--beg;
		++end;
	}

	{
		temp = beg + 3;
		REQUIRE(*temp == '6');
		temp = end - 5;
		REQUIRE(*temp == '4');
	}

	{
		temp = beg;
		temp += 3;
		REQUIRE(*temp == '6');
		temp = end;
		temp -= 5;
		REQUIRE(*temp == '4');
	}

	{
		auto difference = end - beg;
		REQUIRE(difference == string.GetLength());
	}
}
