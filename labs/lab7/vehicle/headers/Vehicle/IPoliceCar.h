#pragma once

#include "ICar.h"
#include "../Person/IPoliceMan.h"

class IPoliceCar : public ICar<IPoliceMan>
{
public:
	IPoliceCar(const IPoliceCar&) = default;
	IPoliceCar(const IPoliceCar&&) noexcept = delete;
	IPoliceCar& operator=(const IPoliceCar&) = delete;
	IPoliceCar& operator=(const IPoliceCar&&) noexcept = delete;

protected:
	IPoliceCar() = default;
	~IPoliceCar() = default;
};
