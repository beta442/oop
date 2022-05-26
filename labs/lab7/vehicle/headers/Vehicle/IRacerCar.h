#pragma once

#include "../Person/IRacer.h"
#include "ICar.h"

class IRacerCar : public ICar<IRacer>
{
public:
	~IRacerCar() = default;
};
