#include "headers/car.h"
#include "headers/main_utils.h"
#include "headers/std_lib.h"
#include "headers/car_controller.h"

int main()
{
	PrintHelloMsg();

	CCar car{};
	CCarController controller(std::cin, std::cout, car);

	while (!std::cin.eof() && !std::cin.fail())
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
