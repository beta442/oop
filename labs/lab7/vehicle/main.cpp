#include "headers/pch.h"

#include "headers/Person/Person.h"
#include "headers/Vehicle/Taxi.h"

int main()
{
	Person pers{ "John Doe" };
	Taxi t{ Taxi::MakeOfTheCar::BMW };

	return 0;
}
