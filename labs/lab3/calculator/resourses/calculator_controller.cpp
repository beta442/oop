#include "../headers/calculator_controller.h"
#include "../headers/main_utils.h"

using namespace std::placeholders;

CalculatorController::CalculatorController(std::istream& input, std::ostream& output, Calculator& calculator)
	: m_input(input)
	, m_output(output)
	, m_calculator(calculator)
	, m_actions({ { EXIT_COMMAND, std::bind(&CalculatorController::StopWorkflow, this) },
		  { FUNCTION_COMMAND, std::bind(&CalculatorController::DeclareFunction, this, _1) },
		  { HELP_COMMAND, std::bind(&CalculatorController::Help, this) },
		  { LET_COMMAND, std::bind(&CalculatorController::InitVariable, this, _1) },
		  { PRINT_COMMAND, std::bind(&CalculatorController::PrintVariable, this, _1) },
		  { PRINT_FUNCTIONS_COMMAND, std::bind(&CalculatorController::PrintAllFunctions, this) },
		  { PRINT_VARS_COMMAND, std::bind(&CalculatorController::PrintAllVariables, this) },
		  { VAR_COMMAND, std::bind(&CalculatorController::DeclareVariable, this, _1) } })
{
	m_isWorkflowGoesOn = true;
}

bool CalculatorController::IsFinishedWork() const
{
	return m_isWorkflowGoesOn;
}

bool CalculatorController::HandleCommand() const
{
	std::string commandLine;
	std::getline(m_input, commandLine);
	std::istringstream stream(commandLine);

	std::string action;
	stream >> action;

	auto it = m_actions.find(action);
	if (it != m_actions.end())
	{
		return it->second(stream);
	}
	return false;
}

bool CalculatorController::DeclareFunction(std::istream& arguments) const
{
	return false;
}

bool CalculatorController::DeclareVariable(std::istream& arguments) const
{
	if (arguments.eof())
	{
		m_output << "Wrong arguments count. See help" << std::endl;
		return true;
	}

	std::string identifier;
	arguments >> identifier;

	if (!m_calculator.DeclareVariable(identifier))
	{
		m_output << "Variable already exists, can't redeclare" << std::endl;
	}
	return true;
}

bool CalculatorController::Help() const
{
	PrintMapCommandDescription(commandDescription, m_output);
	m_output << std::endl;
	return true;
}

bool CalculatorController::InitVariable(std::istream& arguments) const
{
	return false;
}

bool CalculatorController::PrintAllFunctions() const
{
	return false;
}

bool CalculatorController::PrintAllVariables() const
{
	m_calculator.PrintVariables(m_output);
	m_output << std::endl;
	return true;
}

bool CalculatorController::PrintVariable(std::istream& arguments) const
{
	if (arguments.eof())
	{
		m_output << "Wrong arguments count. See help" << std::endl;
		return true;
	}

	std::string identifier;
	arguments >> identifier;

	if (!m_calculator.PrintVariable(identifier, m_output))
	{
		m_output << "Variable doesn't exists, failed to print its value" << std::endl;
	}
	return true;
}

bool CalculatorController::StopWorkflow()
{
	if (m_isWorkflowGoesOn)
	{
		m_isWorkflowGoesOn = false;
		return true;
	}
	return false;
}
