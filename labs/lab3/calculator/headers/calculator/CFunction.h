#pragma once

#include "../std_lib.h"

#include "COperand.h"

class Function : public Operand, std::enable_shared_from_this<Function>
{
public:
	static std::shared_ptr<Function> Create(OperandPtr const operand)
	{
		//private_tag
		struct Wrapper : Function
		{
			Wrapper(OperandPtr const operand)
				: Function(operand)
			{
			}
		};
		auto func = std::make_shared<Wrapper>(operand);
		func->Init(operand);
		return func;
	}

	static std::shared_ptr<Function> Create(OperandPtr const operandFirst,
		const Operation& operation, OperandPtr const operandSecond)
	{
		struct Wrapper : Function
		{
			Wrapper(OperandPtr const operandFirst,
				const Operation& operation, OperandPtr const operandSecond)
				: Function(operandFirst, operation, operandSecond)
			{
			}
		};
		auto func = std::make_shared<Wrapper>(operandFirst, operation, operandSecond);
		func->Init(operandFirst, operation, operandSecond);
		return func;
	}

	Value GetValue() const override;
	void FlushCachedValue();

private:
	void Init(OperandPtr const operand);
	void Init(OperandPtr const operandFirst,
		const Operation& operation, OperandPtr const operandSecond);

	void CalculateValue() const;

	std::shared_ptr<Operand> m_firstOperand;
	std::optional<Operation> m_operation;
	std::optional<OperandPtr> m_secondOperand;
	mutable std::optional<Value> m_cachedValue;

	explicit Function(OperandPtr const operand);
	explicit Function(OperandPtr const operandFirst,
		const Operation& operation, OperandPtr const operandSecond);
};
