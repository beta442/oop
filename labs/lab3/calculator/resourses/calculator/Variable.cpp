#include "../../headers/calculator/CVariable.h"

Variable::Variable(const Value value)
	: m_value(value)
{
}

Variable::Variable()
	: m_value(m_nanValue)
{
}

Variable::Value Variable::GetValue() const
{
	return m_value;
}

void Variable::SetValue(const Variable::Value value)
{
	m_value = value;
}
