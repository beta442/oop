#include "../../headers/HttpUrl/CHttpUrl.h"

#include <regex>

using Protocol = HttpUrl::Protocol;

const std::regex URL_REGEX = std::regex("(https?):\\/{2,}(\\w+\\.\\w+\\.\\w+|\\w+\\.\\w+)([:\\d]{2,5})?\\/([\\w\\/\\.?=&#]*)?");

HttpUrl::HttpUrl(std::string const& url)
	: m_document()
	, m_domain()
	, m_port(0)
	, m_protocol(Protocol(0))
{
	std::smatch matches;
	if (!std::regex_match(url, matches, URL_REGEX))
	{
		throw UrlParsingError("Failed to parse Url");
	}
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

std::string HttpUrl::GetURL() const
{
	return std::string();
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
