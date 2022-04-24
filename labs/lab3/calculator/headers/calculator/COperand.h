#pragma once

#include "../std_lib.h"

class Operand
{
public:
	using Value = double;

	virtual Value GetValue() const = 0;

protected:
	//virtual void AddDependentOperand(std::shared_ptr<Operand> functPtr) = 0;
	//virtual void FlushDependentFunctions() = 0;

	std::vector<std::shared_ptr<Operand>> m_dependentOperandsPtrs;
	inline const static Value m_nanValue = std::numeric_limits<Value>::quiet_NaN();
};
