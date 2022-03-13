#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"

#include "html_decode.h"

SCENARIO("Correct workflow of html_decode function that decodes html sequences in given string and returns result")
{
	WHEN("Given string is empty")
	{
		const std::string emptyString;
		REQUIRE(std::size(emptyString) == 0);

		const std::string res = HtmlDecode(emptyString);

		THEN("No things happend to given string and result is empty")
		{
			REQUIRE(std::size(res) == 0);
			REQUIRE(res == emptyString);
		}
	}

	WHEN("String doesn't contain any html encoded symbols")
	{
		const std::string noHtml = "Some regular string in workflow that obviously hasn't any html content";

		const std::string res = HtmlDecode(noHtml);

		THEN("No things happend to given string and result has same size")
		{
			REQUIRE(res == noHtml);
		}
	}

	WHEN("String has html coded symbols in different places")
	{
		const std::string htmlString = "Cat &lt;says&gt; &quot;Meow&quot;. M&amp;M&apos;s";
		const std::string requiredRes = "Cat <says> \"Meow\". M&M's";

		const std::string res = HtmlDecode(htmlString);

		THEN("All symbols decoded correctly")
		{
			REQUIRE(res == requiredRes);
		}
	}

	WHEN("String contains only html coded symbols")
	{
		const std::string htmlString = "&lt;&gt;&quot;&apos;&amp; &lt;&gt;&quot;&apos;&amp; &lt;&gt;&quot;&apos;&amp; &lt;&gt;&quot;&apos;&amp;";
		const std::string requiredRes = "<>\"'& <>\"'& <>\"'& <>\"'&";

		const std::string res = HtmlDecode(htmlString);

		THEN("All symbols decoded correctly")
		{
			REQUIRE(res == requiredRes);
		}
	}
}
