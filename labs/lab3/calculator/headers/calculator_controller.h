#pragma once

#include "std_lib.h"

#include "calculator.h"

class CalculatorController
{
public:
	CalculatorController(std::istream& input, std::ostream& output, Calculator& calculator);

	bool IsFinishedWork() const;
	bool HandleCommand() const;

private:
	bool DeclareFunction(std::istream& arguments) const;
	bool DeclareVariable(std::istream& arguments) const;
	bool Help() const;
	bool InitVariable(std::istream& arguments) const;
	bool PrintAllFunctions() const;
	bool PrintAllVariables() const;
	bool PrintVariable(std::istream& arguments) const;
	bool StopWorkflow();

	using ActionsMap = std::map<std::string, std::function<bool(std::istream& arguments)>>;

	bool m_isWorkflowGoesOn;
	Calculator& m_calculator;
	const ActionsMap m_actions;
	std::istream& m_input;
	std::ostream& m_output;
	std::string m_commandLine;
};
