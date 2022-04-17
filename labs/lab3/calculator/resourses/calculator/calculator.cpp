#include "../../headers/calculator/calculator.h"
#include "../../headers/std_lib.h"

Calculator::Calculator()
{
	m_identifierRegexp = std::regex("^[a-zA-Z]([\\w]|[\\d])+$");
}

bool Calculator::DeclareVariable(const std::string& varName)
{
	if (std::size(varName) == 0 ||
		m_vars.count(varName) != 0 ||
		!std::regex_match(varName, m_identifierRegexp))
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
		output << varName << DELIMETR << std::setprecision(2) << value << std::endl;
	}
}

bool Calculator::PrintVariable(const std::string varName, std::ostream& output) const
{
	if (output.fail() || m_vars.count(varName) == 0)
	{
		return false;
	}

	output << varName << DELIMETR << std::setprecision(2) << m_vars.at(varName) << std::endl;

	return true;
}
