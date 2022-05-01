#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"

#include "../../../labs/lab3/calculator/headers/calculator/CVariable.h"

SCENARIO("Variable at creation state")
{
	Variable varNan{};
	const Operand::Value value = 900;
	Variable var{ value };

	WHEN("Variable created w/o value")
	{
		THEN("Variable's value is nan")
		{
			REQUIRE(std::isnan(varNan.GetValue()));
		}
	}

	WHEN("Variable created with provided value")
	{
		THEN("Variable's value is equal to provided value")
		{
			REQUIRE(var.GetValue() == value);
		}
	}
}

#include "../../../labs/lab3/calculator/headers/calculator/CResult.h"

SCENARIO("Result at creation state")
{
	WHEN("Result created w/o provided messsage")
	{
		const Result resErr{ false };
		const Result resOk{ true };

		THEN("Result hasn't any msg")
		{
			REQUIRE(!resErr.HasMessage());
			REQUIRE(!resOk.HasMessage());
			REQUIRE(std::size(resErr.Message()) == 0);
			REQUIRE(std::size(resOk.Message()) == 0);
		}
	}

	WHEN("Result created with provided message")
	{
		const std::string errMsg = "Err occured";
		const Result resErrWithMsg{ false, errMsg };
		const std::string okMsg = "Everything is ok";
		const Result resOkWitHMsg{ true, okMsg };
		THEN("Result contains message inside")
		{
			REQUIRE(resErrWithMsg.HasMessage());
			REQUIRE(resOkWitHMsg.HasMessage());
			REQUIRE(resErrWithMsg.Message() == errMsg);
			REQUIRE(resOkWitHMsg.Message() == okMsg);
		}
	}
}

#include "../../../labs/lab3/calculator/headers/calculator/CParser.h"

SCENARIO("Calculator's expressions parsing test")
{
	Parser parser;

	SECTION("Identifier parsing results")
	{
		WHEN("Identifier is valid")
		{
			const std::string validIdentifierFirst = "aA123B123Cccasd123";
			const std::string validIdentifierSecond = "A";
			const std::string validIdentifierThird = "a";
			const std::string validIdentifierFourth = "aBcaasdA";
			THEN("IsStringValidIdentifier() returns true")
			{
				REQUIRE(parser.IsStringValidIdentifier(validIdentifierFirst));
				REQUIRE(parser.IsStringValidIdentifier(validIdentifierSecond));
				REQUIRE(parser.IsStringValidIdentifier(validIdentifierThird));
				REQUIRE(parser.IsStringValidIdentifier(validIdentifierFourth));
			}
		}

		WHEN("Idenitifier is invalid")
		{
			const std::string invalidIdentifierFirst = "123";
			const std::string invalidIdentifierSecond = "1a2A3A";
			const std::string invalidIdentifierThird = "A=";
			const std::string invalidIdentifierfourth = "A123A!SC/!=";
			THEN("IsStringValidIdentifier() returns false")
			{
				REQUIRE_FALSE(parser.IsStringValidIdentifier(invalidIdentifierFirst));
				REQUIRE_FALSE(parser.IsStringValidIdentifier(invalidIdentifierSecond));
				REQUIRE_FALSE(parser.IsStringValidIdentifier(invalidIdentifierThird));
				REQUIRE_FALSE(parser.IsStringValidIdentifier(invalidIdentifierfourth));
			}
		}
	}

	SECTION("Double value parsing results")
	{
		WHEN("Double value is valid")
		{
			const std::string validDoubleFirst = "0,12399";
			const std::string validDoubleSecond = "1992.399999";
			const std::string validDoubleThird = "999129993";
			THEN("IsStringValideDouble() returns true")
			{
				REQUIRE(parser.IsStringValidDouble(validDoubleFirst));
				REQUIRE(parser.IsStringValidDouble(validDoubleSecond));
				REQUIRE(parser.IsStringValidDouble(validDoubleThird));
			}
		}

		WHEN("Double value is invalid")
		{
			const std::string invalidDoubleFirst = "1A2399,";
			const std::string invalidDoubleSecond = "1992399999.";
			const std::string invalidDoubleThird = ".,999129993";
			THEN("IsStringValideDouble() returns false")
			{
				REQUIRE_FALSE(parser.IsStringValidDouble(invalidDoubleFirst));
				REQUIRE_FALSE(parser.IsStringValidDouble(invalidDoubleSecond));
				REQUIRE_FALSE(parser.IsStringValidDouble(invalidDoubleThird));
			}
		}
	}

	SECTION("Operation string parsing result")
	{
		WHEN("Operation string is valid")
		{
			const std::string validOperationFirst = "+";
			const std::string validOperationSecond = "-";
			const std::string validOperationThird = "*";
			const std::string validOperationFourth = "/";
			THEN("IsStringValidOperation() returns true")
			{
				REQUIRE(parser.IsStringValidOperation(validOperationFirst));
				REQUIRE(parser.IsStringValidOperation(validOperationSecond));
				REQUIRE(parser.IsStringValidOperation(validOperationThird));
				REQUIRE(parser.IsStringValidOperation(validOperationFourth));
			}
		}

		WHEN("Operation string is invalid")
		{
			const std::string invalidOperationFirst = "-+++*";
			const std::string invalidOperationSecond = "++++++++";
			const std::string invalidOperationThird = "asd";
			const std::string invalidOperationFourth = "/*-+";
			THEN("IsStringValidOperation() returns false")
			{
				REQUIRE_FALSE(parser.IsStringValidOperation(invalidOperationFirst));
				REQUIRE_FALSE(parser.IsStringValidOperation(invalidOperationSecond));
				REQUIRE_FALSE(parser.IsStringValidOperation(invalidOperationThird));
				REQUIRE_FALSE(parser.IsStringValidOperation(invalidOperationFourth));
			}
		}
	}
}
