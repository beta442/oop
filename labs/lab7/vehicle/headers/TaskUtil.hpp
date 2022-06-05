#pragma once

#include "Person/PoliceMan.h"
#include "Person/Racer.h"
#include "Vehicle/PoliceCar.h"
#include "Vehicle/Taxi.h"

template <typename PassengerType = IPerson, typename VehicleType = IVehicle<PassengerType>>
void PrintPassengersInVehicle(std::ostream& os, const std::shared_ptr<VehicleType>& vehicle)
{
	os << "Passengers:" << std::endl;

	if (vehicle->IsEmpty())
	{
		os << "  No passengers in vehicle" << std::endl;
		return;
	}

	const auto passengerCount = vehicle->GetPassengerCount();
	const PassengerType* p = nullptr;
	std::string passengerType;
	for (size_t i = 0; i < passengerCount; ++i)
	{
		p = &vehicle->GetPassenger(i);
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

template <typename VehicleType = IVehicle<IPerson>>
void PrintVehicleInfo(std::ostream& os, const std::shared_ptr<VehicleType>& vehicle)
{
	os << "Vehcile info:" << std::endl
	   << "--Max amount of passengers: " << vehicle->GetPlaceCount() << std::endl
	   << "--";
	PrintPassengersInVehicle(os, vehicle);
}

template <typename CarType = ICar<IPerson>>
void PrintCarInfo(std::ostream& os, const std::shared_ptr<CarType>& car)
{
	os << "Car info:" << std::endl
	   << "--Type: " << car->GetCarType() << std::endl
	   << "--Make: " << MakeOfTheCarToString(static_cast<const typename ICar<IPerson>::MakeOfTheCar>(car->GetMakeOfTheCar())) << std::endl;
	PrintVehicleInfo(os, car);
}

template <typename PassengerType = IPerson, typename VehicleType = IVehicle<PassengerType>>
void RemovePassengerWithEcho(std::ostream& os, const std::shared_ptr<VehicleType>& vehicle, const std::shared_ptr<PassengerType>& passenger)
{
	if (const auto oPassengerIndex = vehicle->GetIndexOfPassenger(passenger);
		oPassengerIndex.has_value())
	{
		os << passenger->GetName() << " leaving his vehicle..." << std::endl;
		vehicle->RemovePassenger(*oPassengerIndex);
	}
}

template <typename PassengerType = IPerson, typename VehicleType = IVehicle<PassengerType>>
void AddPassengerInVehicleWithEcho(std::ostream& os, const std::shared_ptr<VehicleType>& vehicle, const std::shared_ptr<PassengerType>& person)
{
	try
	{
		vehicle->AddPassenger(person);
		os << person->GetName() << " got into the vehicle" << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
}
