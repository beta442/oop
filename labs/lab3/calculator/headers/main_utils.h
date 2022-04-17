#pragma once

#include "std_lib.h"

const std::string HELLO_MSG = "Calculator app";

const std::string EXIT_COMMAND = "exit";
const std::string FUNCTION_COMMAND = "fn";
const std::string HELP_COMMAND = "help";
const std::string LET_COMMAND = "let";
const std::string PRINT_COMMAND = "print";
const std::string PRINT_FUNCTIONS_COMMAND = "printfn";
const std::string PRINT_VARS_COMMAND = "printvars";
const std::string VAR_COMMAND = "var";

const std::string SUM_OPERATION = "+";
const std::string SUB_OPERATION = "-";
const std::string MULTIPLY_OPERATION = "*";
const std::string DIVISION_OPERATION = "/";

const std::string VAR_NAME_PARAMETER = "<varName>";
const std::string VAR_NAME_PARAMETER_DESCRIPTION = "Should start with letter, may be represented only by letters and digits";
const std::string VAR_VALUE_PARAMETER = "<varValue>";
const std::string VAR_VALUE_PARAMETER_DESCRIPTION = "Should be represented like that: 123.123 or 123,123 or 12345";
const std::string OPERATION_PARAMETER = "<operation>";
const std::string OPERATION_PARAMETER_DESCRIPTION = SUM_OPERATION + "|" + SUB_OPERATION + "|" + MULTIPLY_OPERATION + "|" + DIVISION_OPERATION;

const std::vector<std::string> commands{
	EXIT_COMMAND,
	FUNCTION_COMMAND,
	HELP_COMMAND,
	LET_COMMAND,
	PRINT_COMMAND,
	PRINT_FUNCTIONS_COMMAND,
	PRINT_VARS_COMMAND,
	VAR_COMMAND,
};

const std::string EXIT_COMMAND_DESCRIPTION = "Exit program";
const std::string FUNCTION_COMMAND_DESCRIPTION
	= std::string("Declare function, e.g. " + FUNCTION_COMMAND + " " + VAR_NAME_PARAMETER + "=" + VAR_NAME_PARAMETER + " | " + FUNCTION_COMMAND + " " + VAR_NAME_PARAMETER + "=" + VAR_NAME_PARAMETER + OPERATION_PARAMETER + VAR_NAME_PARAMETER);
const std::string HELP_COMMAND_DESCRIPTION = "Shows available commands";
const std::string LET_COMMAND_DESCRIPTION
	= std::string("Initialize double variable, e.g. " + LET_COMMAND + " " + VAR_NAME_PARAMETER + "=" + VAR_VALUE_PARAMETER + " | " + LET_COMMAND + " " + VAR_NAME_PARAMETER + "=" + VAR_NAME_PARAMETER);
const std::string PRINT_COMMAND_DESCRIPTION
	= std::string("Print variable, e.g. " + PRINT_COMMAND + " " + VAR_NAME_PARAMETER);
const std::string PRINT_FUNCTIONS_COMMAND_DESCRIPTION = "Prints all functions with their values";
const std::string PRINT_VARS_COMMAND_DESCRIPTION = "Prints all declarated variables";
const std::string VAR_COMMAND_DESCRIPTION
	= std::string("Declare double variable, e.g. " + VAR_COMMAND + " " + VAR_NAME_PARAMETER);

const std::unordered_map<std::string, std::string> commandDescription{
	{ FUNCTION_COMMAND, FUNCTION_COMMAND_DESCRIPTION },
	{ HELP_COMMAND, HELP_COMMAND_DESCRIPTION },
	{ LET_COMMAND, LET_COMMAND_DESCRIPTION },
	{ PRINT_COMMAND, PRINT_COMMAND_DESCRIPTION },
	{ PRINT_FUNCTIONS_COMMAND, PRINT_FUNCTIONS_COMMAND_DESCRIPTION },
	{ PRINT_VARS_COMMAND, PRINT_VARS_COMMAND_DESCRIPTION },
	{ VAR_COMMAND, VAR_COMMAND_DESCRIPTION },
	{ EXIT_COMMAND, EXIT_COMMAND_DESCRIPTION },
	{ VAR_NAME_PARAMETER, VAR_NAME_PARAMETER_DESCRIPTION },
	{ VAR_VALUE_PARAMETER, VAR_VALUE_PARAMETER_DESCRIPTION },
	{ OPERATION_PARAMETER, OPERATION_PARAMETER_DESCRIPTION },
};

void PrintHelloMsg();
void PrintMapCommandDescription(std::unordered_map<std::string, std::string> map, std::ostream& output);
