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

	Result DeclareVariable(const std::string& identifier);
	Result DeclareFunction(const std::string& expression);
	Result InitVariable(const std::string& expression);
	void PrintIdentifierAndValue(const std::string& identifier, std::ostream& output) const;
	void PrintVariables(std::ostream& output) const;
	void PrintFunctions(std::ostream& output) const;

private:
	using Identifier = std::string;
	using VariableValueMap = std::map<Identifier, std::shared_ptr<Variable>>;
	using FunctionValueMap = std::map<Identifier, std::shared_ptr<Function>>;

	bool IsFunctionDeclarated(const std::string& identifier) const;
	bool IsVariableDeclarated(const std::string& identifier) const;

	inline const static Parser m_parser;

	VariableValueMap m_vars;
	FunctionValueMap m_funcs;
	size_t m_precision;
	char m_delimetr;
};
