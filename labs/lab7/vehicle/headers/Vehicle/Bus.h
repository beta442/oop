#pragma once

#include "VehicleImpl.hpp"
#include "IBus.h"
#include "../Person/IPerson.h"

class Bus : public VehicleImpl<IPerson, IBus>
{
public:
	Bus(size_t maxCapacity = s_maxPassengerAmount);

private:
	inline static const size_t s_maxPassengerAmount = 30;
};
