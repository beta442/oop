#include "headers/pch.h"

#include "headers/TaskUtil.hpp"

int main()
{
	std::cout << "Based on a true story:" << std::endl
			  << std::endl;

	std::cout << "=============PART   I==============" << std::endl
			  << std::endl;

	const auto policeManFirst = CreatePerson<PoliceMan>("John Smith", "Northwest Police Station"),
			   policeManSecond = CreatePerson<PoliceMan>("Jim Clark", "Southeastern Police Station");
	auto policeCar = CreateCar<PoliceCar>(PoliceCar::MakeOfTheCar::FORD, 5);

	std::cout << "We see an ordinary patrol car:" << std::endl;

	AddPassengerInVehicleWithEcho(std::cout, policeCar, policeManFirst);
	AddPassengerInVehicleWithEcho(std::cout, policeCar, policeManSecond);
	std::cout << std::endl;

	PrintCarInfo(std::cout, policeCar);
	std::cout << std::endl;

	std::cout << "=============PART  II=============" << std::endl
			  << std::endl;

	std::cout << "The police quarreled:" << std::endl;
	RemovePassengerWithEcho(std::cout, policeCar, policeManSecond);
	std::cout << std::endl;

	const auto taxiDriver = CreatePerson<Person>("Raja Gandhi");
	const auto racer = CreatePerson<Racer>("Michael Schumacher", 20);
	auto taxi = CreateCar<Taxi>(Taxi::MakeOfTheCar::TOYOTA, 2);

	std::cout << "The policeman " << policeManSecond->GetName() << " sees not ordinary taxi: " << std::endl
			  << std::endl;

	AddPassengerInVehicleWithEcho(std::cout, taxi, taxiDriver);
	AddPassengerInVehicleWithEcho(std::cout, taxi, racer);
	std::cout << std::endl;

	PrintCarInfo(std::cout, taxi);
	std::cout << std::endl;

	std::cout << "The policeman demands the taxi driver " << taxiDriver->GetName() << " to leave his car:" << std::endl;
	RemovePassengerWithEcho(std::cout, taxi, taxiDriver);
	std::cout << std::endl;

	AddPassengerInVehicleWithEcho(std::cout, taxi, policeManSecond);
	std::cout << std::endl;

	std::cout << "=============PART III=============" << std::endl
			  << std::endl;

	std::cout << taxiDriver->GetName() << " tries to get back into his car:" << std::endl;
	AddPassengerInVehicleWithEcho(std::cout, taxi, taxiDriver);

	std::cout << "True story's ends..." << std::endl;

	return 0;
}
