#include "../headers/main_utils.h"

void PrintHelloMsg()
{
	std::cout << PROGRAM_HELLO_MSG;
	PrintMapCommandDescription(commandDescription);
	std::cout << std::endl;
}

void PrintMapCommandDescription(std::map<std::string, std::string> map)
{
	for (auto& [command, description] : map)
	{
		std::cout << "--" << command << ": " << description << std::endl;
	}
}