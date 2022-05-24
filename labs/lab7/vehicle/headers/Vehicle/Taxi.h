#pragma once

#include "CarImpl.hpp"
#include "ITaxi.h"

class Taxi : public CarImpl<IPerson, VehicleImpl<ITaxi, IPerson>>
{
public:
	using Base = CarImpl<IPerson, VehicleImpl<ITaxi, IPerson>>;

public:
	Taxi(MakeOfTheCar carMake, size_t maxCapacity = s_maxPassengerAmount);

	inline static const int s_maxPassengerAmount = 5;
};
