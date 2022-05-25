#include "../../headers/Vehicle/PoliceCar.h"

#include <list>

PoliceCar::PoliceCar(MakeOfTheCar carMake, size_t maxPassengerCapacity)
	: Base(maxPassengerCapacity, carMake, s_type)
{
}
