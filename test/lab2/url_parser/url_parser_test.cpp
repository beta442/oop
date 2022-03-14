#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"

#include "url_parser.h"

SCENARIO("Giving wrong urlParserFunc's param")
{
	Protocol protocol = Protocol::FTP;
	int port = 90;
	std::string host = "132";
	std::string document = "987";
	WHEN("String is empty")
	{
		std::string emptyString = "";
		REQUIRE(ParseURL(emptyString, protocol, port, host, document) == false);

		THEN("String is still empty, none of func's params changed")
		{
			REQUIRE(std::size(emptyString) == 0);
			REQUIRE(protocol == Protocol::FTP);
			REQUIRE(port == 90);
			REQUIRE(host == "132");
			REQUIRE(document == "987");
		}
	}

	WHEN("String is absolutely not URL")
	{
		std::string obviousNotUrl = "sadasd.asdsad.asdasd//:sadasd.asdsad.asdasd";
		REQUIRE(ParseURL(obviousNotUrl, protocol, port, host, document) == false);

		THEN("String is still the same, none of func's params changed")
		{
			REQUIRE(obviousNotUrl == "sadasd.asdsad.asdasd//:sadasd.asdsad.asdasd");
			REQUIRE(protocol == Protocol::FTP);
			REQUIRE(port == 90);
			REQUIRE(host == "132");
			REQUIRE(document == "987");
		}
	}

	WHEN("String looks similar to URL, but it is not URL at all (Protocol spelled incorrectly)")
	{
		std::string similarToUrl = "htasdtp://www.mysite.com/docs/document1.html?page=30&lang=en#title";
		REQUIRE(ParseURL(similarToUrl, protocol, port, host, document) == false);

		THEN("String is still the same, none of func's params changed")
		{
			REQUIRE(similarToUrl == "htasdtp://www.mysite.com/docs/document1.html?page=30&lang=en#title");
			REQUIRE(protocol == Protocol::FTP);
			REQUIRE(port == 90);
			REQUIRE(host == "132");
			REQUIRE(document == "987");
		}
	}

	WHEN("String looks similar to URL, but it is not URL at all (Missed : between Protocol and host name)")
	{
		std::string similarToUrl = "http//www.mysite.com/docs/document1.html?page=30&lang=en#title";
		REQUIRE(ParseURL(similarToUrl, protocol, port, host, document) == false);

		THEN("String is still the same, none of func's params changed")
		{
			REQUIRE(similarToUrl == "http//www.mysite.com/docs/document1.html?page=30&lang=en#title");
			REQUIRE(protocol == Protocol::FTP);
			REQUIRE(port == 90);
			REQUIRE(host == "132");
			REQUIRE(document == "987");
		}
	}

	WHEN("String looks similar to URL, but it is not URL at all (Missed one / between Protocol and host name)")
	{
		std::string similarToUrl = "http:/www.mysite.com/docs/document1.html?page=30&lang=en#title";
		REQUIRE(ParseURL(similarToUrl, protocol, port, host, document) == false);

		THEN("String is still the same, none of func's params changed")
		{
			REQUIRE(similarToUrl == "http:/www.mysite.com/docs/document1.html?page=30&lang=en#title");
			REQUIRE(protocol == Protocol::FTP);
			REQUIRE(port == 90);
			REQUIRE(host == "132");
			REQUIRE(document == "987");
		}
	}

	WHEN("String looks similar to URL, but it is not URL at all (Missed all / between Protocol and host name)")
	{
		std::string similarToUrl = "http:www.mysite.com/docs/document1.html?page=30&lang=en#title";
		REQUIRE(ParseURL(similarToUrl, protocol, port, host, document) == false);

		THEN("String is still the same, none of func's params changed")
		{
			REQUIRE(similarToUrl == "http:www.mysite.com/docs/document1.html?page=30&lang=en#title");
			REQUIRE(protocol == Protocol::FTP);
			REQUIRE(port == 90);
			REQUIRE(host == "132");
			REQUIRE(document == "987");
		}
	}

	WHEN("String looks similar to URL, but it is not URL at all (Too much / #1)")
	{
		std::string similarToUrl = "http:///www.mysite.com/docs/document1.html?page=30&lang=en#title";
		REQUIRE(ParseURL(similarToUrl, protocol, port, host, document) == false);

		THEN("String is still the same, none of func's params changed")
		{
			REQUIRE(similarToUrl == "http:///www.mysite.com/docs/document1.html?page=30&lang=en#title");
			REQUIRE(protocol == Protocol::FTP);
			REQUIRE(port == 90);
			REQUIRE(host == "132");
			REQUIRE(document == "987");
		}
	}

	WHEN("String looks similar to URL, but it is not URL at all (Missed / between host name and filePath)")
	{
		std::string similarToUrl = "http://www.mysite.comdocsdocument1.html?page=30&lang=en#title";
		REQUIRE(ParseURL(similarToUrl, protocol, port, host, document) == false);

		THEN("String is still the same, none of func's params changed")
		{
			REQUIRE(similarToUrl == "http://www.mysite.comdocsdocument1.html?page=30&lang=en#title");
			REQUIRE(protocol == Protocol::FTP);
			REQUIRE(port == 90);
			REQUIRE(host == "132");
			REQUIRE(document == "987");
		}
	}

	WHEN("String looks similar to URL, but it is not URL at all (Missed dots in host name)")
	{
		std::string similarToUrl = "http://wwwmysitecom/docs/document1.html?page=30&lang=en#title";
		REQUIRE(ParseURL(similarToUrl, protocol, port, host, document) == false);

		THEN("String is still the same, none of func's params changed")
		{
			REQUIRE(similarToUrl == "http://wwwmysitecom/docs/document1.html?page=30&lang=en#title");
			REQUIRE(protocol == Protocol::FTP);
			REQUIRE(port == 90);
			REQUIRE(host == "132");
			REQUIRE(document == "987");
		}
	}

	WHEN("String looks similar to URL, but it is not URL at all (Too much dots in host name #1)")
	{
		std::string similarToUrl = "http://www..mysite.com/doc/sdocument1.html?page=30&lang=en#title";
		REQUIRE(ParseURL(similarToUrl, protocol, port, host, document) == false);

		THEN("String is still the same, none of func's params changed")
		{
			REQUIRE(similarToUrl == "http://www..mysite.com/doc/sdocument1.html?page=30&lang=en#title");
			REQUIRE(protocol == Protocol::FTP);
			REQUIRE(port == 90);
			REQUIRE(host == "132");
			REQUIRE(document == "987");
		}
	}

	WHEN("String looks similar to URL, but it is not URL at all (Too much dots in host name #2)")
	{
		std::string similarToUrl = "http://www.mysite..com/doc/sdocument1.html?page=30&lang=en#title";
		REQUIRE(ParseURL(similarToUrl, protocol, port, host, document) == false);

		THEN("String is still the same, none of func's params changed")
		{
			REQUIRE(similarToUrl == "http://www.mysite..com/doc/sdocument1.html?page=30&lang=en#title");
			REQUIRE(protocol == Protocol::FTP);
			REQUIRE(port == 90);
			REQUIRE(host == "132");
			REQUIRE(document == "987");
		}
	}

	WHEN("String looks similar to URL, but it is not URL at all (Too much dots in host name #3)")
	{
		std::string similarToUrl = "http://www..mysite..com/doc/sdocument1.html?page=30&lang=en#title";
		REQUIRE(ParseURL(similarToUrl, protocol, port, host, document) == false);

		THEN("String is still the same, none of func's params changed")
		{
			REQUIRE(similarToUrl == "http://www..mysite..com/doc/sdocument1.html?page=30&lang=en#title");
			REQUIRE(protocol == Protocol::FTP);
			REQUIRE(port == 90);
			REQUIRE(host == "132");
			REQUIRE(document == "987");
		}
	}

	WHEN("String looks similar to URL, but it is not URL at all (Protocol is close to be correct)")
	{
		std::string similarToUrl = "http::http://www.mysite.com/doc/sdocument1.html?page=30&lang=en#title";
		REQUIRE(ParseURL(similarToUrl, protocol, port, host, document) == false);

		THEN("String is still the same, none of func's params changed")
		{
			REQUIRE(similarToUrl == "http::http://www.mysite.com/doc/sdocument1.html?page=30&lang=en#title");
			REQUIRE(protocol == Protocol::FTP);
			REQUIRE(port == 90);
			REQUIRE(host == "132");
			REQUIRE(document == "987");
		}
	}

	WHEN("String looks similar to URL, but it is not URL at all (Protocol is close to be correct)")
	{
		std::string similarToUrl = "http::http://www.mysite.com/doc/sdocument1.html?page=30&lang=en#title";
		REQUIRE(ParseURL(similarToUrl, protocol, port, host, document) == false);

		THEN("String is still the same, none of func's params changed")
		{
			REQUIRE(similarToUrl == "http::http://www.mysite.com/doc/sdocument1.html?page=30&lang=en#title");
			REQUIRE(protocol == Protocol::FTP);
			REQUIRE(port == 90);
			REQUIRE(host == "132");
			REQUIRE(document == "987");
		}
	}

	WHEN("String looks similar to URL, but it is not URL at all (Reverse spelled correct URL #1)")
	{
		std::string similarToUrl = "document1.html?page=30&lang=en#title/docs/www.mysite.com//:http";
		REQUIRE(ParseURL(similarToUrl, protocol, port, host, document) == false);

		THEN("String is still the same, none of func's params changed")
		{
			REQUIRE(similarToUrl == "document1.html?page=30&lang=en#title/docs/www.mysite.com//:http");
			REQUIRE(protocol == Protocol::FTP);
			REQUIRE(port == 90);
			REQUIRE(host == "132");
			REQUIRE(document == "987");
		}
	}

	WHEN("String looks similar to URL, but it is not URL at all (Reverse spelled correct URL #2)")
	{
		std::string similarToUrl = "document1.html?page=30&lang=en#title//docs//www.mysite.com///:http";
		REQUIRE(ParseURL(similarToUrl, protocol, port, host, document) == false);

		THEN("String is still the same, none of func's params changed")
		{
			REQUIRE(similarToUrl == "document1.html?page=30&lang=en#title//docs//www.mysite.com///:http");
			REQUIRE(protocol == Protocol::FTP);
			REQUIRE(port == 90);
			REQUIRE(host == "132");
			REQUIRE(document == "987");
		}
	}
}

SCENARIO("Giving correct urlParserFunc's param")
{
	Protocol protocol = Protocol::FTP;
	int port = 90;
	std::string host = "132";
	std::string document = "987";

	WHEN("Given Fullcomposite URL")
	{
		std::string url = "http://www.mysite.com:3304/doc/sdocument1.html?page=30&lang=en#title";
		REQUIRE(ParseURL(url, protocol, port, host, document) == true);

		THEN("String is still the same, func's params changed to the corresponding values")
		{
			REQUIRE(url == "http://www.mysite.com:3304/doc/sdocument1.html?page=30&lang=en#title");
			REQUIRE(protocol == Protocol::HTTP);
			REQUIRE(port == 3304);
			REQUIRE(host == "www.mysite.com");
			REQUIRE(document == "doc/sdocument1.html?page=30&lang=en#title");
		}
	}

	WHEN("Given http URL without port")
	{
		std::string url = "http://www.mysite.com/doc/sdocument1.html?page=30&lang=en#title";
		REQUIRE(ParseURL(url, protocol, port, host, document) == true);

		THEN("String is still the same, func's params changed to the corresponding values")
		{
			REQUIRE(url == "http://www.mysite.com/doc/sdocument1.html?page=30&lang=en#title");
			REQUIRE(protocol == Protocol::HTTP);
			REQUIRE(port == 80);
			REQUIRE(host == "www.mysite.com");
			REQUIRE(document == "doc/sdocument1.html?page=30&lang=en#title");
		}
	}

	WHEN("Given FTP URL without port")
	{
		std::string url = "FtP://www.mysite.com/doc/sdocument1.html?page=30&lang=en#title";
		REQUIRE(ParseURL(url, protocol, port, host, document) == true);

		THEN("String is still the same, func's params changed to the corresponding values")
		{
			REQUIRE(url == "FtP://www.mysite.com/doc/sdocument1.html?page=30&lang=en#title");
			REQUIRE(protocol == Protocol::FTP);
			REQUIRE(port == 21);
			REQUIRE(host == "www.mysite.com");
			REQUIRE(document == "doc/sdocument1.html?page=30&lang=en#title");
		}
	}

	WHEN("Given HTTPS URL without port")
	{
		std::string url = "httpS://www.mysite.com/doc/sdocument1.html?page=30&lang=en#title";
		REQUIRE(ParseURL(url, protocol, port, host, document) == true);

		THEN("String is still the same, func's params changed to the corresponding values")
		{
			REQUIRE(url == "httpS://www.mysite.com/doc/sdocument1.html?page=30&lang=en#title");
			REQUIRE(protocol == Protocol::HTTPS);
			REQUIRE(port == 443);
			REQUIRE(host == "www.mysite.com");
			REQUIRE(document == "doc/sdocument1.html?page=30&lang=en#title");
		}
	}

	WHEN("Given URL without www in hostname")
	{
		std::string url = "fTp://www.mysite/doc";
		REQUIRE(ParseURL(url, protocol, port, host, document) == true);

		THEN("String is still the same, func's params changed to the corresponding values")
		{
			REQUIRE(url == "fTp://www.mysite/doc");
			REQUIRE(protocol == Protocol::FTP);
			REQUIRE(port == 21);
			REQUIRE(host == "www.mysite");
			REQUIRE(document == "doc");
		}
	}

	WHEN("Given URL without www in hostname and without document path")
	{
		std::string url = "http://asd.some";
		REQUIRE(ParseURL(url, protocol, port, host, document) == true);

		THEN("String is still the same, func's params changed to the corresponding values")
		{
			REQUIRE(url == "http://asd.some");
			REQUIRE(protocol == Protocol::HTTP);
			REQUIRE(port == 80);
			REQUIRE(host == "asd.some");
			REQUIRE(document == "");
		}
	}

	WHEN("String is URL with too much / in file path")
	{
		std::string url = "http://www.mysite.com//docs////document1.html?page=30&lang=en#title";
		REQUIRE(ParseURL(url, protocol, port, host, document) == true);

		THEN("String is still the same, func's params changed to the corresponding values")
		{
			REQUIRE(url == "http://www.mysite.com//docs////document1.html?page=30&lang=en#title");
			REQUIRE(protocol == Protocol::HTTP);
			REQUIRE(port == 80);
			REQUIRE(host == "www.mysite.com");
			REQUIRE(document == "/docs////document1.html?page=30&lang=en#title");
		}
	}

	WHEN("String is URL with / at end")
	{
		std::string url = "ftp://asd.someasd123/";
		REQUIRE(ParseURL(url, protocol, port, host, document) == true);

		THEN("String is still the same, func's params changed to the corresponding values")
		{
			REQUIRE(url == "ftp://asd.someasd123/");
			REQUIRE(protocol == Protocol::FTP);
			REQUIRE(port == 21);
			REQUIRE(host == "asd.someasd123");
			REQUIRE(document == "");
		}
	}

	WHEN("String is URL with many / at end")
	{
		std::string url = "ftp://asd.someasd123////";
		REQUIRE(ParseURL(url, protocol, port, host, document) == true);

		THEN("String is still the same, func's params changed to the corresponding values")
		{
			REQUIRE(url == "ftp://asd.someasd123////");
			REQUIRE(protocol == Protocol::FTP);
			REQUIRE(port == 21);
			REQUIRE(host == "asd.someasd123");
			REQUIRE(document == "///");
		}
	}
}
