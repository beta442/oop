#pragma once

#include "../std_lib.h"

#include "CFunction.h"
#include "CResult.h"
#include "CVariable.h"

class Calculator
{
public:
	Calculator();

	Result DeclareVariable(const std::string& varName);
	bool DeclareVariable(const std::string& varName, const std::string& value);
	void PrintVariables(std::ostream& output) const;
	void PrintVariable(const std::string& varName, std::ostream& output) const;

private:

	using Identifier = std::string;
	//todo: variable and function can't have same name
	using VariableValueMap = std::map<Identifier, Variable>;
	using FunctionValueMap = std::map<Identifier, Function>;

	VariableValueMap m_vars;
	FunctionValueMap m_funcs;
	std::regex m_identifierRegExp;
	std::regex m_doubleValueRegExp;
	size_t m_precision;
	char m_delimetr;
};
