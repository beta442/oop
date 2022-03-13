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
				  << "that you can decide save or not later " << std::endl;
		return std::nullopt;
	}

	return std::optional<std::string>{ argv[1] };
}

enum class DictionaryNeedUpdateStatus
{
	NeedToSave,
	NotNeedToSave,
};

Dictionary MakeDictionaryFromFileByFileName(std::string fileName);
DictionaryNeedUpdateStatus TranslateIStreamByDictionary(std::istream& istream, Dictionary& dict);
void SaveDictionaryToFileByFileName(const Dictionary& dict, const std::string& fileName);

int main(int argc, char* argv[])
{
	std::optional<std::string> oFileName = ParseArg(argc, argv);

	std::string fileName = oFileName ? oFileName.value() : "created_dict.txt";
	Dictionary dict = MakeDictionaryFromFileByFileName(fileName);

	if (TranslateIStreamByDictionary(std::cin, dict) == DictionaryNeedUpdateStatus::NeedToSave)
	{
		SaveDictionaryToFileByFileName(dict, fileName);
	}

	return 0;
}

size_t WordCount(const std::string& str);
DictionaryNode MakePairOfFirstKeyWordAndItsTranslationVariantsFromString(const std::string& str);

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
		auto [keyWord, translation] = MakePairOfFirstKeyWordAndItsTranslationVariantsFromString(buff);
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

DictionaryNode MakePairOfFirstKeyWordAndItsTranslationVariantsFromString(const std::string& str)
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

constexpr auto TERMINAL_SYMBOL = '>';

std::optional<DictionaryNeedUpdateStatus> DecideToUpdateDictionaryByUserInput();

bool GetLineFromStream(std::istream& istream, std::string& str);
std::string GetPhraseTranslation(Dictionary& dict, const std::string& phrase);
std::string GetTrimString(const std::string& str);

DictionaryNeedUpdateStatus TranslateIStreamByDictionary(std::istream& istream, Dictionary& dict)
{
	std::string buff, translation;

	std::optional<DictionaryNeedUpdateStatus> userDecision;
	while (GetLineFromStream(istream, buff))
	{
		if (std::size(buff) == 0)
		{
			continue;
		}

		if (buff == "...")
		{
			if (userDecision = DecideToUpdateDictionaryByUserInput();
				userDecision)
			{
				break;
			}
			continue;
		}

		if (translation = GetPhraseTranslation(dict, GetTrimString(buff)); std::size(translation) != 0)
		{
			std::cout << translation << std::endl;
		}
		else
		{
			std::cout << "Unknown word '" << buff << "'. Enter translation or empty line to skip" << std::endl;
			std::getline(std::cin, translation);
			if (std::size(translation))
			{
				dict[GetTrimString(buff)] = GetTrimString(translation);
			}
		}
	}

	return userDecision.value();
}

bool GetLineFromStream(std::istream& istream, std::string& str)
{
	std::cout << std::endl
			  << "Please, enter phrase translate to or ... to stop translating:" << std::endl
			  << TERMINAL_SYMBOL;
	if (std::getline(istream, str))
	{
		return true;
	}
	return false;
}

bool iequals(const std::string& a, const std::string& b);
bool InsensetiveStringHasSubString(const std::string& str, const std::string& needle);
std::string GetFirstWord(const std::string& phrase);

std::string GetPhraseTranslation(Dictionary& dict, const std::string& phrase)
{
	if (std::size(phrase) == 0)
	{
		return "";
	}
	std::string res;

	for (auto& [keyWord, translation] : dict)
	{
		if (iequals(keyWord, phrase))
		{
			res += dict[keyWord] + " ";
		}
		if (iequals(translation, phrase))
		{
			res += keyWord + " ";
		}
	}

	return GetTrimString(res);
}

std::optional<DictionaryNeedUpdateStatus> DecideToUpdateDictionaryByUserInput()
{
	std::string buff;
	do
	{
		std::cout << std::endl;
		std::cout << "Enter Y/y or N/n if need to save performed dictionary" << std::endl;
		std::cout << "Or enter '...' again to return back to translating" << std::endl
				  << TERMINAL_SYMBOL;
		std::getline(std::cin, buff);
	} while (buff != "N" && buff != "n" && buff != "Y" && buff != "y" && buff != "...");
	if (buff == "N" || buff == "n")
	{
		return DictionaryNeedUpdateStatus::NotNeedToSave;
	}
	if (buff == "Y" || buff == "y")
	{
		return DictionaryNeedUpdateStatus::NeedToSave;
	}
	return std::nullopt;
}

std::string GetTrimString(const std::string& str)
{
	if (std::size(str) == 0)
	{
		return "";
	}
	std::string res;
	std::stringstream ss{ str };

	for (std::istream_iterator<std::string> it{ ss }, end; it != end; it++)
	{
		res += *it + " ";
	}
	res.erase(std::end(res) - 1);
	res.shrink_to_fit();

	return res;
}

std::string GetFirstWord(const std::string& phrase)
{
	if (std::size(phrase) == 0)
	{
		return "";
	}

	std::stringstream ss{ phrase };
	std::istream_iterator<std::string> it{ ss };

	return *it;
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
