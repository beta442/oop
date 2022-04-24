#include "../../headers/std_lib.h"

#include "../../headers/calculator/Ccalculator.h"

Calculator::Calculator()
	: m_precision(2)
	, m_delimetr(':')
{
}

Result Calculator::DeclareVariable(const std::string& identifier)
{
	if (std::size(identifier) == 0)
	{
		return { false, "Empty variable name given" };
	}
	if (IsVariableDeclarated(identifier) || IsFunctionDeclarated(identifier))
	{
		return { false, "Given variable name is already taken" };
	}
	if (!m_parser.IsStringValidIdentifier(identifier))
	{
		return { false, "Given variable name isn't valid" };
	}

	m_vars.emplace(identifier, std::make_shared<Variable>());
	return { true };
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

Result Calculator::DeclareFunction(const std::string& expression)
{
	auto [resultType, results] = m_parser.ParseExpression(expression);
	if (resultType == Parser::ResultType::Failure || std::size(results) == 0)
	{
		return { false, "Failed to parse given expression" };
	}

	auto oLeftPartOfExpression = RemoveFirst(results, m_parser.IsValidIdentifier);
	if (oLeftPartOfExpression.has_value())
	{
		std::string leftIdentifier = oLeftPartOfExpression.value();
		if (IsVariableDeclarated(leftIdentifier))
		{
			return { false, "Given function name is already taken" };
		}

		if (auto oRightPartOfExpression = RemoveFirst(results, m_parser.IsValidIdentifier);
			resultType == Parser::ResultType::IdentifierAssignIdentifier && oRightPartOfExpression.has_value())
		{
			std::string rightOperand = oRightPartOfExpression.value();
			if (IsVariableDeclarated(rightOperand))
			{
				m_funcs.emplace(leftIdentifier, std::make_shared<Function>(m_vars[rightOperand]));
			}
			else if (IsFunctionDeclarated(rightOperand))
			{
				m_funcs.emplace(leftIdentifier, m_funcs[rightOperand]);
			}
			else
			{
				return { false, "No such variable or function to assign to" };
			}
		}
		else if (auto oRightMiddlePartOfExpression = RemoveFirst(results, m_parser.IsValidOperation),
			oRightRightPartOfExpression = RemoveFirst(results, m_parser.IsValidIdentifier);
				 resultType == Parser::ResultType::IdentifierAssignExpression && oRightPartOfExpression.has_value() && oRightRightPartOfExpression.has_value())
		{
			if (!oRightMiddlePartOfExpression.has_value())
			{
				return { false, "Incorrect operation" };
			}

			std::string rightFirstOperand = oRightPartOfExpression.value();
			std::string operation = oRightMiddlePartOfExpression.value();
			std::string rightSecondOperand = oRightRightPartOfExpression.value();

			if (!(IsVariableDeclarated(rightFirstOperand) || IsFunctionDeclarated(rightFirstOperand)))
			{
				return { false, "Can't find first operand" };
			}

			if (!(IsVariableDeclarated(rightSecondOperand) || IsFunctionDeclarated(rightSecondOperand)))
			{
				return { false, "Can't find second operand" };
			}

			//m_funcs.emplace(leftIdentifier, std::make_shared<Function>({ rightFirstOperand, operation, rightSecondOperand }));
		}

		return { true };
	}

	return { false, "Failed to declare function" };
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
		if (auto oRightPartOfExpression = RemoveFirst(results, m_parser.IsValidDouble);
			resultType == Parser::ResultType::IdentifierAssignDouble && oRightPartOfExpression.has_value())
		{
			std::string value = *oRightPartOfExpression;
			std::replace(std::begin(value), std::end(value), ',', '.');
			std::stringstream ss{ value };

			double val;
			ss >> val;

			if (!IsVariableDeclarated(*oLeftPartOfExpression))
			{
				m_vars.emplace(*oLeftPartOfExpression, std::make_shared<Variable>(val));
			}
			else
			{
				m_vars[*oLeftPartOfExpression]->SetValue(val);
			}
			return { true };
		}
		if (auto oRightPartOfExpression = RemoveFirst(results, m_parser.IsValidIdentifier);
			resultType == Parser::ResultType::IdentifierAssignIdentifier && oRightPartOfExpression.has_value())
		{
			std::string value = *oRightPartOfExpression;
			if (!IsVariableDeclarated(value))
			{
				return { false, "No such variable to assign to" };
			}

			m_vars.emplace(*oLeftPartOfExpression, std::make_shared<Variable>(m_vars.at(value)->GetValue()));
			return { true };
		}
	}

	return { false, "Failed to assign value to variable" };
}

bool Calculator::IsFunctionDeclarated(const std::string& identifier) const
{
	return m_funcs.count(identifier) != 0;
}

bool Calculator::IsVariableDeclarated(const std::string& identifier) const
{
	return m_vars.count(identifier) != 0;
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
		output << varName << m_delimetr << value->GetValue() + 0 << std::endl;
	}
}

void Calculator::PrintIdentifierAndValue(const std::string& identifier, std::ostream& output) const
{
	if (!IsVariableDeclarated(identifier) && !IsFunctionDeclarated(identifier))
	{
		output << "No such variable or function" << std::endl;
		return;
	}

	PrepareStreamForPrintDoubleValues(output, m_precision);
	output << identifier << m_delimetr;
	if (IsVariableDeclarated(identifier))
	{
		output << m_vars.at(identifier)->GetValue() + 0;
	}
	else
	{
		output << m_funcs.at(identifier)->GetValue() + 0;
	}
	output << std::endl;
}

void Calculator::PrintFunctions(std::ostream& output) const
{
	if (std::size(m_funcs) == 0)
	{
		output << "No declarated functions" << std::endl;
		return;
	}
	PrepareStreamForPrintDoubleValues(output, m_precision);
	for (auto& [varName, value] : m_funcs)
	{
		output << varName << m_delimetr << value->GetValue() + 0 << std::endl;
	}
}
