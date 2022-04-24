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

	Function(std::shared_ptr<Operand> const operand);
	Function(std::shared_ptr<Operand> const operandFirst,
		const Operation& operation, std::shared_ptr<Operand> const operandSecond);

	Value GetValue() const override;

	//void AddDependentOperand(std::shared_ptr<Operand> funcPtr) override;
	//void FlushDependentFunctions() override;

private:
	void CalculateValue() const;
	void FlushCachedValue();

	std::shared_ptr<Operand> m_firstOperand;
	std::optional<Operation> m_operation;
	std::optional<std::shared_ptr<Operand>> m_secondOperand;
	mutable std::optional<Value> m_cachedValue;
};
