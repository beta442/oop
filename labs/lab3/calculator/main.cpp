#include "headers/std_lib.h"

#include "headers/main_utils.h"
#include "headers/calculator/calculator.h"
#include "headers/calculator_controller.h"

int main()
{
	PrintHelloMsg();

	Calculator calculator{};
	CalculatorController controller(std::cin, std::cout, calculator);


	while (!std::cin.eof() && !std::cin.fail() && controller.IsFinishedWork())
	{
		std::cout << "> ";
		if (!controller.HandleCommand())
		{
			std::cout << "Unknown command!" << std::endl;
		}
	}
	std::cout << "Exiting program" << std::endl;

	return 0;
}
