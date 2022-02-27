#include <iostream>
#include <map>
#include <numeric>
#include <sstream>
#include <string>

constexpr auto BASE_PARAM_DESCR = "source notation";
constexpr auto NEED_BASE_PARAM_DESCR = "destination notation";
constexpr auto VALUE_PARAM_DESCR = "value";

constexpr auto ALPHABET_SIZE = 26;
constexpr auto DECIMAL_BASE_CHAR_VALUE = 'A';
constexpr auto MIN_BASE_CHAR_VALUE = 48;
constexpr auto MIN_BASE = 2;
constexpr auto DECIMAL_BASE = 10;
constexpr auto MAX_BASE = DECIMAL_BASE + ALPHABET_SIZE;

int StringToInt(const std::string& str, int radix, bool& wasError);
std::string IntToString(int n, int radix, bool& wasError);

bool MainFuncParamsValidation(const int argc, char* argv[])
{
	bool status = true;
	if (argc != 4)
	{
		printf("Invalid argument count\n");
		printf("Usage: radix.exe <%s> <%s> <%s>\n",
			BASE_PARAM_DESCR, NEED_BASE_PARAM_DESCR, VALUE_PARAM_DESCR);

		status = false;
		return status;
	}

	for (char** arg = argv; *arg; ++arg)
	{
		if (!std::strlen(*arg))
		{
			printf("Invalid arguments value\n");
			printf("Usage: radix.exe <%s> <%s> <%s>\n",
				BASE_PARAM_DESCR, NEED_BASE_PARAM_DESCR, VALUE_PARAM_DESCR);
			printf("One of the arguments is empty\n");

			status = false;
			break;
		}
	}

	return status;
}

int InitParams(short& sourceNotation, short& destinationNotation, std::string& value, char* argv[])
{
	std::stringstream ss;
	bool status = true;
	short buffer;

	ss << argv[1];
	ss >> buffer;
	if (ss.fail())
	{
		status = false;
	}
	sourceNotation = buffer;
	ss.clear();

	ss << argv[2];
	ss >> buffer;
	if (ss.fail())
	{
		status = false;
	}
	destinationNotation = buffer;
	ss.clear();

	if (sourceNotation < MIN_BASE || sourceNotation > MAX_BASE || destinationNotation < MIN_BASE || destinationNotation > MAX_BASE)
	{
		status = false;
	}

	if (!status)
	{
		printf("Invalid argument values\n");
		printf("Usage: radix.exe <%s> <%s> <%s>\n",
			BASE_PARAM_DESCR, NEED_BASE_PARAM_DESCR, VALUE_PARAM_DESCR);
		printf("<%s> and <%s> can be only between %d and %d", BASE_PARAM_DESCR, NEED_BASE_PARAM_DESCR, MIN_BASE, MAX_BASE);
		return status;
	}

	value = argv[3];

	return status;
}

int main(int argc, char* argv[])
{
	if (!MainFuncParamsValidation(argc, argv))
	{
		return EXIT_FAILURE;
	}

	short sourceNotation = 0;
	short destinationNotation = 0;
	std::string value;

	if (!InitParams(sourceNotation, destinationNotation, value, argv))
	{
		return EXIT_FAILURE;
	}

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

	std::cout << "Value given: " << value << std::endl;
	std::cout << "Source's notation: " << sourceNotation << ". Destination notation: " << destinationNotation << std::endl;
	std::cout << "Transfered number: " << transformedVal << std::endl;

	return EXIT_SUCCESS;
}

void PrintMap(std::map<int, char> map)
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

const char NEG_VAL_SYMB = '-';

std::map<int, char> GenerateValueToNotationMap(const int radix)
{
	std::map<int, char> result;

	for (int i = 0; i < radix && i < MAX_BASE; i++)
	{
		if (i < DECIMAL_BASE)
		{
			result.insert(std::pair<int, char>(i, MIN_BASE_CHAR_VALUE + i));
		}
		else
		{
			result.insert(std::pair<int, char>(i, DECIMAL_BASE_CHAR_VALUE + i - DECIMAL_BASE));
		}
	}

	return result;
}

int GetFromValueToNotationMapValueOfSpecificNotation(std::map<int, char> map, const char val)
{
	int result = -1;

	for (int i = 0; i < map.size(); i++)
	{
		if (map[i] == val)
		{
			result = i;
			break;
		}
	}

	return result;
}

int CountDelta(const size_t pos, const std::string& str, const int radix, const short offset, const std::map<int, char> map)
{
	size_t performIndex = str.length() - pos + offset;
	char valueInWorkflow = toupper(str[performIndex]);
	int valueOfSpecificNotation = GetFromValueToNotationMapValueOfSpecificNotation(map, valueInWorkflow);
	if (valueOfSpecificNotation == -1)
	{
		return -1;
	}

	return valueOfSpecificNotation * static_cast<int>(std::pow(radix, pos - 1 - offset));
}

int StringToInt(const std::string& str, int radix, bool& wasError)
{
	wasError = false;
	int result = 0;

	std::map<int, char> map = GenerateValueToNotationMap(radix);
	bool isNeg = str[0] == NEG_VAL_SYMB;
	short offset = isNeg ? 1 : 0;

	int delta;
	for (size_t i = str.length(); i > offset; i--)
	{

		delta = CountDelta(i, str, radix, offset, map);
		if (delta == -1)
		{
			std::cout << "Failed to convert given value to decimal presentation" << std::endl;
			std::cout << "You can use only these symbols to describe your num:" << std::endl;
			PrintMap(map);
			wasError = true;
			break;
		}

		result += delta;
		if (result < 0)
		{
			std::cout << "Err!\nGiven value is too big for this app" << std::endl;
			wasError = true;
			break;
		}
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
	std::map<int, char> map = GenerateValueToNotationMap(radix);
	int valueInWorkflow = std::abs(n);

	int reminder = 0;
	for (size_t i = 0; valueInWorkflow > 0; i++)
	{
		reminder = valueInWorkflow % radix;
		valueInWorkflow /= radix;
		if (map[reminder] == NEG_VAL_SYMB)
		{
			std::cout << "Failed to convert decimal presintation of given number to required" << std::endl;
			std::cout << "<" << BASE_PARAM_DESCR << "> isn't correct" << std::endl;
			wasError = true;
			break;
		}
		result.push_back(map[reminder]);
	}

	std::reverse(result.begin(), result.end());
	if (n < 0)
	{
		result.insert(result.begin(), NEG_VAL_SYMB);
	}

	return result;
}
