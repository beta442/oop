#pragma once

#include "../Person/IRacer.h"
#include "ICar.h"

class IRacerCar : public ICar<IRacer>
{
protected:
	IRacerCar() = default;
	~IRacerCar() = default;
};
