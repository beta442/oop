#pragma once

#include "PersonImpl.hpp"

class Person : public PersonImpl<IPerson>
{
public:
	using Base = PersonImpl<IPerson>;

public:
	Person(std::string name);

private:
	static inline const std::string s_type = "Person";
};
