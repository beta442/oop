#include "../../headers/HttpUrl/CHttpUrl.h"

#include <regex>
#include <sstream>

using Protocol = HttpUrl::Protocol;

const std::regex URL_REGEX = std::regex("([hH][tT]{2}[pP][sS]?):\\/{2,}(\\w+\\.\\w+\\.\\w+|\\w+\\.\\w+)([:\\d]{2,5})?(\\/[\\w\\/\\.?=\\-&#]*)?");

constexpr auto MATCHES_URL_INDEX = 0;
constexpr auto MATCHES_PROTOCOL_INDEX = 1;
constexpr auto MATCHES_DOMAIN_INDEX = 2;
constexpr auto MATCHES_PORT_INDEX = 3;
constexpr auto MATCHES_DOCUMENT_INDEX = 4;

constexpr auto HTTP_PORT = 80;
constexpr auto HTTPS_PORT = 443;

Protocol StringToProtocol(const std::string& src);
unsigned short StringToPort(const std::string& src);

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

	m_port = (matches[MATCHES_PORT_INDEX].str().size() == 0 || matches[MATCHES_PORT_INDEX].str().size() == 1)
		? (m_protocol == Protocol::HTTP ? HTTP_PORT : HTTPS_PORT)
		: StringToPort(matches[MATCHES_PORT_INDEX].str().substr(1));

	m_document = matches[MATCHES_DOCUMENT_INDEX].str().size() == 0 ? "/" : matches[MATCHES_DOCUMENT_INDEX].str();
}

HttpUrl::HttpUrl(std::string const& domain,
	std::string const& document,
	Protocol protocol)
	: m_document()
	, m_domain()
	, m_port(0)
	, m_protocol(protocol)
{
}

HttpUrl::HttpUrl(std::string const& domain,
	std::string const& document,
	Protocol protocol,
	unsigned short port)
	: m_document()
	, m_domain()
	, m_port(0)
	, m_protocol(Protocol(0))
{
}

const std::string HTTP_STRING = "http";
const std::string HTTPS_STRING = "https";

std::string HttpUrl::GetURL() const
{
	std::string result{};
	result += m_protocol == Protocol::HTTP ? HTTPS_STRING : HTTPS_STRING;
	result += "://";
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
