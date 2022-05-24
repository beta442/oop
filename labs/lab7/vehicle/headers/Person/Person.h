#pragma once

#include "PersonImpl.hpp"

class Person : public PersonImpl<IPerson>
{
public:
	using Base = PersonImpl<IPerson>;

public:
	Person(const std::string& name);
};
