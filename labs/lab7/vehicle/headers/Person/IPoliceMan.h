#pragma once

#include "IPerson.h"

class IPoliceMan : public IPerson
{
public:
	~IPoliceMan() = default;

	virtual std::string GetDepartmentName() const = 0;
};
