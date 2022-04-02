#include "headers/std_lib.h"
#include "headers/vector.h"

int main()
{
	std::vector<double> vec{};
	if (!CopyStreamOfDoubleIntoVector(std::cin, vec))
	{
		std::cout << "An error occured while processing input" << std::endl;
		return 1;
	}

	if (std::size(vec) == 0)
	{
		std::cout << "Nothing to process" << std::endl;
		return 1;
	}

	std::cout << "Vector was:" << std::endl;
	PrintVectorOfDouble(vec);

	ProcessVectorOfDoubleByTask(vec);
	std::sort(std::begin(vec), std::end(vec));

	std::cout << std::endl << "Vector now:" << std::endl;
	PrintVectorOfDouble(vec);

	return 0;
}
