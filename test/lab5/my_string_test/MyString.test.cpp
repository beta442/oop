#include "../../../catch2/catch.hpp"

#include <sstream>

#include "../../../labs/lab5/my_string/headers/string/CMyString.h"

TEST_CASE("MyString constructed with 0 params")
{
	auto expectedStr = std::make_unique<char[]>(1);
	MyString str{};

	REQUIRE(str.GetLength() == 0);
	REQUIRE(str == expectedStr.get());
}

TEST_CASE("MyString constructed with char[]")
{
	WHEN("Created with not empty char[]")
	{
		const char* src = "asd";
		const MyString str{ src };
		THEN("MyString methods shows correct info")
		{
			REQUIRE(str.GetLength() == std::strlen(src));
			REQUIRE(std::strcmp(str.GetStringData(), src) == 0);
		}
	}

	WHEN("Created with empty char[]")
	{
		const char* src = "";
		const MyString str{ src };
		THEN("MyString is empty")
		{
			REQUIRE(str.GetLength() == std::strlen(src));
			REQUIRE(std::strcmp(str.GetStringData(), src) == 0);
		}
	}
}

TEST_CASE("MyString constructed with char[] and size params")
{
	const char* src = "asd";

	WHEN("Created with not empty char[], and size was smaller than size of provided char[]")
	{
		const size_t size = 2;
		const char* expectedStr = "as";
		const MyString str{ src, size };
		THEN("MyString methods shows correct info")
		{
			REQUIRE(str.GetLength() == size);
			REQUIRE(std::strcmp(str.GetStringData(), expectedStr) == 0);
		}
	}

	WHEN("Created with not empty char[], and size was greater than size of provided char[]")
	{
		const size_t size = 10;
		const char* expectedStr = "asd";
		const MyString str{ src, size };
		THEN("MyString methods shows correct info")
		{
			REQUIRE(str.GetLength() == size);
			REQUIRE(std::strcmp(str.GetStringData(), expectedStr) == 0);
		}
	}

	WHEN("Created with not empty char[], and size is equal to 0")
	{
		const size_t size = 0;
		const char* expectedStr = "";
		const MyString str{ src, size };
		THEN("MyString methods shows correct info")
		{
			REQUIRE(str.GetLength() == size);
			REQUIRE(std::strcmp(str.GetStringData(), expectedStr) == 0);
		}
	}

	WHEN("Created with char[] that contains 0-valued char in the middle, and size is equal to size of char[]")
	{
		const size_t size = 5;
		const char* middle0Str = new char[size]{ '1', '2', 0, '5' };
		const MyString str{ middle0Str, size };
		THEN("MyString represented correctly")
		{
			REQUIRE(str.GetLength() == size);
			REQUIRE(str == middle0Str);
		}
		delete[] middle0Str;
	}
}

TEST_CASE("MyString constructed with with std::string")
{
	WHEN("Provided string is empty")
	{
		const std::string src = "";
		const MyString str{ src };
		THEN("MyString represented correctly")
		{
			REQUIRE(str.GetLength() == src.size());
			REQUIRE(str == src);
		}
	}

	WHEN("Provided string isn't empty")
	{
		const std::string src = "12345";
		const MyString str{ src };
		THEN("MyString represented correctly")
		{
			REQUIRE(str.GetLength() == src.size());
			REQUIRE(str == src);
		}
	}
}

TEST_CASE("MyString constructed with other MyString")
{
	MyString strSrc{ "12345" };
	MyString str{ strSrc };

	REQUIRE(str == strSrc);
}

TEST_CASE("MyString construceted my move constructor")
{
	const char* expectedStr = "12345";
	MyString strSrc{ expectedStr };
	MyString str{ std::move(strSrc) };

	REQUIRE(str == expectedStr);
	REQUIRE(strSrc.GetLength() == 0);
	REQUIRE(strSrc == "");
}

TEST_CASE("MyString SubString() method test")
{
	const MyString str{ "0123456789" };

	WHEN("Start is greater than str's length")
	{
		const MyString res = str.SubString(500);
		THEN("SubString() returns empty string")
		{
			REQUIRE(res.GetLength() == 0);
			REQUIRE(res == "");
		}
	}

	WHEN("Start is in range of str")
	{
		const MyString res = str.SubString(2);
		THEN("SubString() returns str from start to end of str")
		{
			REQUIRE(res == "23456789");
		}
	}

	WHEN("Start and end is in range of str")
	{
		const MyString res = str.SubString(2, 5);
		THEN("SubString returns str from start to end")
		{
			REQUIRE(res == "23456");
		}
	}
}

TEST_CASE("Clear() method test")
{
	MyString str{ "12345" };
	str.Clear();

	REQUIRE(str == "");
	REQUIRE(str.GetLength() == 0);
}

TEST_CASE("Operator= test. MyString = MyString")
{
	const MyString src{ "12345" };
	MyString str = src;

	REQUIRE(str == src);
	REQUIRE(str.GetLength() == src.GetLength());
}

TEST_CASE("Operator+ test. MyString + MyString")
{
	const char* expectedStr = "1234512345";
	const MyString src{ "12345" };
	MyString str = src + src;

	REQUIRE(str == expectedStr);
	REQUIRE(str.GetLength() == std::strlen(expectedStr));
}

TEST_CASE("Opeartor+ test. MyString + std::string or std::string + MyString")
{
	const std::string src1 = "01234";
	const MyString src2{ "56789" };
	const MyString res1 = src1 + src2, res2 = src2 + src1;

	REQUIRE(res1 == "0123456789");
	REQUIRE(res2 == "5678901234");
}

TEST_CASE("Operator+ test. MyString + char[] or char[] + MyString")
{
	const char* src1 = "01234";
	const MyString src2{ "56789" };
	const MyString res1 = src1 + src2, res2 = src2 + src1;

	REQUIRE(res1 == "0123456789");
	REQUIRE(res2 == "5678901234");
}

TEST_CASE("Operator+= test. MyString += MyString")
{
	const MyString add{ "567890" };
	MyString dest{ "01234" };
	dest += add;

	REQUIRE(dest == "01234567890");
}

TEST_CASE("Operator== test")
{
	const MyString s1{}, s2{ "1234" }, s3{ "1234" };

	REQUIRE(s2 == s3);
	REQUIRE_FALSE(s1 == s2);
	REQUIRE_FALSE(s1 == s3);
}

TEST_CASE("Operator!= test")
{
	const MyString s1{}, s2{ "1234" }, s3{ "1234" };

	REQUIRE_FALSE(s2 != s3);
	REQUIRE(s1 != s2);
	REQUIRE(s1 != s3);
}

TEST_CASE("Operator< test")
{
	const MyString s1{ "123456" }, s2{ "12331" }, s3{ "54321" };

	REQUIRE(s1 < s3);
	REQUIRE(s2 < s1);
	REQUIRE(s2 < s3);
}

TEST_CASE("Operator> test")
{
	const MyString s1{ "123456" }, s2{ "12331" }, s3{ "54321" };

	REQUIRE(s3 > s1);
	REQUIRE(s1 > s2);
	REQUIRE(s3 > s2);
}

TEST_CASE("Operator<= test")
{
	const MyString s1{ "123456" }, s2{ "12331" }, s3{ "54321" };

	REQUIRE(s1 <= s3);
	REQUIRE(s2 <= s1);
	REQUIRE(s2 <= s3);
}

TEST_CASE("Operator>= test")
{
	const MyString s1{ "123456" }, s2{ "12331" }, s3{ "54321" };

	REQUIRE(s3 >= s1);
	REQUIRE(s1 >= s2);
	REQUIRE(s3 >= s2);
}

TEST_CASE("Read operator[] test")
{
	const MyString str{ "123456" };

	REQUIRE(str[0] == '1');
	REQUIRE(str[1] == '2');
	REQUIRE(str[2] == '3');
	REQUIRE(str[3] == '4');
	REQUIRE(str[5] == '6');
	REQUIRE(str[6] == 0);
}

TEST_CASE("Write operator[] test.")
{
	MyString str{ "1234567" };

	REQUIRE_FALSE(str[0] == str[2]);
	str[0] = str[2];
	REQUIRE(str[0] == str[2]);
}

TEST_CASE("Operator<< test")
{
	WHEN("Output stream in good state")
	{
		std::ostringstream os{};
		const std::string expectedResult = "123456";

		const MyString str{ expectedResult };

		THEN("Operator<< outputs MyString correctly")
		{
			os << str;
			REQUIRE(os.str() == expectedResult);
		}
	}

	WHEN("Output stream in bad state")
	{
		std::ostringstream os{};
		os.setstate(std::ios::badbit);
		const std::string expectedResult = "";

		const MyString str{ expectedResult };

		THEN("Operator<< doesn't change ostream content")
		{
			os << str;
			REQUIRE(os.str() == expectedResult);
		}
	}

	WHEN("Output stream in fail state")
	{
		std::ostringstream os{};
		os.setstate(std::ios::failbit);
		const std::string expectedResult = "";

		const MyString str{ expectedResult };

		THEN("Operator<< doesn't change ostream content")
		{
			os << str;
			REQUIRE(os.str() == expectedResult);
		}
	}
}

TEST_CASE("Operator>> test")
{
	WHEN("Input stream in bad or fail state")
	{
		const std::string expectedStreamContent = "123456";
		std::istringstream is{ expectedStreamContent };
		is.setstate(std::ios_base::failbit);
		is.setstate(std::ios_base::badbit);

		MyString str{};

		THEN("Operator>> doesn't change stream's content")
		{
			is >> str;
			REQUIRE(str == "");
			REQUIRE(is.str() == expectedStreamContent);
		}
	}

	WHEN("Input stream in correct state")
	{
		const std::string expectedStreamContent = "123456 1234";
		std::istringstream is{ expectedStreamContent };

		MyString str{};

		THEN("Operator>> works correctly")
		{
			is >> str;

			REQUIRE(str == "123456");
		}
	}
}
