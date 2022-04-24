#include "../../headers/calculator/COperand.h"

void Operand::AddDependentOperand(std::shared_ptr<Function> const functPtr)
{
	m_dependentOperandsPtrs.push_back(functPtr);
}

void Operand::FlushDependentFunctions() const
{
	for (auto& ptr : m_dependentOperandsPtrs)
	{
		ptr->FlushCachedValue();
	}
}
