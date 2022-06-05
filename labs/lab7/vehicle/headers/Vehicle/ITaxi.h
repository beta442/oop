#pragma once

#include "ICar.h"
#include "../Person/Person.h"

class ITaxi : public ICar<IPerson>
{
public:
	ITaxi(const ITaxi&) = default;
	ITaxi(const ITaxi&&) noexcept = delete;
	ITaxi& operator=(const ITaxi&) = delete;
	ITaxi& operator=(const ITaxi&&) noexcept = delete;

protected:
	ITaxi() = default;
	~ITaxi() = default;
};
