#include "../headers/main_utils.h"

void PrintHelloMsg()
{
	std::cout << HELLO_MSG << std::endl;
	PrintMapCommandDescription(commandDescription, std::cout);
	std::cout << std::endl;
}

void PrintMapCommandDescription(std::map<std::string, std::string> map, std::ostream& output)
{
	for (auto& [command, description] : map)
	{
		output << "--" << command << ": " << description << std::endl;
	}
}
