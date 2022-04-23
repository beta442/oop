#include "../../headers/std_lib.h"

#include "../../headers/calculator/Ccalculator.h"

Calculator::Calculator()
	: m_precision(2)
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
	if (!m_parser.IsStringValidIdentifier(varName))
	{
		return { false, "Given variable name isn't valid" };
	}

	m_vars.emplace(varName, Variable{});
	return { true, "" };
}

std::optional<std::string> RemoveFirst(std::vector<std::string>& sequence,
	const std::function<bool(const std::string& str)>& pred)
{
	const auto sequenceIt = std::begin(sequence), sequenceEnd = std::end(sequence);
	if (const auto it = std::find_if(sequenceIt, sequenceEnd, pred);
		std::find_if(sequenceIt, sequenceEnd, pred) != sequenceEnd)
	{
		std::string result = *it;
		sequence.erase(it);
		return result;
	}
	return std::nullopt;
}

Result Calculator::InitVariable(const std::string& expression)
{
	auto [resultType, results] = m_parser.ParseExpression(expression);

	if (resultType == Parser::ResultType::Failure || std::size(results) == 0)
	{
		return { false, "Failed to parse given expression" };
	}

	auto oLeftPartOfExpression = RemoveFirst(results, m_parser.IsValidIdentifier);

	if (oLeftPartOfExpression.has_value())
	{
		std::cout << "Left" << *oLeftPartOfExpression << std::endl;
		if (auto oRightPartOfExpression = RemoveFirst(results, m_parser.IsValidDouble);
			resultType == Parser::ResultType::IdentifierAssignDouble && oRightPartOfExpression.has_value())
		{
			std::string value = *oRightPartOfExpression;
			std::cout << "Right" << *oRightPartOfExpression << std::endl;
			std::replace(std::begin(value), std::end(value), ',', '.');
			std::stringstream ss{ value };

			double val;
			ss >> val;

			Variable var{ val };
			m_vars[*oLeftPartOfExpression] = var;
			return true;
		}
		if (auto oRightPartOfExpression = RemoveFirst(results, m_parser.IsValidIdentifier);
			resultType == Parser::ResultType::IdentifierAssignIdentifier && oRightPartOfExpression.has_value())
		{
			std::cout << "Right" << *oRightPartOfExpression << std::endl;
			std::string value = *oRightPartOfExpression;
			if (m_vars.count(value) == 0)
			{
				return { false, "No such variable to assign to" };
			}

			Variable newVar{ m_vars.at(value) };
			m_vars.emplace(*oLeftPartOfExpression, newVar);
			return true;
		}
	}

	return { false, "Failed to assign value to variable" };
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
		output << varName << m_delimetr << value.GetValue() + 0 << std::endl;
	}
}

void Calculator::PrintVariable(const std::string& varName, std::ostream& output) const
{
	if (output.fail())
	{
		output << "Failed to output variable" << std::endl;
		return;
	}

	if (std::size(m_vars) == 0 || m_vars.count(varName) == 0)
	{
		output << "No such variable" << std::endl;
		return;
	}

	PrepareStreamForPrintDoubleValues(output, m_precision);
	output << varName << m_delimetr << m_vars.at(varName).GetValue() + 0 << std::endl;
}
