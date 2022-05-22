#pragma once

#include "IPerson.h"
#include "PersonImpl.hpp"

class Person : PersonImpl<IPerson>
{
public:
	Person(const std::string& name);
};
