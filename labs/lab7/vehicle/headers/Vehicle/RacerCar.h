#pragma once

#include "CarImpl.hpp"
#include "IRacerCar.h"

class RacerCar : public CarImpl<VehicleImpl<IRacerCar, IRacer>>
{
public:
	using Base = CarImpl<VehicleImpl<IRacerCar, IRacer>>;

	static inline const std::string s_type = "RacerCar";

public:
	explicit RacerCar(MakeOfTheCar carMake, size_t maxPassengerCapacity = s_maxPassengerAmount);

	static inline const int s_maxPassengerAmount = 2;
};
