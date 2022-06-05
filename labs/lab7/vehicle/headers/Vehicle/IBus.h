#pragma once

#include "IVehicle.h"

#include "../Person/IPerson.h"

class IBus : public IVehicle<IPerson>
{
public:
	IBus(const IBus&) = default;
	IBus(const IBus&&) noexcept = delete;
	IBus& operator=(const IBus&) = delete;
	IBus& operator=(const IBus&&) noexcept = delete;

protected:
	IBus() = default;
	~IBus() = default;
};
