#pragma once

#include "IPoliceMan.h"
#include "PersonImpl.hpp"

class PoliceMan : public PersonImpl<IPoliceMan>
{
public:
	PoliceMan(const std::string& name, const std::string& departmentName);

	std::string GetDepartmentName() const override;

private:
	std::string m_departmentName;
};
