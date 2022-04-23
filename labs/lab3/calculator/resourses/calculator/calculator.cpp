#include "../../headers/std_lib.h"

#include "../../headers/calculator/Ccalculator.h"

Calculator::Calculator()
	: m_identifierRegExp(std::regex("^([a-zA-Z]([\\w]|[\\d])+|[a-zA-Z])$"))
	, m_doubleValueRegExp(std::regex("([\\d]+(\\.|,)[\\d]+)|([\\d]+)"))
	, m_precision(2)
	, m_delimetr(':')
{
}

Result Calculator::DeclareVariable(const std::string& varName)
{
	if (std::size(varName) == 0)
	{
		return { false, "Empty variable name given" };
	}
	if (m_vars.count(varName) != 0)
	{
		return { false, "Given variable name is already taken" };
	}
	if (!std::regex_match(varName, m_identifierRegExp))
	{
		return { false, "Given variable name isn't valid" };
	}

	m_vars.emplace(varName, Variable{});
	return { true, "" };
}

bool Calculator::DeclareVariable(const std::string& varName, const std::string& value)
{
	bool isValueContainRValue = std::regex_match(value, m_doubleValueRegExp);
	bool isValueContainLValue = std::regex_match(value, m_identifierRegExp);

	if (std::size(varName) == 0 || std::size(value) == 0 || !std::regex_match(varName, m_identifierRegExp) || !(isValueContainLValue || isValueContainRValue))
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

		// m_vars[varName] = val;
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

void PrepareStreamForPrintDoubleValues(std::ostream& output, size_t precision)
{
	output << std::setprecision(precision);
	output << std::fixed;
}

void Calculator::PrintVariables(std::ostream& output) const
{
	if (std::size(m_vars) == 0)
	{
		output << "No declarated variables" << std::endl;
		return;
	}
	PrepareStreamForPrintDoubleValues(output, m_precision);
	for (auto& [varName, value] : m_vars)
	{
		output << varName << m_delimetr << value.GetValue() << std::endl;
	}
}

void Calculator::PrintVariable(const std::string& varName, std::ostream& output) const
{
	if (output.fail())
	{
		output << "Failed to output variable" << std::endl;
	}

	if (std::size(m_vars) == 0 || m_vars.count(varName) == 0)
	{
		output << "No such variable" << std::endl;
	}

	PrepareStreamForPrintDoubleValues(output, m_precision);
	output << varName << m_delimetr << m_vars.at(varName).GetValue() << std::endl;
}
