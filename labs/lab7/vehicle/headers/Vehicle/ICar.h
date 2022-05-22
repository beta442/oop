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

public:
	virtual MakeOfTheCar GetMakeOfTheCar() const = 0;
};
