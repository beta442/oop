#include "../../headers/std_lib.h"

#include "../../headers/calculator/Ccalculator.h"

Calculator::Calculator()
	: m_precision(2)
	, m_delimetr(':')
{
}

const std::string VARIABLE_NAME_TAKEN_MSG = "Given variable name is already taken";
const std::string EMPTY_VARIABLE_NAME_MSG = "Empty variable name given";
const std::string INVALID_VARIABLE_NAME_MSG = "Given variable name isn't valid";

Result Calculator::DeclareVariable(const std::string& identifier)
{
	if (std::size(identifier) == 0)
	{
		return { false, EMPTY_VARIABLE_NAME_MSG };
	}
	if (IsVariableDeclarated(identifier) || IsFunctionDeclarated(identifier))
	{
		return { false, VARIABLE_NAME_TAKEN_MSG };
	}
	if (!Parser::IsStringValidIdentifier(identifier))
	{
		return { false, INVALID_VARIABLE_NAME_MSG };
	}

	m_vars.emplace(identifier, std::shared_ptr<Variable>(new Variable{}));
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

const std::string EXPRESSION_PARSE_FAIL_MSG = "Failed to parse given expression";
const std::string FUNCTION_NAME_TAKEN_MSG = "Failed to declare function: given function name is already taken";
const std::string NOT_IMPLEMENTED_OPERATION_MSG = "Failed to declare function: not implemented operation";
const std::string FUNCTION_WASNT_CREATED_MSG = "Function wasn't created";

Result Calculator::DeclareFunction(const std::string& expression)
{
	auto [resultType, results] = Parser::ParseExpression(expression);
	if ((resultType != Parser::ResultType::IdentifierAssignIdentifier &&
		resultType != Parser::ResultType::IdentifierAssignExpression) ||
		std::size(results) == 0)
	{
		return { false, EXPRESSION_PARSE_FAIL_MSG };
	}

	std::string leftIdentifier = RemoveFirst(results, Parser::IsValidIdentifier).value(),
				rightOperand = RemoveFirst(results, Parser::IsValidIdentifier).value();

	if (IsVariableDeclarated(leftIdentifier) || IsFunctionDeclarated(leftIdentifier))
	{
		return { false, FUNCTION_NAME_TAKEN_MSG };
	}

	if (resultType == Parser::ResultType::IdentifierAssignIdentifier)
	{
		return DeclareFunction(leftIdentifier, rightOperand);
	}

	std::string operationString = RemoveFirst(results, Parser::IsValidOperation).value(),
				rightSecondOperand = RemoveFirst(results, Parser::IsValidIdentifier).value();

	auto oOperation = Operand::StringToOperation(operationString);
	if (!oOperation.has_value())
	{
		return { false, NOT_IMPLEMENTED_OPERATION_MSG };
	}
	
	if (resultType == Parser::ResultType::IdentifierAssignExpression)
	{
		return DeclareFunction(leftIdentifier, rightOperand, oOperation.value(), rightSecondOperand);
	}

	return { false, FUNCTION_WASNT_CREATED_MSG };
}

const std::string NO_SUCH_FUNCTION_OR_VARIABLE_TO_ASSIGN_MSG = "No such variable or function to assign to";

Result Calculator::DeclareFunction(const std::string& firstIdentifier, const std::string& secondIdentifier)
{
	if (IsVariableDeclarated(secondIdentifier))
	{
		m_funcs.emplace(firstIdentifier, GetOperandPtrBy(secondIdentifier));
	}
	else if (IsFunctionDeclarated(secondIdentifier))
	{
		m_funcs.emplace(firstIdentifier, m_funcs[secondIdentifier]);
	}
	else
	{
		return { false, NO_SUCH_FUNCTION_OR_VARIABLE_TO_ASSIGN_MSG };
	}
	return { true };
}

const std::string CANT_FIND_FIRST_ASSIGNMENT_OPERAND_MSG = "Can't find first assignment operand";
const std::string CANT_FIND_SECOND_ASSIGNMENT_OPERAND_MSG = "Can't find second assignment operand";
const std::string NO_SUCH_DECLARATED_OPERANDS_MSG = "Can't find assignment operands";

Result Calculator::DeclareFunction(const std::string& identifier,
	const std::string& leftOperand, Operand::Operation operation, const std::string& rightOperand)
{
	std::shared_ptr<Operand> leftAssignmentOperandPtr = GetOperandPtrBy(leftOperand),
							 rightAssignmentOperandPtr = GetOperandPtrBy(rightOperand);
	if (leftAssignmentOperandPtr == nullptr)
	{
		return { false, CANT_FIND_FIRST_ASSIGNMENT_OPERAND_MSG };
	}
	else if (rightAssignmentOperandPtr == nullptr)
	{
		return { false, CANT_FIND_SECOND_ASSIGNMENT_OPERAND_MSG };
	}

	m_funcs.emplace(identifier,
		std::shared_ptr<Function>(Function::Create( leftAssignmentOperandPtr, operation, rightAssignmentOperandPtr )));

	return { true };
}

const std::string FAILED_TO_READ_DOUBLE_VALUE_MSG = "Can't declare variable: failed to read double value";
const std::string FAILED_VARIABLE_INIT_MSG = "Failed to init variable";
const std::string NO_SUCH_VARIABLE_MSG = "Can't declare variable: no such variable to assign to";

Result Calculator::InitVariable(const std::string& expression)
{
	auto [resultType, results] = Parser::ParseExpression(expression);
	if (resultType == Parser::ResultType::Failure || std::size(results) == 0)
	{
		return { false, EXPRESSION_PARSE_FAIL_MSG };
	}

	std::string leftPartOfExpression = RemoveFirst(results, Parser::IsValidIdentifier).value();

	if (IsFunctionDeclarated(leftPartOfExpression))
	{
		return { false, VARIABLE_NAME_TAKEN_MSG };
	}

	std::string righPartOfExpression;
	if (resultType == Parser::ResultType::IdentifierAssignDouble)
	{
		righPartOfExpression = RemoveFirst(results, Parser::IsValidDouble).value();
		std::replace(std::begin(righPartOfExpression), std::end(righPartOfExpression), ',', '.');
		std::stringstream ss{ righPartOfExpression };
		Operand::Value val;
		ss >> val;

		if (ss.fail())
		{
			return { false, FAILED_TO_READ_DOUBLE_VALUE_MSG };
		}

		if (IsVariableDeclarated(leftPartOfExpression))
		{
			m_vars[leftPartOfExpression]->SetValue(val);
		}
		else
		{
			m_vars.emplace(leftPartOfExpression, std::shared_ptr<Variable>(new Variable{ val }));
		}
		return { true };
	}
	if (resultType == Parser::ResultType::IdentifierAssignIdentifier)
	{
		righPartOfExpression = RemoveFirst(results, Parser::IsValidIdentifier).value();

		if (!IsVariableDeclarated(righPartOfExpression))
		{
			return { false, NO_SUCH_VARIABLE_MSG };
		}

		m_vars.emplace(leftPartOfExpression,
			std::shared_ptr<Variable>(new Variable{ m_vars.at(righPartOfExpression)->GetValue() }));
		return { true };
	}

	return { false, FAILED_VARIABLE_INIT_MSG };
}

bool Calculator::IsFunctionDeclarated(const std::string& identifier) const
{
	return m_funcs.count(identifier) != 0;
}

bool Calculator::IsVariableDeclarated(const std::string& identifier) const
{
	return m_vars.count(identifier) != 0;
}

Calculator::OperandPtr Calculator::GetOperandPtrBy(const std::string& identifier) const
{
	if (IsVariableDeclarated(identifier))
	{
		return m_vars.at(identifier);
	}
	else if (IsFunctionDeclarated(identifier))
	{
		return m_funcs.at(identifier);
	}
	return nullptr;
}

void PrepareStreamForPrintDoubleValues(std::ostream& output, size_t precision)
{
	output << std::setprecision(precision);
	output << std::fixed;
}

const std::string NO_DECLARATED_VARIABLES = "No declarated variables";

void Calculator::PrintVariables(std::ostream& output) const
{
	if (std::size(m_vars) == 0)
	{
		output << NO_DECLARATED_VARIABLES << std::endl;
		return;
	}
	PrepareStreamForPrintDoubleValues(output, m_precision);
	for (auto& [varName, value] : m_vars)
	{
		output << varName << m_delimetr << value->GetValue() + 0 << std::endl;
	}
}

const std::string NO_SUCH_DECLARATED_FUNCTION_OR_VARIABLE = "No such declarated variable or function";

void Calculator::PrintIdentifierAndValue(const std::string& identifier, std::ostream& output) const
{
	if (!IsVariableDeclarated(identifier) && !IsFunctionDeclarated(identifier))
	{
		output << NO_SUCH_DECLARATED_FUNCTION_OR_VARIABLE << std::endl;
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

const std::string NO_DECLARATED_FUNCTIONS = "No declarated functions";

void Calculator::PrintFunctions(std::ostream& output) const
{
	if (std::size(m_funcs) == 0)
	{
		output << NO_DECLARATED_FUNCTIONS << std::endl;
		return;
	}
	PrepareStreamForPrintDoubleValues(output, m_precision);
	for (auto& [varName, value] : m_funcs)
	{
		output << varName << m_delimetr << value->GetValue() + 0 << std::endl;
	}
}
