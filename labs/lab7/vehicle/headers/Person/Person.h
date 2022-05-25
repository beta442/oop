#pragma once

#include "PersonImpl.hpp"

class Person : public PersonImpl<IPerson>
{
public:
	using Base = PersonImpl<IPerson>;

	static inline const std::string s_type = "Person";

public:
	Person(const std::string& name);
};
