#pragma once

#include "../std_lib.h"

#include "COperand.h"

class Function : public Operand
{
public:
	enum class Operation
	{
		Sum,
		Sub,
		Mul,
		Div,
	};

	Function(const std::shared_ptr<Function> operand);
	Function(const std::shared_ptr<Operand> operandFirst,
		const Operation& operation, const std::shared_ptr<Operand> operandSecond);

	Value GetValue() const override;

private:

	std::shared_ptr<Operand> m_firstOperand;
	std::optional<Operation> m_operation;
	std::optional<std::shared_ptr<Operand>> m_secondOperand;
	mutable std::optional<Value> m_cachedValue;
};
