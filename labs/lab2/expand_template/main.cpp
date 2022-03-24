#include "headers/expand_template.h"

int main()
{
	{
		std::string const tpl = "Hello, %USER_NAME%. Today is {WEEK_DAY}.";
		std::map<std::string, std::string> params;
		params["%USER_NAME%"] = "Ivan Petrov";
		params["{WEEK_DAY}"] = "Friday";
		assert(ExpandTemplate(tpl, params) == "Hello, Ivan Petrov. Today is Friday.");
		std::cout << (ExpandTemplate(tpl, params) == "Hello, Ivan Petrov. Today is Friday.") << std::endl;
	}

	std::cout << std::endl;

	{
		std::string const tpl = "Hello, %USER_NAME%. Today is {WEEK_DAY}.";
		std::map<std::string, std::string> params;
		params["%USER_NAME%"] = "Super %USER_NAME% {WEEK_DAY}";
		params["{WEEK_DAY}"] = "Friday. {WEEK_DAY}";
		assert(ExpandTemplate(tpl, params) == "Hello, Super %USER_NAME% {WEEK_DAY}. Today is Friday. {WEEK_DAY}.");
		std::cout << (ExpandTemplate(tpl, params) == "Hello, Super %USER_NAME% {WEEK_DAY}. Today is Friday. {WEEK_DAY}.") << std::endl;
	}

	std::cout << std::endl;

	{
		std::string const tpl = "-AABBCCCCCABC+";
		std::map<std::string, std::string> params;
		params["A"] = "[a]";
		params["AA"] = "[aa]";
		params["B"] = "[b]";
		params["BB"] = "[bb]";
		params["C"] = "[c]";
		params["CCC"] = "[ccc]";
		params["CCAB"] = "[ccab]";
		params["CA"] = "[ca]";
		assert(ExpandTemplate(tpl, params) == "-[aa][bb][ccc][ccab][c]+");
		std::cout << (ExpandTemplate(tpl, params) == "-[aa][bb][ccc][ccab][c]+") << std::endl;
	}

	return 0;
}
