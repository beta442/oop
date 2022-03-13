#include <iostream>
#include <iterator>
#include <optional>
#include <sstream>
#include <string>

void DecodeHtmlCInToCOut();

int main()
{
	DecodeHtmlCInToCOut();

	return 0;
}

std::string HtmlDecode(std::string const& html);

void DecodeHtmlCInToCOut()
{
	std::string buff;
	std::stringstream ss{};
	while (std::getline(std::cin, buff))
	{
		if (std::size(buff) != 0)
		{
			ss << buff;
			for (std::istream_iterator<std::string> it{ ss }, end; it != end; it++)
			{
				std::cout << HtmlDecode(*it) << " ";
			}
			ss.clear();
		}

		std::cout << std::endl;
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
