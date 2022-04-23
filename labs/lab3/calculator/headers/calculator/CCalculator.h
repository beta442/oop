#pragma once

#include "../std_lib.h"

#include "CFunction.h"
#include "CParser.h"
#include "CResult.h"
#include "CVariable.h"

class Calculator
{
public:
	Calculator();

	Result DeclareVariable(const std::string& varName);
	Result InitVariable(const std::string& expression);
	void PrintVariables(std::ostream& output) const;
	void PrintVariable(const std::string& varName, std::ostream& output) const;

private:

	using Identifier = std::string;
	//todo: variable and function can't have same name
	using VariableValueMap = std::map<Identifier, Variable>;
	using FunctionValueMap = std::map<Identifier, Function>;

	inline const static Parser m_parser;

	VariableValueMap m_vars;
	FunctionValueMap m_funcs;
	size_t m_precision;
	char m_delimetr;
};
