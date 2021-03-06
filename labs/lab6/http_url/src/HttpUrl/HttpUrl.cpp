#include "../../headers/HttpUrl/CHttpUrl.h"

#include <regex>
#include <sstream>
#include <iostream>

using Protocol = HttpUrl::Protocol;

const std::string PROTOCOL_REGEX_STRING = "([hH][tT]{2}[pP][sS]?):\\/{2,}";
const std::string DOMAIN_REGEX_STRING = "(\\w+\\.\\w+\\.\\w+|\\w+\\.\\w+)";
const std::string PORT_REGEX_STRING = "([:\\d]{2,5})?";
const std::string DOCUMENT_REGEX_STRING = "(\\/+[\\w\\/\\.?=\\-&#]*)?";

const std::regex URL_REGEX = std::regex(PROTOCOL_REGEX_STRING + DOMAIN_REGEX_STRING + PORT_REGEX_STRING + DOCUMENT_REGEX_STRING);
const std::regex DOMAIN_REGEX = std::regex(DOMAIN_REGEX_STRING);
const std::regex DOCUMENT_REGEX = std::regex(DOCUMENT_REGEX_STRING);
  
constexpr auto MATCHES_URL_INDEX = 0;
constexpr auto MATCHES_PROTOCOL_INDEX = 1;
constexpr auto MATCHES_DOMAIN_INDEX = 2;
constexpr auto MATCHES_PORT_INDEX = 3;
constexpr auto MATCHES_DOCUMENT_INDEX = 4;

constexpr auto HTTP_PORT = 80;
constexpr auto HTTPS_PORT = 443;

Protocol StringToProtocol(const std::string& src);
unsigned short StringToPort(const std::string& src);

std::string FormatDocument(const std::string& src);

HttpUrl::HttpUrl(std::string const& url)
{
	std::smatch matches;
	if (!std::regex_match(url, matches, URL_REGEX))
	{
		throw UrlParsingError("Failed to parse Url");
	}

	m_protocol = StringToProtocol(matches[MATCHES_PROTOCOL_INDEX]);
	m_domain = matches[MATCHES_DOMAIN_INDEX];

	try
	{
		m_port = (matches[MATCHES_PORT_INDEX].str().size() <= 1)
			? (m_protocol == Protocol::HTTP ? HTTP_PORT : HTTPS_PORT)
			: StringToPort(matches[MATCHES_PORT_INDEX].str().substr(1));
	}
	catch (...)
	{
		m_protocol = Protocol::HTTP;
		m_domain = "";
		throw;
	}

	m_document = FormatDocument(matches[MATCHES_DOCUMENT_INDEX].str());
}

std::string CheckDomain(const std::string& src);
std::string CheckDocument(const std::string& src);

HttpUrl::HttpUrl(std::string const& domain,
	std::string const& document,
	Protocol protocol)
	: m_protocol(protocol)
{
	m_domain = CheckDomain(domain);
	m_document = CheckDocument(document);
	m_domain = domain;
	m_port = m_protocol == Protocol::HTTP ? HTTP_PORT : HTTPS_PORT;
	m_document = FormatDocument(document);
}

HttpUrl::HttpUrl(std::string const& domain,
	std::string const& document,
	Protocol protocol,
	unsigned short port)
	: m_protocol(protocol)
{
	m_domain = CheckDomain(domain);
	m_document = CheckDocument(document);
	m_domain = domain;
	m_port = port;
	m_document = FormatDocument(document);
}

const std::string BETWEEN_PROTOCOL_AND_DOMAIN_STRING = "://";
const std::string HTTP_STRING = "http";
const std::string HTTPS_STRING = "https";

std::string HttpUrl::GetURL() const
{
	std::string result{};
	result += m_protocol == Protocol::HTTP ? HTTPS_STRING : HTTPS_STRING;
	result += BETWEEN_PROTOCOL_AND_DOMAIN_STRING;
	result += m_domain;
	result += m_document;

	return result;
}

std::string HttpUrl::GetDomain() const
{
	return m_domain;
}

std::string HttpUrl::GetDocument() const
{
	return m_document;
}

Protocol HttpUrl::GetProtocol() const
{
	return m_protocol;
}

unsigned short HttpUrl::GetPort() const
{
	return m_port;
}

bool IEquals(const std::string& a, const std::string& b)
{
	return std::equal(a.begin(), a.end(),
		b.begin(), b.end(),
		[](char a, char b) {
			return tolower(a) == tolower(b);
		});
}

Protocol StringToProtocol(const std::string& src)
{
	if (IEquals(src, HTTP_STRING))
	{
		return Protocol::HTTP;
	}
	if (IEquals(src, HTTPS_STRING))
	{
		return Protocol::HTTPS;
	}
	return Protocol::HTTP;
}

unsigned short StringToPort(const std::string& src)
{
	unsigned short result = 0;

	try
	{
		result = std::stoi(src);
	}
	catch (const std::invalid_argument&)
	{
		throw std::invalid_argument("Failed to parse Port. Invalid argument");
	}
	catch (const std::out_of_range&)
	{
		throw std::out_of_range("Failed to parse Port. Argument is out of range");
	}

	return result;
}

std::string CheckDomain(const std::string& src)
{
	if (!std::regex_match(src, DOMAIN_REGEX))
	{
		throw std::invalid_argument("Invalid domain argument");
	}

	return src;
}

std::string CheckDocument(const std::string& src)
{
	if (!std::regex_match(src, DOCUMENT_REGEX))
	{
		throw std::invalid_argument("Invalid document argument");
	}

	return src;
}

std::string FormatDocument(const std::string& src)
{
	const auto cleanDocument = std::regex_replace(src, std::regex("\\/+"), "/");
	return cleanDocument.size() != 0 && cleanDocument[0] == '/' ? cleanDocument : "/" + cleanDocument;
	
}
