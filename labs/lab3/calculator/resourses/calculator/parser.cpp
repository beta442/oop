#include "../../headers/calculator/CParser.h"

bool Parser::IsStringValidIdentifier(const std::string& str)
{
	return std::regex_match(str, m_identifierRegExp);
}

bool Parser::IsStringValidDouble(const std::string& str)
{
	return std::regex_match(str, m_doubleValueRegExp);
}

Parser::ParsingResult Parser::ParseExpression(const std::string& str)
{
	ParsingResult result{ ResultType::Failure, {} };

	std::smatch matches;
	if (std::regex_match(str, matches, m_identifierAssignDoubleValueRegExp))
	{
		// l - 1, r - 3
		result.type = ResultType::IdentifierAssignDouble;
	}
	else if (std::regex_match(str, matches, m_identifierAssignIdentifierRegExp))
	{
		// l - 1, r - 3
		result.type = ResultType::IdentifierAssignIdentifier;
	}
	else if (std::regex_match(str, matches, m_identifierAssignExpressionRegExp))
	{
		// l - 1, rl - 3, o - 5, ll - 6
		result.type = ResultType::IdentifierAssignExpression;
	}
	else
	{
		return result;
	}

	for (auto& match : matches)
	{
		result.parsedResults.push_back(match.str());
	}

	return result;
}
