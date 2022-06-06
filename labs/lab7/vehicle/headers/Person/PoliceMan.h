#pragma once

#include "IPoliceMan.h"
#include "PersonImpl.hpp"

class PoliceMan : public PersonImpl<IPoliceMan>
{
public:
	using Base = PersonImpl<IPoliceMan>;

public:
	PoliceMan(std::string name, std::string departmentName);

	std::string GetDepartmentName() const final;

private:
	static inline const std::string s_type = "PoliceMan";

	std::string m_departmentName;
};
