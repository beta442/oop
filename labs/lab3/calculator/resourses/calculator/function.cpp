#include "../../headers/calculator/CFunction.h"

Function::Function(std::shared_ptr<Operand> const operand)
	: m_firstOperand(operand)
	, m_operation(std::nullopt)
	, m_secondOperand(std::nullopt)
	, m_cachedValue(std::nullopt)
{
}

Function::Function(std::shared_ptr<Operand> const operandFirst,
	const Operation& operation, std::shared_ptr<Operand> const operandSecond)
	: m_firstOperand(operandFirst)
	, m_operation(operation)
	, m_secondOperand(operandSecond)
	, m_cachedValue(std::nullopt)
{
}

Function::Value Function::GetValue() const
{
	if (!m_cachedValue.has_value())
	{
		CalculateValue();
	}
	
	return m_cachedValue.value();
}

//void Function::AddDependentOperand(std::shared_ptr<Operand> funcPtr)
//{
//	m_dependentOperandsPtrs.push_back(funcPtr);
//}
//
//void Function::FlushDependentFunctions()
//{
//	for (auto& ptr : m_dependentOperandsPtrs)
//	{
//		Function = Function{ *ptr };
//		ptr->FlushDependentFunctions();
//	}
//}
//
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
	case Function::Operation::Sum:
		m_cachedValue = leftOperandValue + rightOperandValue;
		break;
	case Function::Operation::Sub:
		m_cachedValue = leftOperandValue - rightOperandValue;
		break;
	case Function::Operation::Mul:
		m_cachedValue = leftOperandValue * rightOperandValue;
		break;
	case Function::Operation::Div:
		m_cachedValue = leftOperandValue / rightOperandValue;
		break;
	default:
		m_cachedValue = m_nanValue;
		break;
	}
}

void Function::FlushCachedValue()
{
	if (m_cachedValue.has_value())
	{
		m_cachedValue.reset();
	}
}
