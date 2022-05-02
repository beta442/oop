#include "../../headers/calculator/COperand.h"

void Operand::AddDependentOperand(std::shared_ptr<Operand> functPtr)
{
	if (functPtr != nullptr)
	{
		m_dependentOperandsPtrs.emplace_back(std::move(functPtr));
	}
}

void Operand::FlushDependentFunctions() const
{
	for (auto& ptr : m_dependentOperandsPtrs)
	{
		ptr->FlushCachedValue();
	}
}

std::optional<Operand::Operation> Operand::StringToOperation(const std::string& str)
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
