#pragma once

#include "../std_lib.h"

#include "COperand.h"

class Function : public Operand
{
public:

	Function(OperandPtr const operand);
	Function(OperandPtr const operandFirst,
		const Operation& operation, std::shared_ptr<Operand> const operandSecond);

	Value GetValue() const override;
	void FlushCachedValue();

private:
	void CalculateValue() const;

	std::shared_ptr<Operand> m_firstOperand;
	std::optional<Operation> m_operation;
	std::optional<std::shared_ptr<Operand>> m_secondOperand;
	mutable std::optional<Value> m_cachedValue;
};
