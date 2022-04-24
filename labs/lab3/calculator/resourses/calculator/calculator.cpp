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

	std::string leftIdentifier, rightOperand;
	if (auto oLeftPartOfExpression = RemoveFirst(results, m_parser.IsValidIdentifier),
		oRightPartOfExpression = RemoveFirst(results, m_parser.IsValidIdentifier);
		!oLeftPartOfExpression.has_value())
	{
		return { false, "Failed to declare function, wrong left identifier" };
	}
	else if (!oRightPartOfExpression.has_value())
	{
		return { false, "Failed to declare function, wrong right identifier" };
	}
	else
	{
		leftIdentifier = oLeftPartOfExpression.value();
		rightOperand = oRightPartOfExpression.value();
	}

	if (IsVariableDeclarated(leftIdentifier) || IsFunctionDeclarated(leftIdentifier))
	{
		return { false, "Given function name is already taken" };
	}

	if (resultType == Parser::ResultType::IdentifierAssignIdentifier)
	{
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
		return { true };
	}

	std::string operationString, rightSecondOperand;
	if (auto oRightMiddlePartOfExpression = RemoveFirst(results, m_parser.IsValidOperation),
		oRightRightPartOfExpression = RemoveFirst(results, m_parser.IsValidIdentifier);
		!oRightMiddlePartOfExpression.has_value())
	{
		return { false, "Incorrect operation" };
	}
	else if (!oRightRightPartOfExpression.has_value())
	{
		return { false, "Incorrect operand after operation" };
	}
	else
	{
		operationString = oRightMiddlePartOfExpression.value();
		rightSecondOperand = oRightRightPartOfExpression.value();
	}

	if (resultType == Parser::ResultType::IdentifierAssignExpression)
	{
		if (!(IsVariableDeclarated(rightOperand) || IsFunctionDeclarated(rightOperand)))
		{
			return { false, "Can't find first operand" };
		}

		if (!(IsVariableDeclarated(rightSecondOperand) || IsFunctionDeclarated(rightSecondOperand)))
		{
			return { false, "Can't find second operand" };
		}

		auto oOperation = Operand::StringToOperation(operationString);
		if (!oOperation.has_value())
		{
			return { false, "Not implemented operation" };
		}

		std::shared_ptr<Operand> leftAssignmentOperandPtr, rightAssignmentOperandPtr;
		const Operand::Operation operation = oOperation.value();

		if (const auto oLeftAssignmentOperand = GetOperandPtrBy(rightOperand),
			oRightAssignmentOperand = GetOperandPtrBy(rightSecondOperand);
			!oLeftAssignmentOperand.has_value() || !oRightAssignmentOperand.has_value())
		{
			return { false, "Can't find assignment operands" };
		}
		else
		{
			leftAssignmentOperandPtr = oLeftAssignmentOperand.value();
			rightAssignmentOperandPtr = oRightAssignmentOperand.value();
		}

		m_funcs.emplace(leftIdentifier,
			std::make_shared<Function>(Function{ leftAssignmentOperandPtr, operation, rightAssignmentOperandPtr }));
	}

	return { true };
}

Result Calculator::InitVariable(const std::string& expression)
{
	auto [resultType, results] = m_parser.ParseExpression(expression);
	if (resultType == Parser::ResultType::Failure || std::size(results) == 0)
	{
		return { false, "Failed to parse given expression" };
	}

	std::string leftPartOfExpression, righPartOfExpression;
	if (auto oLeftPartOfExpression = RemoveFirst(results, m_parser.IsValidIdentifier),
		oRightPartOfExpression = RemoveFirst(results, m_parser.IsValidDouble);
		!oLeftPartOfExpression.has_value())
	{
		return { false, "Incorrectly typed left identifier" };
	}
	else if (!oRightPartOfExpression.has_value() && resultType == Parser::ResultType::IdentifierAssignDouble)
	{
		return { false, "Incorrectly typed right double value" };
	}
	else
	{
		leftPartOfExpression = *oLeftPartOfExpression;
		righPartOfExpression = *oRightPartOfExpression;
	}

	if (IsFunctionDeclarated(leftPartOfExpression))
	{
		return { false, "Can't declare variable, given name is already taken" };
	}

	if (resultType == Parser::ResultType::IdentifierAssignDouble)
	{
		std::replace(std::begin(righPartOfExpression), std::end(righPartOfExpression), ',', '.');
		std::stringstream ss{ righPartOfExpression };

		Operand::Value val;
		ss >> val;

		if (IsVariableDeclarated(leftPartOfExpression))
		{
			m_vars[leftPartOfExpression]->SetValue(val);
		}
		else
		{
			m_vars.emplace(leftPartOfExpression, std::make_shared<Variable>(val));
		}
	}
	else if (resultType == Parser::ResultType::IdentifierAssignIdentifier)
	{
		if (auto oLeftPartOfExpression = RemoveFirst(results, m_parser.IsValidIdentifier);
			!oLeftPartOfExpression.has_value())
		{
			return { false, "Incorrectly typed right identifier" };
		}
		else
		{
			righPartOfExpression = oLeftPartOfExpression.value();
		}

		if (!IsVariableDeclarated(righPartOfExpression))
		{
			return { false, "No such variable to assign to" };
		}

		m_vars.emplace(leftPartOfExpression, std::make_shared<Variable>(m_vars.at(righPartOfExpression)->GetValue()));
	}

	return { true };
}

bool Calculator::IsFunctionDeclarated(const std::string& identifier) const
{
	return m_funcs.count(identifier) != 0;
}

bool Calculator::IsVariableDeclarated(const std::string& identifier) const
{
	return m_vars.count(identifier) != 0;
}

std::optional<Calculator::OperandPtr> Calculator::GetOperandPtrBy(const std::string identifier) const
{
	if (IsVariableDeclarated(identifier))
	{
		return m_vars.at(identifier);
	}
	else if (IsFunctionDeclarated(identifier))
	{
		return m_funcs.at(identifier);
	}
	return std::nullopt;
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
