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
