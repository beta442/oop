#include "../../headers/Vehicle/Taxi.h"

Taxi::Taxi(MakeOfTheCar carMake, size_t maxCapacity)
	: Base(maxCapacity, carMake, s_type)
{
}
