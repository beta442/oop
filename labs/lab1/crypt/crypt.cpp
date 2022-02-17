#include <fstream>
#include <iostream>
#include <string>

constexpr auto MODE_CRYPT = "crypt";
constexpr auto MODE_DECRYPT = "decrypt";
constexpr auto INPUT_FILE_PARAM = "input file";
constexpr auto OUTPUT_FILE_PARAM = "output file";
constexpr auto KEY_PARAM = "key";
constexpr auto KEY_PARAM_MIN_VALUE = 0;
constexpr auto KEY_PARAM_MAX_VALUE = 255;

constexpr short ERR_CODE_INVALID_PARAM_LENGTH = 2;
constexpr short ERR_CODE_INVALID_KEY_VALUE = 3;
constexpr short ERR_CODE_INVALID_PROGRAM_MODE_PARAM = 4;

enum class ProgramMode
{
	CRYPT = 0,
	DECRYPT,
};

int main(int argc, char* argv[])
{
	std::ifstream fIn;
	std::ofstream fOut;

	if (argc != 5)
	{
		printf("Invalid argument count\n");
		printf("Usage: crypt.exe <%s|%s> <%s> <%s> <%s>\n", MODE_CRYPT, MODE_DECRYPT, INPUT_FILE_PARAM, OUTPUT_FILE_PARAM, KEY_PARAM);

		return EXIT_FAILURE;
	}

	short key = 0;
	auto mode = ProgramMode::CRYPT;

	try
	{
		if (std::strlen(argv[1]) == 0 || std::strlen(argv[2]) == 0 || std::strlen(argv[3]) == 0 || std::strlen(argv[4]) == 0)
		{
			throw ERR_CODE_INVALID_PARAM_LENGTH;
		}

		if (std::string(argv[1]) != MODE_CRYPT && std::string(argv[1]) != MODE_DECRYPT)
		{
			throw ERR_CODE_INVALID_PROGRAM_MODE_PARAM;
		}
		if (std::string(argv[1]) == MODE_CRYPT)
		{
			mode = ProgramMode::CRYPT;
		}
		if (std::string(argv[1]) == MODE_DECRYPT)
		{
			mode = ProgramMode::DECRYPT;
		}

		key = std::stoi(argv[4]);
		if (key < 0 || key > 255)
		{
			throw ERR_CODE_INVALID_KEY_VALUE;
		}
	}
	catch (short err_code)
	{
		printf("Invalid arguments value\n");
		printf("Usage: crypt.exe <%s|%s> <%s> <%s> <%s>\n", MODE_CRYPT, MODE_DECRYPT, INPUT_FILE_PARAM, OUTPUT_FILE_PARAM, KEY_PARAM);
		if (err_code == ERR_CODE_INVALID_PROGRAM_MODE_PARAM)
		{
			printf("<%s|%s> is program mode, use \"%s\" or \"%s\" to specify what program should do\n", MODE_CRYPT, MODE_DECRYPT, MODE_CRYPT, MODE_DECRYPT);
		}
		if (err_code == ERR_CODE_INVALID_KEY_VALUE)
		{
			printf("<%s> should be represented by value between %d and %d\n", KEY_PARAM, KEY_PARAM_MIN_VALUE, KEY_PARAM_MAX_VALUE);
		}
		exit(EXIT_FAILURE);
	}

	fIn.open(argv[2]);
	std::string tempStr;
	if (!fIn.is_open() || !getline(fIn, tempStr))
	{
		printf("Something bad with input file\n");
		return EXIT_FAILURE;
	}
	fIn.seekg(0, fIn.beg);

	fOut.open(argv[3]);
	if (!fOut.is_open())
	{
		printf("Something bad with output file\n");
		return EXIT_FAILURE;
	}

	printf("\nGot:\n");
	printf("<%s>: %s;\n", INPUT_FILE_PARAM, argv[2]);
	printf("<%s>: %s;\n", OUTPUT_FILE_PARAM, argv[3]);
	printf("Mode: %s;\n", mode == ProgramMode::CRYPT ? MODE_CRYPT : MODE_DECRYPT);
	printf("Key: %d;\n", key);

	return EXIT_SUCCESS;
}

typedef union
{
	char ch;
	struct
	{
		unsigned int bytes : sizeof(char);
	} byte_part;
} Char_cast;

struct Symbol
{
	Char_cast symb;
	void setChar(const char& ch);
	void printBytePresentation();
};

void Symbol::setChar(const char& ch)
{
	symb.ch = ch;
}

void Symbol::printBytePresentation()
{
	printf("%d", symb.byte_part.bytes);
}
