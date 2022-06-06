#pragma once

#include "CarImpl.hpp"
#include "IPoliceCar.h"

class PoliceCar : public CarImpl<VehicleImpl<IPoliceCar, IPoliceMan>>
{
public:
	using Base = CarImpl<VehicleImpl<IPoliceCar, IPoliceMan>>;

public:
	explicit PoliceCar(MakeOfTheCar carMake, size_t maxPassengerCapacity = s_maxPassengerAmount);

	static inline const std::string s_type = "PoliceCar";
	static inline const int s_maxPassengerAmount = 5;
};
