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
}

bool CalculatorController::IsFinishedWork() const
{
}

bool CalculatorController::HandleCommand() const
{
}

bool CalculatorController::DeclareFunction(std::istream& arguments) const
{
}

bool CalculatorController::DeclareVariable(std::istream& arguments) const
{
}

bool CalculatorController::Help() const
{
}

bool CalculatorController::InitVariable(std::istream& arguments) const
{
}

bool CalculatorController::PrintAllFunctions() const
{
}

bool CalculatorController::PrintAllVariables() const
{
}

bool CalculatorController::PrintVariable(std::istream& arguments) const
{
}

bool CalculatorController::StopWorkflow() const
{
}
