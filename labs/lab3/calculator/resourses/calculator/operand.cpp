#include "../../headers/calculator/COperand.h"

void Operand::AddDependentOperand(std::shared_ptr<Operand> const functPtr)
{
	if (functPtr != nullptr)
	{
		m_dependentOperandsPtrs.push_back(functPtr);
	}
}

void Operand::FlushDependentFunctions() const
{
	for (auto& ptr : m_dependentOperandsPtrs)
	{
		ptr->FlushCachedValue();
	}
}

std::optional<Operand::Operation> Operand::StringToOperation(const std::string str)
{
	if (str == "+")
	{
		return Operand::Operation::Sum;
	}
	else if (str == "-")
	{
		return Operand::Operation::Sub;
	}
	else if (str == "*")
	{
		return Operand::Operation::Mul;
	}
	else if (str == "/")
	{
		return Operand::Operation::Div;
	}
	return std::nullopt;
}
