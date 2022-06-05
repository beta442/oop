#pragma once

#include "../Person/IRacer.h"
#include "ICar.h"

class IRacerCar : public ICar<IRacer>
{
public:
	IRacerCar(const IRacerCar&) = default;
	IRacerCar(const IRacerCar&&) noexcept = delete;
	IRacerCar& operator=(const IRacerCar&) = delete;
	IRacerCar& operator=(const IRacerCar&&) noexcept = delete;

protected:
	IRacerCar() = default;
	~IRacerCar() = default;
};
