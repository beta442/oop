#pragma once

#include "IPerson.h"

template <typename Base = IPerson>
class PersonImpl : public Base
{
public:
	PersonImpl() = delete;
	PersonImpl(const PersonImpl&) = delete;
	PersonImpl(const PersonImpl&&) noexcept = delete;
	PersonImpl& operator=(const PersonImpl&) = delete;
	PersonImpl& operator=(const PersonImpl&&) noexcept = delete;

	std::string GetName() const override final
	{
		return m_name;
	}

	std::string GetType() const override final
	{
		return m_type;
	}

protected:
	PersonImpl(const std::string& name, const std::string& personType = s_defaultType)
		: m_name(name)
		, m_type(personType)
	{
	}
	~PersonImpl() = default;

private:
	static inline const std::string s_defaultType = "Person";

	std::string m_name;
	std::string m_type;
};
