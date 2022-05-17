#include "headers/pch.h"

#include "headers/List/List.hpp"

int main()
{
	const std::string cs = "2";
	std::string s = "1";
	List<std::string> list{};
	list.PushBack("3");
	list.PushBack("4");
	list.PushFront(cs);
	list.PushFront(s);

	auto it = list.begin();

	++it;
	++it;

	list.Emplace(it, "999");
	list.Emplace(list.begin(), "a");
	list.Emplace(list.end(), "z");

	//list.Clear();

	for (auto& s : list)
	{
		std::cout << s << std::endl;
	}


	std::cout << std::endl << *it << std::endl;
	auto g = list.Erase(it);
	std::cout << *g << std::endl << std::endl;

	for (auto& s : list)
	{
		std::cout << s << std::endl;
	}

	return 0;
}
