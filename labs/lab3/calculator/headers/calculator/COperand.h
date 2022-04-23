#pragma once

#include "../std_lib.h"

class Operand
{
public:
	using Value = double;

	virtual Value GetValue() const = 0;
};
