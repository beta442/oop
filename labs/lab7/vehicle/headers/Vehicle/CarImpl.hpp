#pragma once

#include "VehicleImpl.hpp"
#include "ICar.h"

template <typename Base = VehicleImpl<ICar<IPerson>>>
class CarImpl : public Base
{
public:
	using typename Base::MakeOfTheCar;

public:
	inline CarImpl(size_t maxPassengerCapacity, const MakeOfTheCar& carMake, const std::string& carType = s_defaultType)
		: Base(maxPassengerCapacity)
		, m_type(carType)
		, m_carMake(carMake)
	{
	}

	inline MakeOfTheCar GetMakeOfTheCar() const override
	{
		return m_carMake;
	}

	inline const std::string& GetCarType() const override
	{
		return m_type;
	}

private:
	static inline const std::string s_defaultType = "Car";

	std::string m_type;
	MakeOfTheCar m_carMake;
};
