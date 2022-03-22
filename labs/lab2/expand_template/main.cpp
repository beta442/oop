#include <cassert>
#include <iostream>
#include <vector>

#include "expand_template.h"

int main()
{
	/*{
		std::string const tpl = "Hello, %USER_NAME%. Today is {WEEK_DAY}.";
		std::map<std::string, std::string> params;
		params["%USER_NAME%"] = "Ivan Petrov";
		params["{WEEK_DAY}"] = "Friday";
		assert(ExpandTemplate(tpl, params) == "Hello, Ivan Petrov. Today is Friday.");
	}

	{
		std::string const tpl = "Hello, %USER_NAME%. Today is {WEEK_DAY}.";
		std::map<std::string, std::string> params;
		params["%USER_NAME%"] = "Super %USER_NAME% {WEEK_DAY}";
		params["{WEEK_DAY}"] = "Friday. {WEEK_DAY}";
		assert(ExpandTemplate(tpl, params) == "Hello, Super %USER_NAME% {WEEK_DAY}. Today is Friday. {WEEK_DAY}.");
	}

	{
		std::string const tpl = "-AABBCCCCCABC+";
		std::map<std::string, std::string> params;
		params["A"] = "[a]";
		params["AA"] = "[aa]";
		params["B"] = "[b]";
		params["BB"] = "[bb]";
		params["C"] = "[c]";
		params["CC"] = "[cc]";
		assert(ExpandTemplate(tpl, params) == "-[aa][bb][cc][cc][c][a][b][c]+");
	}*/


	//PrintBohrTrie(bohrTreeRoot);
	/*for (size_t i = 0; i < bohrTreeRoot.nextVrtx.size(); i++)
	{
		if (bohrTreeRoot.nextVrtx[i] == nullptr)
		{
			std::cout << "i:" << i << " - 0" << std::endl;
		}
		else
		{
			std::cout << "i:" << i << " - 1" << std::endl;
		}
	}
	std::cout << "HELLO" << std::endl;
	BohrVrtx next = (*bohrTreeRoot.nextVrtx[97]);
	std::cout << next.nextVrtx.size() << std::endl;
	for (size_t i = 0; i < next.nextVrtx.size(); i++)
	{
		if (next.nextVrtx[i] == nullptr)
		{
			std::cout << "i:" << i << " - 0" << std::endl;
		}
		else
		{
			std::cout << "i:" << i << " - 1" << std::endl;
		}
	}*/

	BohrVrtx bohrTrieRoot = InitBohrTrie();
	AddStringIntoBohrTrie(bohrTrieRoot, "aaa");
	AddStringIntoBohrTrie(bohrTrieRoot, "aabaa");
	AddStringIntoBohrTrie(bohrTrieRoot, "aba");
	AddStringIntoBohrTrie(bohrTrieRoot, "bab");
	AddStringIntoBohrTrie(bohrTrieRoot, "bbab");
	std::vector<char> temp;
	PrintBohrTrie(bohrTrieRoot, temp);
	std::cout << CountWordsInBohrTrie(bohrTrieRoot) << std::endl;
	std::cout << IsStringInBohrTrie(bohrTrieRoot, "bbbb") << std::endl << std::endl;
	StitchBohrTrieWithSuffixLinks(bohrTrieRoot);

	//for (size_t i = 0; i < bohrTrieRoot.nextVrtx.size(); i++)
	//{
	//	if (bohrTrieRoot.nextVrtx[i] == nullptr)
	//	{
	//		std::cout << "i:" << i << " - 0" << std::endl;
	//	}
	//	else
	//	{
	//		std::cout << "i:" << i << " - 1" << std::endl;
	//	}
	//}

	return 0;
}
