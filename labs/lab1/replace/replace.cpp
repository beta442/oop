#include <iostream>
#include <fstream>
#include <string>

constexpr auto INPUT_FILE = "inputFile";
constexpr auto OUTPUT_FILE = "outputFile";
constexpr auto REPLACMENT_STRING = "replacmentString";
constexpr auto SEARCH_STRING = "searchString";

std::string ReplaceString(const std::string& str, const std::string& needle, const std::string& newstr)
{
	size_t pos = 0;
	std::string result = needle.length() ? "" : str;

	if (needle.length())
	{
		while (pos < str.length())
		{
			size_t foundPos = str.find(needle, pos);
			result.append(str, pos, foundPos - pos);
			if (foundPos != std::string::npos)
			{
				result.append(newstr);
				pos = foundPos + needle.length();
			}
			else
			{
				break;
			}
		}
	}
	return result;
}

void CopyFileWithReplace(std::istream& fIn, std::ostream& fO, const std::string& find, const std::string& replace)
{
	std::string line;

	while (getline(fIn, line))
	{
		fO << ReplaceString(line, find, replace) << "\n";
	}
	fO.flush();
}

int main(int argc, char* argv[])
{
	std::ifstream fIn;
	std::ofstream fO;

	std::string searchString;
	std::string replacmentString;

	if (argc != 5)
	{
		printf("Invalid argument count\n");
		printf("Usage: replace.exe <%s> <%s> <%s> <%s>\n", INPUT_FILE, OUTPUT_FILE, SEARCH_STRING, REPLACMENT_STRING);

		return EXIT_FAILURE;
	}

	fIn.open(argv[1]);
	std::string tempStr;
	if (!fIn.is_open() || !getline(fIn, tempStr))
	{
		printf("Something bad with input file\n");
		return EXIT_FAILURE;
	}
	fIn.seekg(0, fIn.beg);

	fO.open(argv[2]);
	if (!fO.is_open())
	{
		printf("Something bad with output file\n");
		return EXIT_FAILURE;
	}

	searchString = argv[3];
	replacmentString = argv[4];

	std::cout << "string to find:\"" << searchString << "\"" << std::endl;
	std::cout << "string to replace:\"" << replacmentString << "\"" << std::endl;

	CopyFileWithReplace(fIn, fO, searchString, replacmentString);

	return EXIT_SUCCESS;
}
