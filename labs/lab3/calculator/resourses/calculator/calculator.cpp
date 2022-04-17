#include "../../headers/calculator/calculator.h"
#include "../../headers/std_lib.h"

Calculator::Calculator()
{
}

bool Calculator::DeclareVariable(const std::string& varName)
{
	if (std::size(varName) == 0 || m_vars.count(varName) != 0)
	{
		return false;
	}

	m_vars.emplace(varName, std::numeric_limits<Value>::quiet_NaN());
	return true;
}

void Calculator::PrintVariables(std::ostream& output) const
{
	for (auto& [varName, value] : m_vars)
	{
		output << varName << "=" << value << std::endl;
	}
}
