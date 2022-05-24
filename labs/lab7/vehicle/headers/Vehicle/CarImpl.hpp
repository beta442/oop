#pragma once

#include "VehicleImpl.hpp"
#include "ICar.h"

template <typename Passenger, typename Base = VehicleImpl<ICar<Passenger>>>
class CarImpl : public Base
{
public:
	using MakeOfTheCar = typename Base::MakeOfTheCar;
public:
	inline CarImpl(size_t maxPassengerCapacity, const MakeOfTheCar& carMake)
		: Base(maxPassengerCapacity)
		, m_carMake(carMake)
	{
	}

	inline MakeOfTheCar GetMakeOfTheCar() const override
	{
		return m_carMake;
	}

private:
	MakeOfTheCar m_carMake;
};
