#pragma once

#include "../std_lib.h"
#include "variable.h"

class Calculator
{
public:
	Calculator();

	bool DeclareVariable(const std::string& varName);
	void PrintVariables(std::ostream& output) const;
	bool PrintVariable(const std::string varName, std::ostream& output) const;

private:
	const char DELIMETR = ':';

	using Identifier = std::string;
	using VariableValueMap = std::map<Identifier, Value>;

	VariableValueMap m_vars;
};
