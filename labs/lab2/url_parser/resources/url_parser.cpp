#include "../headers/std_lib.h"

#include "../headers/url_parser.h"
#include "../headers/url_parser_utils.h"

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

constexpr size_t PROTOCOL_PARSED_INDEX = 1;
constexpr size_t BETWEEN_PROTOCOL_AND_DOMEN_PARSED_INDEX = 2;
constexpr size_t HOST_PARSED_INDEX = 3;
constexpr size_t PORT_PARSED_INDEX = 6;
constexpr size_t FILE_PATH_BEGIN_SYMBOL_PARSED_INDEX = 7;
constexpr size_t DOCUMENT_PARSED_INDEX = 8;

bool ParseURL(std::string const& url, Protocol& protocol, int& port, std::string& host, std::string& document)
{
	bool isOk = true;

	std::regex regularUrl = GetRegExOfUrl();

	std::smatch matches;
	if (!std::regex_match(url, matches, regularUrl))
	{
		return !isOk;
	}

	if (!AreMatchesCorrect(matches))
	{
		return !isOk;
	}

	port = 80;
	host = "";
	document = "";

	auto oProtocol = ParseProtocol(matches[PROTOCOL_PARSED_INDEX].str());
	if (!oProtocol)
	{
		return !isOk;
	}
	protocol = oProtocol.value();

	host = matches[HOST_PARSED_INDEX].str();

	auto oPort = ParsePortAccordingProtocol(matches[PORT_PARSED_INDEX].str(), protocol);
	if (!oPort)
	{
		return !isOk;
	}
	port = oPort.value();

	document = matches[DOCUMENT_PARSED_INDEX].str();

	return isOk;
}

bool AreMatchesCorrect(const std::smatch& matches)
{
	bool isOk = true;
	if (std::size(matches) == 0)
	{
		return !isOk;
	}

	if (std::size(matches[BETWEEN_PROTOCOL_AND_DOMEN_PARSED_INDEX].str()) == 0)
	{
		return !isOk;
	}

	if (auto filePathBeginSymb = matches[FILE_PATH_BEGIN_SYMBOL_PARSED_INDEX].str(), filePath = matches[DOCUMENT_PARSED_INDEX].str();
		std::size(filePathBeginSymb) == 0 && std::size(filePath) != 0)
	{
		return !isOk;
	}

	return isOk;
}

std::regex GetRegExOfUrl()
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

	if (ss.fail() || res < 0 || res > 65535)
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