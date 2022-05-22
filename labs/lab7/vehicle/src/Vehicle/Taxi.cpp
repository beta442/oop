#include "../../headers/Vehicle/Taxi.h"

Taxi::Taxi(MakeOfTheCar carMake, size_t maxCapacity)
	: CarImpl<Person, VehicleImpl<Person, ITaxi>>(maxCapacity, carMake)
{
}
