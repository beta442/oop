#pragma once

#include "../std_lib.h"

#include "COperand.h"

class Variable : public Operand
{
public:
	Variable();
	Variable(const Value value);

	Value GetValue() const override;
	void SetValue(const Value value);

private:

	Value m_value;
};
