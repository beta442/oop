#include "../../headers/calculator/variable.h"

Variable::Variable(const Value value)
{
	m_value = value;
}

Value Variable::GetValue() const
{
	return m_value;
}

Variable Variable::operator+(const Variable& v) const
{
	return Variable(m_value + v.GetValue());
}

Variable Variable::operator-(const Variable& v) const
{
	return Variable(m_value - v.GetValue());
}

Variable Variable::operator*(const Variable& v) const
{
	return Variable(m_value * v.GetValue());
}

Variable Variable::operator/(const Variable& v) const
{
	return Variable(m_value / v.GetValue());
}
