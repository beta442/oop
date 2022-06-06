#pragma once

#include "IVehicle.h"

#include "../Person/IPerson.h"

class IBus : public IVehicle<IPerson>
{
protected:
	IBus() = default;
	~IBus() = default;
};
