#include <algorithm>
#include <functional>
#include <iostream>
#include <iterator>
#include <optional>
#include <sstream>
#include <string>

void TranslateDecodedHtmlStreamToAnotherStream(std::istream& fIn, std::ostream& fOut);

int main()
{
	TranslateDecodedHtmlStreamToAnotherStream(std::cin, std::cout);

	return 0;
}

std::string HtmlDecode(std::string const& html);

void TranslateDecodedHtmlStreamToAnotherStream(std::istream& fIn, std::ostream& fOut)
{
	std::string buff;
	std::stringstream ss{};
	while (std::getline(fIn, buff))
	{
		if (std::size(buff) != 0)
		{
			ss << buff;
			std::istream_iterator<std::string> it{ ss }, end;
			for (; it != end; it++)
			{
				fOut << HtmlDecode(*it) << " ";
			}
			ss.clear();
		}

		fOut << std::endl;
	}
}

std::optional<char> GetTranslatedHtmlSymbolCodeToChar(const std::string_view& code);

std::string HtmlDecode(const std::string& html)
{
	std::string temp{};
	for (auto it = std::begin(html); it != std::end(html); it++)
	{
		if (*it == '&')
		{
			temp += " &";
		}
		else if (*it == ';')
		{
			temp += "; ";
		}
		else
		{
			temp += *it;
		}
	}

	std::stringstream ss(std::move(temp));

	std::string res{};
	std::istream_iterator<std::string> it{ ss }, end;
	for (; it != end; it++)
	{
		if (std::optional<char> ch = GetTranslatedHtmlSymbolCodeToChar(*it); ch)
		{
			res += ch.value();
		}
		else
		{
			res += *it;
		}
	}

	return res;
}

std::optional<char> GetTranslatedHtmlSymbolCodeToChar(const std::string_view& code)
{
	if (code == "&quot;")
	{
		return '"';
	}
	else if (code == "&apos;")
	{
		return '\'';
	}
	else if (code == "&lt;")
	{
		return '<';
	}
	else if (code == "&gt;")
	{
		return '>';
	}
	else if (code == "&amp;")
	{
		return '&';
	}

	return std::nullopt;
}
