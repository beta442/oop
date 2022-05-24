#pragma once

#include "VehicleImpl.hpp"
#include "IBus.h"
#include "../Person/IPerson.h"

class Bus : public VehicleImpl<IBus, IPerson>
{
public:
	using Base = VehicleImpl<IBus, IPerson>;

public:
	Bus(size_t maxCapacity = s_maxPassengerAmount);

private:
	inline static const size_t s_maxPassengerAmount = 30;
};
