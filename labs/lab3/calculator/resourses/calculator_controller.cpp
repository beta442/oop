#include "../headers/CCalculator_controller.h"

using namespace std::placeholders;

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
	= std::string("Print variable or function, e.g. " + PRINT_COMMAND + " " + VAR_NAME_PARAMETER);
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

void PrintMapCommandDescription(const std::unordered_map<std::string, std::string> description, std::ostream& output)
{
	for (auto& [command, description] : description)
	{
		output << "--" << command << ": " << description << std::endl;
	}
}

void PrintHelloMsg(std::ostream& output)
{
	output << HELLO_MSG << std::endl;
	PrintMapCommandDescription(commandDescription, output);
	output << std::endl;
}


CalculatorController::CalculatorController(std::istream& input,
	std::ostream& output, Calculator& calculator, bool consoleMode)
	: m_input(input)
	, m_output(output)
	, m_calculator(calculator)
	, m_isWorkflowGoOn(true)
	, m_actions({ { EXIT_COMMAND, std::bind(&CalculatorController::StopWorkflow, this) },
		  { FUNCTION_COMMAND, std::bind(&CalculatorController::DeclareFunction, this, _1) },
		  { HELP_COMMAND, std::bind(&CalculatorController::Help, this) },
		  { LET_COMMAND, std::bind(&CalculatorController::InitVariable, this, _1) },
		  { PRINT_COMMAND, std::bind(&CalculatorController::PrintIdentifierAndValue, this, _1) },
		  { PRINT_FUNCTIONS_COMMAND, std::bind(&CalculatorController::PrintAllFunctions, this) },
		  { PRINT_VARS_COMMAND, std::bind(&CalculatorController::PrintAllVariables, this) },
		  { VAR_COMMAND, std::bind(&CalculatorController::DeclareVariable, this, _1) } })
{
	if (consoleMode)
	{
		PrintHelloMsg(m_output);
	}
}

void CalculatorController::StartWorkflow()
{
	while (!m_input.eof() && m_input.good() && m_output.good() && m_isWorkflowGoOn)
	{
		m_output << "> ";
		if (!HandleCommand())
		{
			std::cout << "Unknown command!" << std::endl;
		}
	}
}

bool CalculatorController::IsWorkFinished() const
{
	return m_isWorkflowGoOn;
}

bool CalculatorController::HandleCommand() const
{
	std::string commandLine;
	std::getline(m_input, commandLine);
	std::istringstream stream(commandLine);

	std::string action;
	stream >> action;

	if (auto it = m_actions.find(action); it != m_actions.end())
	{
		it->second(stream);
		return true;
	}
	return false;
}

void CalculatorController::DeclareFunction(std::istream& arguments) const
{
	std::string trimmedExpression, buffer;
	while (!arguments.eof())
	{
		arguments >> buffer;
		trimmedExpression += buffer;
	}

	if (auto result = m_calculator.DeclareFunction(trimmedExpression);
		!result.IsOk() && result.HasMessage())
	{
		m_output << result.Message() << std::endl;
	}
}

void CalculatorController::DeclareVariable(std::istream& arguments) const
{
	std::string identifier;
	arguments >> identifier;

	if (auto result = m_calculator.DeclareVariable(identifier);
		!result.IsOk() && result.HasMessage())
	{
		m_output << result.Message() << std::endl;
	}
}

void CalculatorController::Help() const
{
	PrintMapCommandDescription(commandDescription, m_output);
	m_output << std::endl;
}

void CalculatorController::InitVariable(std::istream& arguments) const
{
	std::string trimmedExpression, buffer;
	while (!arguments.eof())
	{
		arguments >> buffer;
		trimmedExpression += buffer;
	}

	if (auto result = m_calculator.InitVariable(trimmedExpression);
		!result.IsOk() && result.HasMessage())
	{
		m_output << result.Message() << std::endl;
	}
}

void CalculatorController::PrintAllFunctions() const
{
}

void CalculatorController::PrintAllVariables() const
{
	m_calculator.PrintVariables(m_output);
	m_output << std::endl;
}

void CalculatorController::PrintIdentifierAndValue(std::istream& arguments) const
{
	std::string identifier;
	arguments >> identifier;

	m_calculator.PrintIdentifierAndValue(identifier, m_output);
	m_output << std::endl;
}

void CalculatorController::StopWorkflow()
{
	if (m_isWorkflowGoOn)
	{
		m_isWorkflowGoOn = false;
	}
}
