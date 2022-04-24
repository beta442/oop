#pragma once

#include "../std_lib.h"

class Operand
{
public:
	using Value = double;
	using OperandPtr = std::shared_ptr<Operand>;

	enum class Operation
	{
		Sum,
		Sub,
		Mul,
		Div,
	};

	virtual Value GetValue() const = 0;

	static std::optional<Operation> StringToOperation(const std::string str);

	void AddDependentOperand(OperandPtr const functPtr);

protected:
	void FlushDependentFunctions() const;

	virtual void FlushCachedValue() = 0;

	std::vector<OperandPtr> m_dependentOperandsPtrs;
	inline const static Value m_nanValue = std::numeric_limits<Value>::quiet_NaN();
};
