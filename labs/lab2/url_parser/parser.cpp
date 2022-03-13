#include <iostream>
#include <optional>
#include <regex>
#include <sstream>
#include <string>

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

int main()
{
	std::string buff;
	Protocol proto{};
	int port{};
	std::string host, document;
	size_t urlCount = 1;
	while (std::getline(std::cin, buff))
	{
		if (ParseURL(buff, proto, port, host, document))
		{
			PrintUrlInfo(buff, proto, port, host, document);
		}
		else
		{
			std::cout << "#" << urlCount << " - wrong url format" << std::endl;
		}
		urlCount++;
	}
}

void PrintUrlInfo(const std::string& url,
	const Protocol& protocol,
	int port,
	const std::string& host,
	const std::string& document)
{
	std::cout << url << std::endl
			  << "HOST: " << host << std::endl
			  << "PORT: " << port << std::endl
			  << " DOC: " << document << std::endl;
}

std::regex GetRegularExpOfUrl();
std::optional<Protocol> ParseProtocol(const std::string& protocol);
std::optional<int> ParsePortAccordingProtocol(const std::string& match, const Protocol& protocol);
bool AreMatchesCorrect(const std::smatch& matches);

bool ParseURL(std::string const& url, Protocol& protocol, int& port, std::string& host, std::string& document)
{
	bool isOk = true;
	if (auto urlBegIt = std::begin(url), urlEndIt = std::end(url);
		url.length() == 0 || std::count(urlBegIt, urlEndIt, '/') < 2 || std::count(urlBegIt, urlEndIt, ':') < 1)
	{
		return !isOk;
	}

	std::regex regularUrl = GetRegularExpOfUrl();

	std::smatch matches;
	std::regex_match(url, matches, regularUrl);

	if (!AreMatchesCorrect(matches))
	{
		return !isOk;
	}

	port = 80;
	host = "";
	document = "";

	auto oProtocol = ParseProtocol(matches[1].str());
	if (!oProtocol)
	{
		return !isOk;
	}
	protocol = oProtocol.value();

	host = matches[3].str();

	auto oPort = ParsePortAccordingProtocol(matches[6].str(), protocol);
	if (!oPort)
	{
		return !isOk;
	}
	port = oPort.value();

	document = matches[8].str();

	return isOk;
}

bool AreMatchesCorrect(const std::smatch& matches)
{
	bool isOk = true;
	if (std::size(matches) == 0)
	{
		return !isOk;
	}

	if (std::size(matches[2].str()) == 0)
	{
		return !isOk;
	}

	if (auto filePathBeginSymb = matches[7].str(), filePath = matches[8].str();
		std::size(filePathBeginSymb) == 0 && std::size(filePath) != 0)
	{
		return !isOk;
	}

	return isOk;
}

std::regex GetRegularExpOfUrl()
{
	std::string protocolReg = "(\\w+)";
	std::string betweenProtocolAndDomenReg = "(:{1}\\/{2})";
	std::string domenReg = "((\\w+\\.\\w+\\.\\w+|\\w+\\.\\w+))";
	std::string portReg = "(:?)(\\d*)";
	std::string filePathBeginReg = "(\\/?)";
	std::string filePathReg = "([\\w\\/\\.\\?\\=\\&\\#]*)";
	std::string sRegularUrl(
		protocolReg + betweenProtocolAndDomenReg + domenReg + portReg + filePathBeginReg + filePathReg);

	return std::regex(sRegularUrl);
}

bool StringEqualsInsensetive(const std::string& a, const std::string& b);

std::optional<Protocol> ParseProtocol(const std::string& protocol)
{
	const auto HTTP = "HTTP", HTTPS = "HTTPS", FTP = "FTP";

	if (StringEqualsInsensetive(protocol, HTTP))
	{
		return Protocol::HTTP;
	}
	if (StringEqualsInsensetive(protocol, HTTPS))
	{
		return Protocol::HTTPS;
	}
	if (StringEqualsInsensetive(protocol, FTP))
	{
		return Protocol::FTP;
	}
	return std::nullopt;
}

std::optional<int> ParsePortAccordingProtocol(const std::string& match, const Protocol& protocol)
{
	if (std::size(match) == 0)
	{
		switch (protocol)
		{
		case Protocol::HTTP:
			return 80;
		case Protocol::HTTPS:
			return 443;
		case Protocol::FTP:
			return 21;
		}
		return std::nullopt;
	}

	int res;
	std::stringstream ss{};
	ss << match;
	ss >> res;

	if (ss.fail() || res < 1 || res > 65535)
	{
		return std::nullopt;
	}
	return res;
}

bool StringEqualsInsensetive(const std::string& a, const std::string& b)
{
	return std::equal(a.begin(), a.end(),
		b.begin(), b.end(),
		[](char a, char b) {
			return tolower(a) == tolower(b);
		});
}
