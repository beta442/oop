#pragma once

#include "VehicleImpl.hpp"

template <typename Passenger, typename Base = VehicleImpl<Passenger>>
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
