#include "headers/std_lib.h"
#include "headers/url_parser.h"

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
