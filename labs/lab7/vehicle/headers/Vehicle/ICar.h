#pragma once

#include "IVehicle.h"

template <typename Passenger>
class ICar : public IVehicle<Passenger>
{
public:
	enum MakeOfTheCar
	{
		BMW = 0,
		MITSUBISHI,
		FORD,
		MERCEDES,
		TOYOTA,
		KIA,
		FERRARI,
		PORSCHE,
		LEXUS,
		NISSAN,
		INIFINITI,
	};

	inline static const std::vector<std::string> MAKES_OF_CAR = {
		"BMW",
		"MITSUBISHI",
		"FORD",
		"MERCEDES",
		"TOYOTA",
		"KIA",
		"FERRARI",
		"PORSCHE",
		"LEXUS",
		"NISSAN",
		"INIFINITI",
	};

public:
	ICar(const ICar&) = default;
	ICar(const ICar&&) noexcept = delete;
	ICar& operator=(const ICar&) = delete;
	ICar& operator=(const ICar&&) noexcept = delete;

	virtual MakeOfTheCar GetMakeOfTheCar() const = 0;
	virtual const std::string& GetCarType() const = 0;

protected:
	ICar() = default;
	~ICar() = default;
};

template <typename CarType = ICar<IPerson>>
std::string MakeOfTheCarToString(const typename CarType::MakeOfTheCar& make)
{
	if (auto index = static_cast<size_t>(make); make < CarType::MAKES_OF_CAR.size())
	{
		return CarType::MAKES_OF_CAR[index];
	}
	return "";
}
