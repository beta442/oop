#pragma once

#include "VehicleImpl.hpp"
#include "ICar.h"

template <typename Base = VehicleImpl<ICar<IPerson>>>
class CarImpl : public Base
{
public:
	using typename Base::MakeOfTheCar;

public:
	CarImpl() = delete;
	CarImpl(const CarImpl&) = delete;
	CarImpl(const CarImpl&&) noexcept = delete;
	CarImpl& operator=(const CarImpl&) = delete;
	CarImpl& operator=(const CarImpl&&) noexcept = delete;

	inline MakeOfTheCar GetMakeOfTheCar() const override final
	{
		return m_carMake;
	}

	inline const std::string& GetCarType() const override final
	{
		return m_type;
	}

protected:
	CarImpl(size_t maxPassengerCapacity, const MakeOfTheCar& carMake, const std::string& carType = s_defaultType)
		: Base(maxPassengerCapacity)
		, m_type(carType)
		, m_carMake(carMake)
	{
	}
	~CarImpl() = default;

private:
	static inline const std::string s_defaultType = "Car";

	std::string m_type;
	MakeOfTheCar m_carMake;
};
