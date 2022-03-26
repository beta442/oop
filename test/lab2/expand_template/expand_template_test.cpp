#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"

#include "../../../labs/lab2/expand_template/headers/expand_template.h"

SCENARIO("Boundary situations of using the ExpandTemplate function")
{
	using ParamsMap = std::map<std::string, std::string>;

	ParamsMap params;
	params["A"] = "[a]";
	params["AA"] = "[aa]";
	params["B"] = "[b]";
	params["BB"] = "[bb]";
	params["C"] = "[c]";
	params["CC"] = "[cc]";
	const ParamsMap copiedParams(params);

	ParamsMap emptyParamsMap{};
	const ParamsMap copiedEmptyParamsMap{ emptyParamsMap };

	WHEN("An empty string is processed, the result will be an empty string")
	{
		std::string emptyString = "";
		THEN("Result is empty string and given string and map are still the same")
		{
			std::string result = ExpandTemplate(emptyString, params);

			REQUIRE(std::size(result) == 0);

			REQUIRE(std::size(emptyString) == 0);
			REQUIRE(params == copiedParams);
		}
	}

	WHEN("Passing string with no templates in, the result will be the same string")
	{
		std::string stringWithNoTemplatesIn = "10% of 110 is 11. '{' is open bracket, but '}' is closing";
		const std::string savedTemplateString(stringWithNoTemplatesIn);
		THEN("Result is equal to given string and given map isn't changed")
		{
			std::string result = ExpandTemplate(stringWithNoTemplatesIn, params);

			REQUIRE(result == savedTemplateString);

			REQUIRE(stringWithNoTemplatesIn == savedTemplateString);
			REQUIRE(params == copiedParams);
		}
	}

	WHEN("Passing empty params map, the result will be the same string")
	{
		std::string regularString = "abcdef";
		const std::string savedRegularString(regularString);
		THEN("Result is equal to given string and given map isn't changed")
		{
			std::string result = ExpandTemplate(regularString, emptyParamsMap);

			REQUIRE(result == savedRegularString);

			REQUIRE(regularString == savedRegularString);
			REQUIRE(emptyParamsMap == copiedEmptyParamsMap);
		}
	}
}

SCENARIO("The given string has templates inside, which must be replaced according to given map")
{
	using ParamsMap = std::map<std::string, std::string>;

	ParamsMap paramsExampleFirst{
		{ "%USER_NAME%", "Ivan Petrov" },
		{ "{WEEK_DAY}", "Friday" },
	};
	const ParamsMap savedFirstParamsExample(paramsExampleFirst);

	ParamsMap paramsExampleRecursiveSecond{
		{ "%USER_NAME%", "Super %USER_NAME% {WEEK_DAY}" },
		{ "{WEEK_DAY}", "Friday. {WEEK_DAY}" }
	};
	const ParamsMap savedSecondParamsExample(paramsExampleRecursiveSecond);

	ParamsMap paramsExampleThird{
		{ "A", "[a]" },
		{ "AA", "[aa]" },
		{ "B", "[b]" },
		{ "BB", "[bb]" },
		{ "C", "[c]" },
		{ "CCC", "[ccc]" },
		{ "CCAB", "[ccab]" },
		{ "CA", "[ca]" },
	};
	const ParamsMap savedThridParamsExample(paramsExampleThird);

	WHEN("Search substrings doesn't intersect and insertion values doesn't contain search substrings")
	{
		std::string tpl = "Hello, %USER_NAME%. Today is {WEEK_DAY}.";
		const std::string savedTpl{ tpl };
		const std::string expectedResult = "Hello, Ivan Petrov. Today is Friday.";

		THEN("All substrings replaced correctly. No changes in given string. No changes in given paramsMap")
		{
			std::string result = ExpandTemplate(tpl, paramsExampleFirst);

			REQUIRE(result == expectedResult);

			REQUIRE(tpl == savedTpl);
			REQUIRE(paramsExampleFirst == savedFirstParamsExample);
		}
	}

	WHEN("Search substrings are represented in insertion values")
	{
		std::string tpl = "Hello, %USER_NAME%. Today is {WEEK_DAY}.";
		const std::string savedTpl{ tpl };
		const std::string expectedResult = "Hello, Super %USER_NAME% {WEEK_DAY}. Today is Friday. {WEEK_DAY}.";

		THEN("All substrings replaced only once. No changes in given string. No changes in given paramsMap")
		{
			std::string result = ExpandTemplate(tpl, paramsExampleRecursiveSecond);

			REQUIRE(result == expectedResult);

			REQUIRE(tpl == savedTpl);
			REQUIRE(paramsExampleRecursiveSecond == savedSecondParamsExample);
		}
	}

	WHEN("Search substrings are intersecting each other")
	{
		std::string tpl = "-AABBCCCCCABC+";
		const std::string savedTpl{ tpl };
		const std::string expectedResult = "-[aa][bb][ccc][ccab][c]+";

		THEN("Replaced only the longest substrings. No changes in given string. No changes in given paramsMap")
		{
			std::string result = ExpandTemplate(tpl, paramsExampleThird);

			REQUIRE(result == expectedResult);

			REQUIRE(tpl == savedTpl);
			REQUIRE(paramsExampleThird == savedThridParamsExample);
		}
	}

	WHEN("Search substrings are intersecting each other and they are shuffled in expanding string. For example here: The prefix set for CCAB, CCC has been broken off on first B, the collected prefix may consist of substrings for searching")
	{
		std::string tpl = "-CCBCCCAABBABC+";
		ParamsMap paramsExampleThird1{
			{ "CCAB", "[ccab]" },
			{ "CCC", "[ccc]" },
			{ "AA", "[aa]" },
			{ "BB", "[bb]" },
			{ "CA", "[ca]" },
			{ "A", "[a]" },
			{ "B", "[b]" },
			{ "C", "[c]" },
		};
		const std::string savedTpl{ tpl };
		const std::string expectedResult = "-[c][c][b][ccc][aa][bb][a][b][c]+";

		THEN("Collected fail-prefix expanded correctly")
		{
			std::string result = ExpandTemplate(tpl, paramsExampleThird);

			REQUIRE(result == expectedResult);

			REQUIRE(tpl == savedTpl);
			REQUIRE(paramsExampleThird == savedThridParamsExample);
		}
	}
}
