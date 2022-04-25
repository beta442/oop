#pragma once

#include "../std_lib.h"

#include "CFunction.h"
#include "COperand.h"
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
	using OperandPtr = Operand::OperandPtr;
	using VariableValueMap = std::map<Identifier, std::shared_ptr<Variable> const>;
	using FunctionValueMap = std::map<Identifier, OperandPtr const>;

	bool IsFunctionDeclarated(const std::string& identifier) const;
	bool IsVariableDeclarated(const std::string& identifier) const;
	OperandPtr GetOperandPtrBy(const std::string& identifier) const;
	Result DeclareFunction(const std::string& firstIdentifier, const std::string& secondIdentifier);
	Result DeclareFunction(const std::string& identifier,
		const std::string& leftOperand, Operand::Operation operation, const std::string& rightOperand);

	VariableValueMap m_vars;
	FunctionValueMap m_funcs;
	size_t m_precision;
	char m_delimetr;
};
