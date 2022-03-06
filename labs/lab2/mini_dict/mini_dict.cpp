#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <sstream>
#include <string>

bool ParseArgs(int argc, char* argv[], std::fstream& stream)
{
	const bool isOk = true;
	if (argc != 2 || std::strlen(argv[1]) == 0)
	{
		std::cout << "Usage:" << std::endl
				  << "PROGRAMNAME.exe <dictionary>" << std::endl;
		std::cout << "No dictionary was provided" << std::endl
				  << "Program will create temporary dictionary in working directory, "
				  << "that you can save later " << std::endl;
		return !isOk;
	}

	stream.open(argv[1], std::ios::in);
	if (stream.fail() || !stream.is_open())
	{
		std::cout << "An error occured while opening dictionary file" << std::endl;
		return !isOk;
	}

	return isOk;
}

enum class DictionarySaveStatus
{
	NeedToSave,
	NotNeedToSave
};

std::map<std::string, std::string> MakeDictionaryFromStream(std::fstream& stream);
DictionarySaveStatus TranclateCinByDictionary(std::map<std::string, std::string>& dict);

int main(int argc, char* argv[])
{
	std::fstream dictionaryStream;
	if (!ParseArgs(argc, argv, dictionaryStream))
	{
		dictionaryStream.open("new_dict.txt");
	}

	std::map<std::string, std::string> dict = MakeDictionaryFromStream(dictionaryStream);

	if (TranclateCinByDictionary(dict) == DictionarySaveStatus::NeedToSave)
	{
		for (const auto& [key, translation] : dict)
		{
			dictionaryStream << key << " " << translation << std::endl;
		}
	}

	return 0;
}

size_t WordCount(const std::string& str);
std::pair<std::string, std::string> MakePairOfKeyWordAndItsTranslationVariantsFromString(const std::string& str);

std::map<std::string, std::string> MakeDictionaryFromStream(std::fstream& stream)
{
	std::map<std::string, std::string> res;

	std::string buff;
	for (size_t i = 0; std::getline(stream, buff); i++)
	{
		if (WordCount(buff) < 2)
		{
			std::cout << "Wrong dictionary format on line " << i << "!" << std::endl
					  << "Each line in dictionary should have at least two words separated by space - ' '" << std::endl;
			continue;
		}
		auto [keyWord, translation] = MakePairOfKeyWordAndItsTranslationVariantsFromString(buff);
		if (res.find(keyWord) == std::end(res))
		{
			res[keyWord] = translation;
		}
		else
		{
			res[keyWord] += translation;
		}
	}

	return res;
}

size_t WordCount(const std::string& str)
{
	std::stringstream ss{};
	ss << str;
	return std::distance(std::istream_iterator<std::string>{ ss }, {});
}

std::pair<std::string, std::string> MakePairOfKeyWordAndItsTranslationVariantsFromString(const std::string& str)
{
	std::pair<std::string, std::string> res;
	if (std::size(str) == 0)
	{
		return res;
	}
	std::string translations, key;
	std::stringstream ss{};
	ss << str;
	std::istream_iterator<std::string> it{ ss }, end;

	key = *it;
	while (true)
	{
		it++;
		if (it == end)
		{
			break;
		}
		translations += *it + " ";
	}
	res = std::pair<std::string, std::string>{ key, translations };

	return res;
}

std::string GetWordTranslation(std::map<std::string, std::string>& dict, std::string& word);

DictionarySaveStatus TranclateCinByDictionary(std::map<std::string, std::string>& dict)
{
	std::string buff, translation;

	std::cout << "Please, enter phrase translate to:" << std::endl;
	std::getline(std::cin, buff);
	do
	{
		if (std::size(buff) == 0)
		{
			continue;
		}
		std::cout << "You entered: " << buff << std::endl;
		if (buff == "...")
		{
			do
			{
				std::cout << "Enter Y/y or N/n if need to save performed dictionary" << std::endl;
				std::getline(std::cin, buff);
			} while (buff != "N" && buff != "n" && buff != "Y" && buff != "y");
			if (buff == "N" || buff == "n")
			{
				return DictionarySaveStatus::NotNeedToSave;
			}
			return DictionarySaveStatus::NeedToSave;
		}

		translation = GetWordTranslation(dict, buff);
		if (std::size(translation))
		{
			std::cout << "Translation: " << translation << std::endl;
		}
		else
		{
			std::cout << "Unknown word '" << buff << "'. Enter translation or empty line to skip" << std::endl;
			std::getline(std::cin, translation);
			if (std::size(translation))
			{
				dict[buff] = translation;
			}
		}

		std::cout << std::endl
				  << "Please, enter phrase translate to:" << std::endl;
		std::cout << "You can enter ... to stop translating" << std::endl;
	} while (std::getline(std::cin, buff));

	return DictionarySaveStatus::NeedToSave;
}

bool iequals(const std::string& a, const std::string& b);
bool InsensetiveStringHasSubString(std::string& str, std::string& needle);

std::string GetWordTranslation(std::map<std::string, std::string>& dict, std::string& word)
{
	std::string res;

	for (auto& [keyWord, translation] : dict)
	{
		if (iequals(keyWord, word))
		{
			res += dict[keyWord] + " ";
		}
		if (InsensetiveStringHasSubString(translation, word))
		{
			res += keyWord + " ";
		}
	}

	return res;
}

bool InsensetiveStringHasSubString(std::string& str, std::string& needle)
{
	bool res = false;

	std::stringstream ss;
	ss << str;
	std::istream_iterator<std::string> it{ ss }, end;
	for (; it != end; it++)
	{
		if (iequals(*it, needle))
		{
			return !res;
		}
	}

	return res;
}

bool iequals(const std::string& a, const std::string& b)
{
	return std::equal(a.begin(), a.end(),
		b.begin(), b.end(),
		[](char a, char b) {
			return tolower(a) == tolower(b);
		});
}
