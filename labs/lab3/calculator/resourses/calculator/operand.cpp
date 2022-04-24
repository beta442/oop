#include "../../headers/calculator/COperand.h"

void Operand::AddDependentOperand(std::shared_ptr<Operand> const functPtr)
{
	m_dependentOperandsPtrs.push_back(functPtr);
}

void Operand::FlushDependentFunctions() const
{
	for (auto& ptr : m_dependentOperandsPtrs)
	{
		if (ptr != nullptr)
		{
			ptr->FlushCachedValue();
		}
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
