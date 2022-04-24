#include "../../headers/calculator/CFunction.h"

Function::Function(const std::shared_ptr<Function> operand)
	: m_firstOperand(operand)
	, m_operation(std::nullopt)
	, m_secondOperand(std::nullopt)
	, m_cachedValue(std::nullopt)
{
}

Function::Function(const std::shared_ptr<Operand> operandFirst,
	const Operation& operation, const std::shared_ptr<Operand> operandSecond)
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
	}
	
	return m_cachedValue.value();
}
