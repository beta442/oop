#pragma once

#include <string>

#include "CUrlParsingError.h"

class HttpUrl
{
public:
	enum class Protocol
	{
		HTTP = 0,
		HTTPS,
	};

public:
	HttpUrl(std::string const& url);
	HttpUrl(std::string const& domain, std::string const& document, Protocol protocol = Protocol::HTTP);
	HttpUrl(std::string const& domain, std::string const& document, Protocol protocol, unsigned short port);

	std::string GetURL() const;
	std::string GetDomain() const;
	std::string GetDocument() const;
	Protocol GetProtocol() const;
	unsigned short GetPort() const;

private:
	unsigned short m_port;
	Protocol m_protocol;
	std::string m_document;
	std::string m_domain;
};
