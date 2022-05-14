#include "../../headers/HttpUrl/CHttpUrl.h"

#include <regex>
#include <sstream>

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

#include <iostream>

HttpUrl::HttpUrl(std::string const& url)
	: m_document()
	, m_domain()
	, m_port(HTTP_PORT)
	, m_protocol(Protocol(0))
{
	std::smatch matches;
	if (!std::regex_match(url, matches, URL_REGEX))
	{
		throw UrlParsingError("Failed to parse Url");
	}

	m_protocol = StringToProtocol(matches[MATCHES_PROTOCOL_INDEX]);
	m_domain = matches[MATCHES_DOMAIN_INDEX];

	m_port = (matches[MATCHES_PORT_INDEX].str().size() <= 1)
		? (m_protocol == Protocol::HTTP ? HTTP_PORT : HTTPS_PORT)
		: StringToPort(matches[MATCHES_PORT_INDEX].str().substr(1));

	const std::string document = std::regex_replace(matches[MATCHES_DOCUMENT_INDEX].str(), std::regex("\\/+"), "/");
	m_document = document.size() != 0 && document[0] == '/' ? document : "/" + document;
}

HttpUrl::HttpUrl(std::string const& domain,
	std::string const& document,
	Protocol protocol)
	: m_document()
	, m_domain()
	, m_port(0)
	, m_protocol(protocol)
{
	if (!std::regex_match(domain, DOMAIN_REGEX))
	{
		throw std::invalid_argument("Invalid domain argument");
	}

	if (!std::regex_match(document, DOCUMENT_REGEX))
	{
		throw std::invalid_argument("Invalid document argument");
	}

	m_domain = domain;
	m_port = m_protocol == Protocol::HTTP ? HTTP_PORT : HTTPS_PORT;

	const std::string doc = std::regex_replace(document, std::regex("\\/+"), "/");
	m_document = doc.size() != 0 && doc[0] == '/' ? doc : "/" + doc;
}

HttpUrl::HttpUrl(std::string const& domain,
	std::string const& document,
	Protocol protocol,
	unsigned short port)
	: m_document()
	, m_domain()
	, m_port(0)
	, m_protocol(protocol)
{
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
	if (IEquals(src, "http"))
	{
		return Protocol::HTTP;
	}
	if (IEquals(src, "https"))
	{
		return Protocol::HTTPS;
	}
	return Protocol::HTTP;
}

unsigned short StringToPort(const std::string& src)
{
	std::stringstream ss{ src };
	unsigned short result = 0;
	if (!(ss >> result))
	{
		throw UrlParsingError("Failed to parse Url. Invalid port");
	}

	return result;
}
