#include "../../headers/Person/Person.h"

Person::Person(const std::string& name)
	: PersonImpl<IPerson>(name)
{
}