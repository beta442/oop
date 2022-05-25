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
	virtual MakeOfTheCar GetMakeOfTheCar() const = 0;
	virtual const std::string& GetCarType() const = 0;
};

template <typename Passenger>
std::string MakeOfTheCarToString(const typename ICar<Passenger>::MakeOfTheCar& make)
{
	if (auto index = static_cast<size_t>(make); make < ICar<Passenger>::MAKES_OF_CAR.size())
	{
		return ICar<Passenger>::MAKES_OF_CAR[index];
	}
	return "";
}
