#pragma once

#include "../std_lib.h"

class Function;

class Operand
{
public:
	using Value = double;

	virtual Value GetValue() const = 0;

	void AddDependentOperand(std::shared_ptr<Function> functPtr);
protected:

	void FlushDependentFunctions() const;

	std::vector<std::shared_ptr<Function>> m_dependentOperandsPtrs;
	inline const static Value m_nanValue = std::numeric_limits<Value>::quiet_NaN();
};

#include "CFunction.h"
