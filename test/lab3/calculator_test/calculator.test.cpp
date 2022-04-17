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

	SECTION("Wrong named variables adding")
	{
		const std::string emptyVarName = "";
		const std::string incorrectVarNameStartsWithNumber = "1";
		const std::string incorrectVarNameIncludesNotOnlyLettersAndDigits = "Aadb!@#";

		WHEN("Variables named incorrectly")
		{
			THEN("Attempt to add variable fails")
			{
				REQUIRE(!calculator.DeclareVariable(emptyVarName));
				REQUIRE(!calculator.DeclareVariable(incorrectVarNameStartsWithNumber));
				REQUIRE(!calculator.DeclareVariable(incorrectVarNameIncludesNotOnlyLettersAndDigits));
			}
		}
	}

	SECTION("Unsorted adding")
	{
		const std::string varName = "B";
		const std::string varNameSecond = "A";
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
		const std::string varName = "Var";

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
		const std::string varName = "Var";
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

SCENARIO("Adding variables and initializing them")
{
	Calculator calculator;
	std::ostringstream output{};

	SECTION("Wrong named variables adding or adding them with wrong value")
	{
		const std::string emptyVarName = "";
		const std::string incorrectVarNameStartsWithNumber = "1";
		const std::string incorrectVarNameIncludesNotOnlyLettersAndDigits = "Aadb!@#";
		const std::string correctValueWithComma = "10,10";
		const std::string correctValueWithPoint = "10.10";
		const std::string correctVarName = "V123arName123";
		const std::string incorrectValue = "abracadabra";

		WHEN("Variables named incorrectly")
		{
			THEN("Attempt to add variable fails")
			{
				REQUIRE(!calculator.DeclareVariable(emptyVarName, correctValueWithComma));
				REQUIRE(!calculator.DeclareVariable(incorrectVarNameStartsWithNumber, correctValueWithPoint));
				REQUIRE(!calculator.DeclareVariable(incorrectVarNameIncludesNotOnlyLettersAndDigits, correctValueWithPoint));
				REQUIRE(!calculator.DeclareVariable(correctVarName, incorrectValue));
			}
		}
	}

	SECTION("Unsorted adding")
	{
		const std::string varName = "B";
		const std::string varNameSecond = "A";
		const std::string secondVarValue = "15.15";
		const std::string firstVarValue = "10,010";
		const std::ostringstream expectingResult{ "A:15.15\nB:10.01\n" };
		std::ostringstream output{};

		WHEN("Printing variables added not in lexicographic order")
		{
			calculator.DeclareVariable(varName, firstVarValue);
			calculator.DeclareVariable(varNameSecond, secondVarValue);
			calculator.PrintVariables(output);

			THEN("outputs them sorted")
			{
				REQUIRE(expectingResult.str() == output.str());
			}
		}
	}

	SECTION("Changing value already declarated variable")
	{
		const std::string varName = "Var";
		std::ostringstream output{};
		const std::ostringstream expectedOutput{ "Var:100.50\n" };
		calculator.DeclareVariable(varName);
		const std::string varValue = "100,50";

		WHEN("Variable declarated, can redeclare it with new value")
		{
			REQUIRE(calculator.DeclareVariable(varName, varValue));
			THEN("Value changed")
			{
				calculator.PrintVariable(varName, output);
				REQUIRE(expectedOutput.str() == output.str());
			}
		}
	}

}
