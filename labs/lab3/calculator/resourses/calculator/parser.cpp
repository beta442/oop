#include "../../headers/calculator/CParser.h"

bool Parser::IsStringValidIdentifier(const std::string& str)
{
	return std::regex_match(str, m_identifierRegExp);
}

bool Parser::IsStringValidDouble(const std::string& str)
{
	return std::regex_match(str, m_doubleValueRegExp);
}

bool Parser::IsStringValidOperation(const std::string& str)
{
	return std::regex_match(str, m_operationSymbolsRegExp);
}

Parser::ParsingResult Parser::ParseExpression(const std::string& str)
{
	ParsingResult result{ ResultType::Failure, {} };

	std::smatch matches;
	if (std::regex_match(str, matches, m_identifierAssignDoubleValueRegExp))
	{
		result.type = ResultType::IdentifierAssignDouble;
	}
	else if (std::regex_match(str, matches, m_identifierAssignIdentifierRegExp))
	{
		result.type = ResultType::IdentifierAssignIdentifier;
	}
	else if (std::regex_match(str, matches, m_identifierAssignExpressionRegExp))
	{
		result.type = ResultType::IdentifierAssignExpression;
	}
	else
	{
		return result;
	}

	size_t i = 0;
	for (auto& match : matches)
	{
		if (i == 1 || i == 3 || i == 5 || i == 6)
		{
			result.parsedResults.push_back(match.str());
		}
		++i;
	}

	return result;
}
