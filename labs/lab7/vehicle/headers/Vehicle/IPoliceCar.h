#pragma once

#include "ICar.h"
#include "../Person/IPoliceMan.h"

class IPoliceCar : public ICar<IPoliceMan>
{
public:
	~IPoliceCar() = default;
};
