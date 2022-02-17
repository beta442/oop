#include <iostream>
#include <map>
#include <numeric>
#include <string>

#include "..\..\..\headers\CustomMath.h"

constexpr auto BASE_PARAM_DESCR = "source notation";
constexpr auto NEED_BASE_PARAM_DESCR = "destination notation";
constexpr auto VALUE_PARAM_DESCR = "value";

constexpr auto ALPHABET_SIZE = 26;
constexpr auto ALPHA = 'A';
constexpr auto MIN_BASE_ALPHA_VALUE = 48;
constexpr auto MIN_BASE = 2;
constexpr auto DECIMAL_BASE = 10;
constexpr auto MAX_BASE = DECIMAL_BASE + ALPHABET_SIZE;

int StringToInt(const std::string& str, int radix, bool& wasError);
std::string IntToString(int n, int radix, bool& wasError);

int main(int argc, char* argv[])
{
	if (argc != 4 || std::strlen(argv[1]) == 0 || std::strlen(argv[2]) == 0 || std::strlen(argv[3]) == 0)
	{
		printf("Invalid argument count\n");
		printf("Usage: radix.exe <%s> <%s> <%s>\n",
			BASE_PARAM_DESCR, NEED_BASE_PARAM_DESCR, VALUE_PARAM_DESCR);

		return EXIT_FAILURE;
	}

	const short sourceNotation = std::stoi(argv[1]);
	const short destinationNotation = std::stoi(argv[2]);
	if (sourceNotation < MIN_BASE || sourceNotation > MAX_BASE || destinationNotation < MIN_BASE || destinationNotation > MAX_BASE)
	{
		printf("Invalid argument values\n");
		printf("Usage: radix.exe <%s> <%s> <%s>\n",
			BASE_PARAM_DESCR, NEED_BASE_PARAM_DESCR, VALUE_PARAM_DESCR);
		printf("<%s> and <%s> can be only between %d and %d", BASE_PARAM_DESCR, NEED_BASE_PARAM_DESCR, MIN_BASE, MAX_BASE);
		return EXIT_FAILURE;
	}
	const std::string value = argv[3];

	std::cout << "Value given: " << value << std::endl;
	std::cout << "Source's notation: " << sourceNotation << ". Destination notation: " << destinationNotation << std::endl;

	bool wasError = false;

	int decimalVal = StringToInt(value, sourceNotation, wasError);
	if (wasError)
	{
		return EXIT_FAILURE;
	}

	std::string transformedVal = IntToString(decimalVal, destinationNotation, wasError);
	if (wasError)
	{
		return EXIT_FAILURE;
	}

	std::cout << "Transfered number: " << transformedVal << std::endl;

	return EXIT_SUCCESS;
}

struct Alphabet
{
	char albet[ALPHABET_SIZE];
	void initAlphabet();
};

void Alphabet::initAlphabet()
{
	std::iota(std::begin(albet), std::end(albet), ALPHA);
}

struct NumberSystemNotationMap
{
	std::map<int, char> map;
	void generateValueMap(const int& upperValue);
	int getVal(const char& symb);
	char getSymb(const int& val);
	void printMap();
	bool hasValue(const char& symb);
};

void NumberSystemNotationMap::generateValueMap(const int& upperValue)
{
	Alphabet alpbet{};
	alpbet.initAlphabet();

	for (int i = 0; i < upperValue && i < MAX_BASE; i++)
	{
		map[i] = i < DECIMAL_BASE
			? MIN_BASE_ALPHA_VALUE + i
			: alpbet.albet[i - DECIMAL_BASE];
	}
}

int NumberSystemNotationMap::getVal(const char& symb)
{
	int result = -1;
	for (int i = 0; i < map.size(); i++)
	{
		if (i < DECIMAL_BASE && map[i] == symb - '0' || map[i] == toupper(symb))
		{
			result = i;
		}
	}
	return result;
}

constexpr auto NEG_VAL_SYMB = '-';

char NumberSystemNotationMap::getSymb(const int& val)
{
	return map[val] ? map[val] : NEG_VAL_SYMB;
}

bool NumberSystemNotationMap::hasValue(const char& symb)
{
	bool result = false;
	for (int i = 0; i < map.size(); i++)
	{
		if (map[i] == symb)
		{
			result = true;
		}
	}
	return result;
}

void NumberSystemNotationMap::printMap()
{
	std::cout << std::endl;
	std::cout << "|";
	for (int i = 0; i < map.size(); i++)
	{
		printf("%c", map[i]);
		if (i < MAX_BASE - 1)
		{
			std::cout << "|";
		}
	}
	std::cout << std::endl;
}

int StringToInt(const std::string& str, int radix, bool& wasError)
{
	wasError = false;
	int result = 0;
	NumberSystemNotationMap map;
	map.generateValueMap(radix);
	bool isNeg = str[0] == NEG_VAL_SYMB;
	auto offset = isNeg ? 1 : 0;

	const auto strLength = str.length();
	for (auto i = strLength; i > 0 + offset; i--)
	{
		const auto performIndex = strLength - i + offset;
		if (!map.hasValue(toupper(str[performIndex])))
		{
			std::cout << "Failed to convert given value to decimal presentation" << std::endl;
			std::cout << "You can use only these symbols to describe your num:" << std::endl;
			map.printMap();
			wasError = true;
			break;
		}

		const auto delta = map.getVal(str[performIndex]) * ipow(radix, i - 1 - offset);

		result += delta;
		if (result < 0)
		{
			std::cout << "Overflow occured!" << std::endl;
			wasError = true;
			break;
		}
	}

	if (wasError)
	{
		exit(EXIT_FAILURE);
	}
	return isNeg ? -result : result;
}

std::string IntToString(int n, int radix, bool& wasError)
{
	if (n == 0)
	{
		return "0";
	}
	std::string result = "";
	NumberSystemNotationMap map;
	map.generateValueMap(radix);
	int valueInWorkflow = std::abs(n);

	int reminder = 0;
	for (size_t i = 0; valueInWorkflow > 0; i++)
	{
		reminder = valueInWorkflow % radix;
		valueInWorkflow /= radix;
		if (map.getSymb(reminder) == NEG_VAL_SYMB)
		{
			std::cout << "Failed to convert decimal presintation of given number to required" << std::endl;
			std::cout << "<" << BASE_PARAM_DESCR << "> isn't correct" << std::endl;
			wasError = true;
			break;
		}
		result.push_back(map.getSymb(reminder));
	}

	if (wasError)
	{
		exit(EXIT_FAILURE);
	}

	std::reverse(result.begin(), result.end());
	if (n < 0)
	{
		result.insert(result.begin(), NEG_VAL_SYMB);
	}

	return result;
}
