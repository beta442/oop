#pragma once

#include "ICar.h"
#include "../Person/IPoliceMan.h"

class IPoliceCar : public ICar<IPoliceMan>
{
protected:
	IPoliceCar() = default;
	~IPoliceCar() = default;
};
