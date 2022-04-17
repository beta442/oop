#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"

#include "../../../labs/lab3/calculator/headers/calculator/calculator.h"

SCENARIO("Calculator at created state")
{
	Calculator calculator;

	WHEN("Calculator created, it hasn't any declarated variable")
	{
		const std::ostringstream expectedResult{};
		std::ostringstream output{};
		
		calculator.PrintVariables(output);

		THEN("Calculator hasn't any variable")
		{
			REQUIRE(expectedResult.str() == output.str());
		}
	}
}

SCENARIO("Adding some variables")
{
	Calculator calculator;
	std::ostringstream output{};

	SECTION("Not initialized at declaration")
	{
		std::string varName = "Var";
		const std::ostringstream expectingResult{ "Var=nan\n" };
		std::ostringstream output{};

		calculator.DeclareVariable(varName);
		calculator.PrintVariables(output);

		REQUIRE(expectingResult.str() == output.str());
	}
}
