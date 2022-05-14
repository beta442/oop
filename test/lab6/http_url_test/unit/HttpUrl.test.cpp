#include "../pch.h"

#include "../../../../labs/lab6/http_url/headers/HttpUrl/CHttpUrl.h"

TEST_CASE("HttpUrl constructed with string. Url is not correct")
{
	WHEN("Url is empty")
	{
		REQUIRE_THROWS_AS(HttpUrl(""), UrlParsingError);
	}
	WHEN("Protocol spelled incorrectly")
	{
		REQUIRE_THROWS_AS(HttpUrl("htasdtp://www.mysite.com/docs/document1.html?page=30&lang=en#title"), UrlParsingError);
	}
	WHEN("Missed ':' after protocol")
	{
		REQUIRE_THROWS_AS(HttpUrl("http//www.mysite.com/docs/document1.html?page=30&lang=en#title"), UrlParsingError);
	}
	WHEN("Missed '/' after protocol")
	{
		REQUIRE_THROWS_AS(HttpUrl("http:/www.mysite.com/docs/document1.html?page=30&lang=en#title"), UrlParsingError);
	}
	WHEN("Missed all '/' after protocol")
	{
		REQUIRE_THROWS_AS(HttpUrl("http:www.mysite.com/docs/document1.html?page=30&lang=en#title"), UrlParsingError);
	}
	WHEN("Missed '/' after domain")
	{
		REQUIRE_THROWS_AS(HttpUrl("http://www.mysite.comdocsdocument1.html?page=30&lang=en#title"), UrlParsingError);
	}
	WHEN("Missed '.' in domain")
	{
		REQUIRE_THROWS_AS(HttpUrl("http://wwwmysitecom/docs/document1.html?page=30&lang=en#title"), UrlParsingError);
	}
	WHEN("Too much '.' in domain #1")
	{
		REQUIRE_THROWS_AS(HttpUrl("http://www..mysite.com/doc/sdocument1.html?page=30&lang=en#title"), UrlParsingError);
	}
	WHEN("Too much '.' in domain #2")
	{
		REQUIRE_THROWS_AS(HttpUrl("http://www.mysite..com/doc/sdocument1.html?page=30&lang=en#title"), UrlParsingError);
	}
	WHEN("Too much '.' in domain #3")
	{
		REQUIRE_THROWS_AS(HttpUrl("http://www..mysite..com/doc/sdocument1.html?page=30&lang=en#title"), UrlParsingError);
	}
	WHEN("Protocol typed twice")
	{
		REQUIRE_THROWS_AS(HttpUrl("http::http://www.mysite.com/doc/sdocument1.html?page=30&lang=en#title"), UrlParsingError);
	}
	WHEN("Missed port, but ':' after domain exists")
	{
		REQUIRE_THROWS_AS(HttpUrl("http://www.mysite.com:/doc/sdocument1.html?page=30&lang=en#title"), UrlParsingError);
	}
	WHEN("Wrong sequence #1")
	{
		REQUIRE_THROWS_AS(HttpUrl("sadasd.asdsad.asdasd//:sadasd.asdsad.asdasd"), UrlParsingError);
	}
	WHEN("Wrong sequence #2")
	{
		REQUIRE_THROWS_AS(HttpUrl("document1.html?page=30&lang=en#title/docs/www.mysite.com//:http"), UrlParsingError);
	}
	WHEN("Wrong sequence #3")
	{
		REQUIRE_THROWS_AS(HttpUrl("document1.html?page=30&lang=en#title//docs//www.mysite.com///:http"), UrlParsingError);
	}

	SECTION("Port is not valid")
	{
		WHEN("Port is too big")
		{
			REQUIRE_THROWS_AS(HttpUrl("https://vk.com:432121/im?sel=1"), UrlParsingError);
		}
		
		REQUIRE_THROWS_AS(HttpUrl("https://vk.com:A3212/im?sel=1"), UrlParsingError);
		REQUIRE_THROWS_AS(HttpUrl("https://vk.com:4321a/im?sel=1"), UrlParsingError);
		REQUIRE_THROWS_AS(HttpUrl("https://vk.com:432a11/im?sel=1"), UrlParsingError);
		REQUIRE_THROWS_AS(HttpUrl("https://vk.com:a/im?sel=1"), UrlParsingError);
	}
}

TEST_CASE("HttpUrl constructed with string. Url is correct. GetProtocol() test")
{
	using Protocol = HttpUrl::Protocol;
	const auto http = Protocol::HTTP;
	const auto https = Protocol::HTTPS;

	WHEN("Protocol is http")
	{
		REQUIRE(HttpUrl("http://vk.com/im?sel=1").GetProtocol() == http);
	}
	WHEN("Protocol is https")
	{
		REQUIRE(HttpUrl("https://vk.com/im?sel=1").GetProtocol() == https);
	}
	WHEN("Protocol typed in upper case")
	{
		REQUIRE(HttpUrl("HtTp://vk.com/im?sel=1").GetProtocol() == http);
		REQUIRE(HttpUrl("hTtPS://vk.com/im?sel=1").GetProtocol() == https);
	}
}

TEST_CASE("HttpUrl constructed with string. Url is correct. GetDomain() test")
{
	WHEN("Domain contains one '.'")
	{
		REQUIRE(HttpUrl("http://vk.com/im?sel=1").GetDomain() == "vk.com");
	}
	WHEN("Domain contains two '.'")
	{
		REQUIRE(HttpUrl("http://www.vk.com/im?sel=1").GetDomain() == "www.vk.com");
	}
}

TEST_CASE("HttpUrl constructed with string. Url is correct. GetPort() test")
{
	WHEN("Port wasn't provided")
	{
		REQUIRE(HttpUrl("http://vk.com/im?sel=1").GetPort() == 80);
		REQUIRE(HttpUrl("https://vk.com/im?sel=1").GetPort() == 443);
	}

	WHEN("Port was provided")
	{
		REQUIRE(HttpUrl("http://vk.com:1234/im?sel=1").GetPort() == 1234);
		REQUIRE(HttpUrl("https://vk.com:4321/im?sel=1").GetPort() == 4321);
	}
}
