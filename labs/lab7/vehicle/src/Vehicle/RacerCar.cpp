#include "../../headers/Vehicle/RacerCar.h"

RacerCar::RacerCar(MakeOfTheCar carMake, size_t maxPassengerCapacity)
	: Base(maxPassengerCapacity, carMake, s_type)
{
}
