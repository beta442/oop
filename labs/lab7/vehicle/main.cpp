#include "headers/pch.h"

#include "headers/Person/PoliceMan.h"
#include "headers/Person/Racer.h"
#include "headers/Vehicle/PoliceCar.h"
#include "headers/Vehicle/Taxi.h"

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

void PrintPoliceManInfo(std::ostream& os, const std::shared_ptr<PoliceMan>& policeMan)
{
	os << policeMan->GetName() << " from the " << policeMan->GetDepartmentName() << " ";
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
