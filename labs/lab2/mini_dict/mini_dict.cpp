#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <optional>
#include <sstream>
#include <string>

using DictionaryNode = std::pair<std::string, std::string>;
using Dictionary = std::map<std::string, std::string>;

std::optional<std::string> ParseArg(int argc, char* argv[])
{
	if (argc != 2 || std::strlen(argv[1]) == 0)
	{
		std::cout << "Usage:" << std::endl
				  << "PROGRAMNAME.exe <dictionary>" << std::endl;
		std::cout << "No dictionary was provided" << std::endl
				  << "Program will create temporary dictionary in working directory, "
				  << "that you can save later " << std::endl;
		return std::nullopt;
	}

	return std::optional<std::string>{ argv[1] };
}

enum class DictionaryUpdatedStatus
{
	NeedToSave,
	NotNeedToSave
};

Dictionary MakeDictionaryFromFileByFileName(std::string fileName);
DictionaryUpdatedStatus TranslateStreamByDictionary(std::istream& stream, Dictionary& dict);
void SaveDictionaryToFileByFileName(const Dictionary& dict, const std::string& fileName);

int main(int argc, char* argv[])
{
	std::optional<std::string> oFileName = ParseArg(argc, argv);

	std::string fileName = oFileName ? oFileName.value() : "created_dict.txt";
	Dictionary dict = MakeDictionaryFromFileByFileName(fileName);

	if (TranslateStreamByDictionary(std::cin, dict) == DictionaryUpdatedStatus::NeedToSave)
	{
		SaveDictionaryToFileByFileName(dict, fileName);
	}

	return 0;
}

size_t WordCount(std::string str);
DictionaryNode MakePairOfKeyWordAndItsTranslationVariantsFromString(std::string str);

Dictionary MakeDictionaryFromFileByFileName(std::string fileName)
{
	Dictionary res;

	std::ifstream stream;
	stream.open(fileName);
	if (!stream.is_open())
	{
		return res;
	}

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

size_t WordCount(std::string str)
{
	std::stringstream ss{};
	ss << str;
	return std::distance(std::istream_iterator<std::string>{ ss }, {});
}

DictionaryNode MakePairOfKeyWordAndItsTranslationVariantsFromString(std::string str)
{
	DictionaryNode res;
	if (std::size(str) == 0)
	{
		return res;
	}
	std::string translations, key;
	std::stringstream ss{ str };
	std::istream_iterator<std::string> it{ ss }, end;

	key = *it;
	while (it != end)
	{
		it++;
		translations += *it + " ";
	}
	translations.erase(std::end(translations) - 1);
	key.shrink_to_fit();
	translations.shrink_to_fit();
	res = DictionaryNode{ key, translations };

	return res;
}

std::string GetWordTranslation(Dictionary& dict, const std::string& word);
DictionaryUpdatedStatus DecideToUpdateDictionaryByUserInput();
std::string GetTrimString(const std::string& str);

DictionaryUpdatedStatus TranslateStreamByDictionary(std::istream& stream, Dictionary& dict)
{
	std::string buff, translation;

	std::cout << "Please, enter phrase translate to:" << std::endl;
	std::getline(stream, buff);
	do
	{
		if (std::size(buff) == 0)
		{
			continue;
		}

		std::cout << "You entered: " << buff << std::endl;
		if (buff == "...")
		{
			return DecideToUpdateDictionaryByUserInput();
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
				dict[buff] = GetTrimString(translation);
			}
		}

		std::cout << std::endl
				  << "Please, enter phrase translate to:" << std::endl;
		std::cout << "You can enter ... to stop translating" << std::endl;
	} while (std::getline(stream, buff));

	return DictionaryUpdatedStatus::NeedToSave;
}

bool iequals(const std::string& a, const std::string& b);
bool InsensetiveStringHasSubString(const std::string& str, const std::string& needle);

std::string GetWordTranslation(Dictionary& dict, const std::string& word)
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
	res.shrink_to_fit();

	return res;
}

DictionaryUpdatedStatus DecideToUpdateDictionaryByUserInput()
{
	std::string buff;
	do
	{
		std::cout << "Enter Y/y or N/n if need to save performed dictionary" << std::endl;
		std::getline(std::cin, buff);
	} while (buff != "N" && buff != "n" && buff != "Y" && buff != "y");
	if (buff == "N" || buff == "n")
	{
		return DictionaryUpdatedStatus::NotNeedToSave;
	}
	return DictionaryUpdatedStatus::NeedToSave;
}

std::string GetTrimString(const std::string& str)
{
	std::string res;
	std::stringstream ss{ str };
	std::istream_iterator<std::string> it{ ss }, end;

	for (; it != end; it++)
	{
		res += *it + " ";
	}
	res.erase(std::end(res) - 1);
	res.shrink_to_fit();

	return res;
}

bool InsensetiveStringHasSubString(const std::string& str, const std::string& needle)
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

void SaveDictionaryToFileByFileName(const Dictionary& dict, const std::string& fileName)
{
	std::ofstream stream;
	stream.open(fileName);
	if (!stream.is_open())
	{
		std::cout << "Failed to save dictionary" << std::endl;
		return;
	}

	for (const auto& [key, translation] : dict)
	{
		stream << key << " " << translation << std::endl;
	}
}
