#include "../../headers/calculator/CFunction.h"

void Function::Init(OperandPtr const operand)
{
	m_firstOperand = operand;
	m_operation = std::nullopt;
	m_secondOperand = std::nullopt;
	m_cachedValue = std::nullopt;
	operand->AddDependentOperand(shared_from_this());
}

void Function::Init(OperandPtr const operandFirst,
	const Operation& operation, OperandPtr const operandSecond)
{
	m_firstOperand = operandFirst;
	m_operation = operation;
	m_secondOperand = operandSecond;
	m_cachedValue = std::nullopt;
	// todo:: std::enable_shared_from_this
	operandFirst->AddDependentOperand(shared_from_this());
	operandSecond->AddDependentOperand(shared_from_this());
}

Function::Value Function::GetValue() const
{
	if (!m_cachedValue.has_value())
	{
		CalculateValue();
	}

	return m_cachedValue.value();
}

void Function::CalculateValue() const
{
	Value leftOperandValue = m_firstOperand->GetValue();

	if (!m_secondOperand.has_value() || std::isnan(leftOperandValue))
	{
		m_cachedValue = leftOperandValue;
		return;
	}

	Value rightOperandValue = m_secondOperand.value()->GetValue();

	if (std::isnan(rightOperandValue) || !m_operation.has_value())
	{
		m_cachedValue = m_nanValue;
		return;
	}

	Operation op = m_operation.value();

	switch (op)
	{
	case Operation::Sum:
		m_cachedValue.emplace(leftOperandValue + rightOperandValue);
		break;
	case Operation::Sub:
		m_cachedValue.emplace(leftOperandValue - rightOperandValue);
		break;
	case Operation::Mul:
		m_cachedValue.emplace(leftOperandValue * rightOperandValue);
		break;
	case Operation::Div:
		m_cachedValue.emplace(leftOperandValue / rightOperandValue);
		break;
	default:
		m_cachedValue.emplace(m_nanValue);
		break;
	}
}

void Function::FlushCachedValue()
{
	if (m_cachedValue.has_value())
	{
		m_cachedValue.reset();
		FlushDependentFunctions();
	}
}
