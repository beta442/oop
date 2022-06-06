#pragma once

#include "VehicleImpl.hpp"
#include "ICar.h"

template <typename Base = VehicleImpl<ICar<IPerson>>>
class CarImpl : public Base
{
public:
	using typename Base::MakeOfTheCar;

public:
	MakeOfTheCar GetMakeOfTheCar() const final
	{
		return m_carMake;
	}

	const std::string& GetCarType() const final
	{
		return m_type;
	}

protected:
	CarImpl(size_t maxPassengerCapacity, const MakeOfTheCar& carMake, std::string carType = s_defaultType)
		: Base(maxPassengerCapacity)
		, m_type(std::move(carType))
		, m_carMake(carMake)
	{
	}
	~CarImpl() = default;

private:
	static inline const std::string s_defaultType = "Car";

	std::string m_type;
	MakeOfTheCar m_carMake;
};
