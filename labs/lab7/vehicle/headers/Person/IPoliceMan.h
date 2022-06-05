#pragma once

#include "IPerson.h"

class IPoliceMan : public IPerson
{
public:
	IPoliceMan(const IPoliceMan&) = delete;
	IPoliceMan(const IPoliceMan&&) noexcept = delete;
	IPoliceMan& operator=(const IPoliceMan&) = delete;
	IPoliceMan& operator=(const IPoliceMan&&) noexcept = delete;

	virtual std::string GetDepartmentName() const = 0;

protected:
	IPoliceMan() = default;
	virtual ~IPoliceMan() = default;
};
