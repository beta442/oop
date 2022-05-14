#include "../../headers/HttpUrl/CHttpUrl.h"

#include <iostream>

#include <algorithm>
#include <regex>

using Protocol = HttpUrl::Protocol;

const std::regex URL_REGEX = std::regex("([hH][tT]{2}[pP][sS]?):\\/{2,}(\\w+\\.\\w+\\.\\w+|\\w+\\.\\w+)([:\\d]{2,5})?\\/([\\w\\/\\.?=&#]*)?");

constexpr auto MATCHES_URL_INDEX = 0;
constexpr auto MATCHES_PROTOCOL_INDEX = 1;
constexpr auto MATCHES_DOMAIN_INDEX = 2;
constexpr auto MATCHES_PORT_INDEX = 3;
constexpr auto MATCHES_DOCUMENT_INDEX = 4;

Protocol StringToProtocol(const std::string& src);

HttpUrl::HttpUrl(std::string const& url)
	: m_document()
	, m_domain()
	, m_port(0)
	, m_protocol(Protocol(0))
	, m_url()
{
	std::smatch matches;
	if (!std::regex_match(url, matches, URL_REGEX))
	{
		throw UrlParsingError("Failed to parse Url");
	}
	m_url = url;

	m_protocol = StringToProtocol(matches[MATCHES_PROTOCOL_INDEX]);

	size_t i = 0;
	for (auto it = std::begin(matches), end = std::end(matches); it != end; ++it, ++i)
	{
		std::cout << "i=" << i << "<->" << *it << std::endl;
	}
}

HttpUrl::HttpUrl(std::string const& domain,
	std::string const& document,
	Protocol protocol)
	: m_document()
	, m_domain()
	, m_port(0)
	, m_protocol(protocol)
	, m_url()
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
	, m_url()
{
}

std::string HttpUrl::GetURL() const
{
	return m_url;
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
