#include "../../headers/calculator/calculator.h"
#include "../../headers/std_lib.h"

Calculator::Calculator()
{
	m_identifierRegExp = std::regex("^([a-zA-Z]([\\w]|[\\d])+|[a-zA-Z])$");
	m_doubleValueRegExp = std::regex("([\\d]+(\\.|,)[\\d]+)|([\\d]+)");
	m_precision = 2;
	m_delimetr = ':';
}

bool Calculator::DeclareVariable(const std::string& varName)
{
	if (std::size(varName) == 0 || m_vars.count(varName) != 0 || !std::regex_match(varName, m_identifierRegExp))
	{
		return false;
	}

	m_vars.emplace(varName, std::numeric_limits<Value>::quiet_NaN());
	return true;
}

bool Calculator::DeclareVariable(const std::string& varName, const std::string& value)
{
	bool isValueContainRValue = std::regex_match(value, m_doubleValueRegExp);
	bool isValueContainLValue = std::regex_match(value, m_identifierRegExp);

	if (std::size(varName) == 0 ||
		std::size(value) == 0 ||
		!std::regex_match(varName, m_identifierRegExp) ||
		!(isValueContainLValue || isValueContainRValue))
	{
		return false;
	}

	if (isValueContainRValue)
	{
		std::string correctValue = value;
		std::replace(std::begin(correctValue), std::end(correctValue), ',', '.');
		std::stringstream ss{ correctValue };
		double val;
		ss >> val;

		m_vars[varName] = val;
	}
	else
	{
		if (m_vars.count(value) == 0)
		{
			return false;
		}

		m_vars.emplace(varName, m_vars.at(value));
	}

	return true;
}

void Calculator::PrintVariables(std::ostream& output) const
{
	output << std::setprecision(m_precision);
	output << std::fixed;
	for (auto& [varName, value] : m_vars)
	{
		output << varName << m_delimetr << value << std::endl;
	}
}

bool Calculator::PrintVariable(const std::string& varName, std::ostream& output) const
{
	if (output.fail() || m_vars.count(varName) == 0)
	{
		return false;
	}

	output << std::setprecision(m_precision);
	output << std::fixed;
	output << varName << m_delimetr << m_vars.at(varName) << std::endl;

	return true;
}
