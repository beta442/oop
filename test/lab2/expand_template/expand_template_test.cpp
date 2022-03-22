#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"

#include "../../../labs/lab2/expand_template/expand_template.h"

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

			REQUIRE(std::size(result) == std::size(savedTemplateString));

			REQUIRE(std::size(stringWithNoTemplatesIn) == std::size(savedTemplateString));
			REQUIRE(params == copiedParams);
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
		{ "CC", "[cc]" },
	};
	const ParamsMap savedThridParamsExample(paramsExampleThird);

	WHEN("")
	{
	}
}
