#pragma once

#include "ICar.h"
#include "../Person/Person.h"

class ITaxi : public ICar<IPerson>
{
protected:
	~ITaxi() = default;
};
