#pragma once

#include "IPerson.h"

template <typename Base = IPerson>
class PersonImpl : public Base
{
public:
	std::string GetName() const final
	{
		return m_name;
	}

	std::string GetType() const final
	{
		return m_type;
	}

protected:
	explicit PersonImpl(std::string name, std::string personType = s_defaultType)
		: m_name(std::move(name))
		, m_type(std::move(personType))
	{
	}
	~PersonImpl() = default;

private:
	static inline const std::string s_defaultType = "Person";

	std::string m_name;
	//todo: наследники не должны хранить это поле, лучше переопределить GetType в наследниках
	std::string m_type;
};
