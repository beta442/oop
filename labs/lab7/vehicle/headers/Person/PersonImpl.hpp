#pragma once

#include "IPerson.h"

template <typename Base = IPerson>
class PersonImpl : public Base
{
public:
	inline PersonImpl(const std::string& name)
		: m_name(name)
	{
	}

	std::string GetName() const override
	{
		return m_name;
	}

private:
	std::string m_name;
};
