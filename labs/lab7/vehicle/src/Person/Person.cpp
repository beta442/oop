#include "../../headers/Person/Person.h"

Person::Person(std::string name)
	: Base(std::move(name), s_type)
{
}
