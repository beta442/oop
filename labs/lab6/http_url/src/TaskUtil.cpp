#include "../headers/TaskUtil.h"

#include <string>

#include "../headers/HttpUrl/CHttpUrl.h"

void PrintUrlInfoToStream(std::ostream& os, const HttpUrl& url);

void TranslateUrlToInfo(std::istream& is, std::ostream& os)
{
	std::string buffer;
	while (std::getline(std::cin, buffer))
	{
		try
		{
			HttpUrl url{ buffer };
			PrintUrlInfoToStream(os, url);
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << std::endl;
		}
	}
}

void PrintUrlInfoToStream(std::ostream& os, const HttpUrl& url)
{
	const std::string protocol = url.GetProtocol() == HttpUrl::Protocol::HTTP ? "http" : "https";

	os << "Protocol: " << protocol << std::endl
	   << "Domain: " << url.GetDomain() << std::endl
	   << "Port: " << url.GetPort() << std::endl
	   << "Document: " << url.GetDocument() << std::endl;
}
