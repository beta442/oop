#pragma once

#include "std_lib.h"

enum class Protocol
{
	HTTP,
	HTTPS,
	FTP,
};

bool ParseURL(std::string const& url, Protocol& protocol, int& port, std::string& host, std::string& document);
void PrintUrlInfo(const std::string& url,
	const Protocol& protocol,
	int port,
	const std::string& host,
	const std::string& document);
