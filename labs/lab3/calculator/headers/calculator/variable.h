#pragma once

using Value = double;

class Variable
{
public:
	Variable(const Value value);

	Value GetValue() const;

	Variable operator+(const Variable& v) const;
	Variable operator-(const Variable& v) const;
	Variable operator*(const Variable& v) const;
	Variable operator/(const Variable& v) const;

private:
	Value m_value;
};
