#include "../../headers/Person/PoliceMan.h"

PoliceMan::PoliceMan(std::string name, std::string departmentName)
	: Base(std::move(name), s_type)
	, m_departmentName(std::move(departmentName))
{
}

std::string PoliceMan::GetDepartmentName() const
{
	return m_departmentName;
}
