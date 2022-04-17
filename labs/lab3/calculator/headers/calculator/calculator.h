#pragma once

#include "../std_lib.h"
#include "variable.h"

class Calculator
{
public:
	Calculator();

	bool DeclareVariable(const std::string& varName);
	bool DeclareVariable(const std::string& varName, const std::string& value);
	void PrintVariables(std::ostream& output) const;
	bool PrintVariable(const std::string& varName, std::ostream& output) const;

private:

	using Identifier = std::string;
	//todo: variable and function can't have same name
	using VariableValueMap = std::map<Identifier, Value>;

	VariableValueMap m_vars;
	std::regex m_identifierRegExp;
	std::regex m_doubleValueRegExp;
	size_t m_precision;
	char m_delimetr;
};
