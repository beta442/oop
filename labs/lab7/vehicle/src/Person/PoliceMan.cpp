#include "../../headers/Person/PoliceMan.h"

PoliceMan::PoliceMan(const std::string& name, const std::string& departmentName)
	: Base(name)
	, m_departmentName(departmentName)
{
}

std::string PoliceMan::GetDepartmentName() const
{
	return m_departmentName;
}
