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

SCENARIO("Adding some not initialized variables")
{
	Calculator calculator;
	std::ostringstream output{};

	SECTION("Unsorted adding")
	{
		std::string varName = "B";
		std::string varNameSecond = "A";
		const std::ostringstream expectingResult{ "A:nan\nB:nan\n" };
		std::ostringstream output{};

		WHEN("Printing variables added not in lexicographic order")
		{
			calculator.DeclareVariable(varName);
			calculator.DeclareVariable(varNameSecond);
			calculator.PrintVariables(output);

			THEN("outputs them sorted")
			{
				REQUIRE(expectingResult.str() == output.str());
			}
		}
	}

	SECTION("Can't redeclare already declarated variable")
	{
		std::string varName = "Var";
		std::ostringstream output{};

		WHEN("Variable already declarated")
		{
			REQUIRE(calculator.DeclareVariable(varName));
			THEN("Can't redeclare it")
			{
				REQUIRE(!calculator.DeclareVariable(varName));
			}
		}
	}

	SECTION("Printing value of certain declarated not initialized variable")
	{
		std::string varName = "Var";
		const std::ostringstream expectingResult{ "Var:nan\n" };
		std::ostringstream output{};

		WHEN("Variable doesn't exists")
		{
			THEN("Calculator can't print it")
			{
				REQUIRE(!calculator.PrintVariable(varName, output));

				REQUIRE(std::size(output.str()) == 0);
			}
		}
		
		WHEN("Variable declarated")
		{
			calculator.DeclareVariable(varName);
			THEN("Calculator can prints it")
			{
				REQUIRE(calculator.PrintVariable(varName, output));

				REQUIRE(expectingResult.str() == output.str());
			}
		}

	}
}
