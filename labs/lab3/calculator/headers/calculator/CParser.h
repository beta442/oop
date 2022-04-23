#pragma once

#include "../std_lib.h"

#include "CResult.h"

class Parser
{
public:
	enum class ResultType
	{
		Failure = 0,
		IdentifierAssignDouble,
		IdentifierAssignIdentifier,
		IdentifierAssignExpression,
	};

	struct ParsingResult
	{
		ResultType type;
		std::vector<std::string> parsedResults;
	};

	static bool IsStringValidIdentifier(const std::string& str);
	static bool IsStringValidDouble(const std::string& str);
	static ParsingResult ParseExpression(const std::string& str);

	inline static const auto IsValidIdentifier = [](const std::string& str) {
		return IsStringValidIdentifier(str);
	};
	inline static const auto IsValidDouble = [](const std::string& str) {
		return IsStringValidDouble(str);
	};

private:
	inline static const std::string m_identifierRegExpString = "([a-zA-Z]([\\w]|[\\d])*)";
	inline static const std::string m_doubleValueRegExpString = "([+-]?((\\d+)|(\\d+[\\.,]?\\d+)))";

	inline static const std::string m_equalSymbol = "=";
	inline static const std::string m_operationSymbolsRegExpString = "([+\\-*\\/])";

	inline static const std::regex m_identifierRegExp = std::regex("^" + m_identifierRegExpString + "$");
	inline static const std::regex m_doubleValueRegExp = std::regex("^" + m_doubleValueRegExpString + "$");
	inline static const std::regex m_identifierAssignDoubleValueRegExp = std::regex("^" + m_identifierRegExpString + m_equalSymbol + m_doubleValueRegExpString + "$");
	inline static const std::regex m_identifierAssignIdentifierRegExp = std::regex("^" + m_identifierRegExpString + m_equalSymbol + m_identifierRegExpString + "$");
	inline static const std::regex m_identifierAssignExpressionRegExp = std::regex("^" + m_identifierRegExpString + m_equalSymbol + m_identifierRegExpString + m_operationSymbolsRegExpString + m_identifierRegExpString + "$");
};
