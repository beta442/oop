#pragma once

#include "std_lib.h"

#include "calculator/CCalculator.h"

class CalculatorController
{
public:
	CalculatorController(std::istream& input,
		std::ostream& output, Calculator& calculator, bool consoleMode);

	void StartWorkflow();

private:
	using CommandsDescription = std::unordered_map<std::string, std::string>;
	using ActionsMap = std::map<std::string, std::function<void(std::istream& arguments)>>;

	void DeclareFunction(std::istream& arguments) const;
	void DeclareVariable(std::istream& arguments) const;
	bool HandleCommand() const;
	void Help() const;
	void InitVariable(std::istream& arguments) const;
	bool IsWorkFinished() const;
	void PrintAllFunctions() const;
	void PrintAllVariables() const;
	void PrintIdentifierAndValue(std::istream& arguments) const;
	void StopWorkflow();

	Calculator& m_calculator;
	bool m_isWorkflowGoOn;
	const ActionsMap m_actions;
	std::istream& m_input;
	std::ostream& m_output;
};
