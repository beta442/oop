#include "headers/std_lib.h"

#include "headers/CCalculator_controller.h"

int main()
{
	Calculator calculator{};
	CalculatorController controller(std::cin, std::cout, calculator, true);

	controller.StartWorkflow();

	std::cout << "Exiting program" << std::endl;
	return 0;
}
