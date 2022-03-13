#pragma once

#include <iterator>
#include <optional>
#include <sstream>
#include <string>

std::string HtmlDecodeWord(const std::string& html);
std::string HtmlDecode(const std::string& html)
{
	std::stringstream ss{};
	std::string res;

	if (std::size(html) != 0)
	{
		ss << html;
		for (std::istream_iterator<std::string> it{ ss }, end; it != end; it++)
		{
			res += HtmlDecodeWord(*it) + ' ';
		}
		ss.clear();
		res.resize(std::size(res) - 1);
	}

	return res;
}

std::optional<char> GetTranslatedHtmlSymbolCodeToChar(const std::string_view& code);
std::string HtmlDecodeWord(const std::string& html)
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
	for (std::istream_iterator<std::string> it{ ss }, end; it != end; it++)
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
