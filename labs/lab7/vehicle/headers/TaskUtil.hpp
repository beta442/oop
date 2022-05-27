#pragma once

#include "Person/PoliceMan.h"
#include "Person/Racer.h"
#include "Vehicle/PoliceCar.h"
#include "Vehicle/Taxi.h"

template <typename ToPersonType, typename PersonType = ToPersonType, typename... Args>
std::shared_ptr<ToPersonType> CreatePerson(const Args&... args)
{
	return std::static_pointer_cast<ToPersonType, PersonType>(std::make_shared<PersonType>(args...));
}

template <typename CarType, typename... Args>
decltype(auto) CreateCar(const Args&... args)
{
	return CarType(args...);
}

template <typename PassengerType>
void PrintPassengersInVehicle(std::ostream& os, const IVehicle<PassengerType>& vehicle)
{
	os << "Passengers:" << std::endl;

	if (vehicle.IsEmpty())
	{
		os << "  No passengers in vehicle" << std::endl;
		return;
	}

	const auto passengerCount = vehicle.GetPassengerCount();
	const PassengerType* p = nullptr;
	std::string passengerType;
	for (size_t i = 0; i < passengerCount; ++i)
	{
		p = &vehicle.GetPassenger(i);
		passengerType = p->GetType();
		os << "  " << passengerType << ". " << p->GetName();
		if (auto policeMan = dynamic_cast<const IPoliceMan*>(p);
			policeMan != nullptr)
		{
			os << " works at " << policeMan->GetDepartmentName();
		}
		if (auto racer = dynamic_cast<const IRacer*>(p);
			racer != nullptr)
		{
			os << " has " << racer->GetAwardsCount() << " awards";
		}
		os << std::endl;
	}
}

template <typename PassengerType>
void PrintVehicleInfo(std::ostream& os, const IVehicle<PassengerType>& vehicle)
{
	os << "Vehcile info:" << std::endl
	   << "--Max amount of passengers: " << vehicle.GetPlaceCount() << std::endl
	   << "--";
	PrintPassengersInVehicle(os, vehicle);
}

template <typename PassengerType>
void PrintCarInfo(std::ostream& os, const ICar<PassengerType>& car)
{
	os << "Car info:" << std::endl
	   << "--Type: " << car.GetCarType() << std::endl
	   << "--Make: " << MakeOfTheCarToString<PassengerType>(car.GetMakeOfTheCar()) << std::endl;
	PrintVehicleInfo(os, car);
}

template <typename PassengerType, typename PassengerPtrType>
void RemovePassengerWithEcho(std::ostream& os, IVehicle<PassengerType>& vehicle, PassengerPtrType passenger)
{
	if (const auto oPassengerIndex = vehicle.GetIndexOfPassenger(passenger);
		oPassengerIndex.has_value())
	{
		os << passenger->GetName() << " leaving his vehicle..." << std::endl;
		vehicle.RemovePassenger(*oPassengerIndex);
	}
}

template <typename PassengerType, typename PersonType>
void AddPassengerInVehicleWithEcho(std::ostream& os, IVehicle<PassengerType>& vehicle, const PersonType& person)
{
	try
	{
		vehicle.AddPassenger(person);
		os << person->GetName() << " got into the vehicle" << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
}
