#pragma once

#include "IPerson.h"

template <typename Base = IPerson>
class PersonImpl : public Base
{
public:
	PersonImpl(const std::string& name, const std::string& personType = s_defaultType)
		: m_name(name)
		, m_type(personType)
	{
	}

	std::string GetName() const override
	{
		return m_name;
	}

	std::string GetType() const override
	{
		return m_type;
	}

private:
	static inline const std::string s_defaultType = "Person";

	std::string m_name;
	std::string m_type;
};
