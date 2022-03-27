#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"

#include "../../../labs/lab3/car/headers/car.h"

SCENARIO("Testing car at created state")
{
	WHEN("Car is created")
	{
		CCar car{};
		THEN("Car's engine is off, car's speed is 0, car's move direction is STAY, car's gear is NEUTRAL")
		{
			REQUIRE(!car.IsTurnedOn());
			REQUIRE(car.GetSpeed() == 0);
			REQUIRE(car.GetDirection() == MoveDirection::STAY);
			REQUIRE(car.GetGear() == Gear::NEUTRAL);
		}
	}

	WHEN("Car is created")
	{
		CCar car{};
		THEN("Car's engine is off -> car's gear, speed, move direction are can't be changed and engine can't be turned on")
		{
			REQUIRE((!car.TurnOffEngine() && !car.IsTurnedOn()));
			REQUIRE((!car.SetGear(5) && car.GetGear() == Gear::NEUTRAL));
			REQUIRE((!car.SetSpeed(100) && car.GetSpeed() == 0));
		}
	}
}

SCENARIO("Testing car in workflow")
{
	WHEN("Car is created, it can be turned on")
	{
		CCar car{};
		car.TurnOnEngine();
		THEN("Car's engine is on and can't be turned on again, speed is 0, move direction is STAY and gear is NEUTRAL")
		{
			REQUIRE((car.IsTurnedOn() && !car.TurnOnEngine()));
			REQUIRE(car.GetDirection() == MoveDirection::STAY);
			REQUIRE(car.GetGear() == Gear::NEUTRAL);
			REQUIRE(car.GetSpeed() == 0);
		}
	}

	WHEN("Car is created and turned on, its speed can't be negative")
	{
		CCar car{};
		car.TurnOnEngine();
		car.SetSpeed(-20);
		THEN("Car's engine is on and can't be turned on again, speed is 0, move direction is STAY and gear is NEUTRAL")
		{
			REQUIRE((car.IsTurnedOn() && !car.TurnOnEngine()));
			REQUIRE(car.GetDirection() == MoveDirection::STAY);
			REQUIRE(car.GetGear() == Gear::NEUTRAL);
			REQUIRE(car.GetSpeed() == 0);
		}
	}

	WHEN("Car is created and turned on, its speed can't be increased because gear is neutral")
	{
		CCar car{};
		car.TurnOnEngine();
		car.SetSpeed(20);
		THEN("Car's engine is on and can't be turned on again, speed is 0, move direction is STAY and gear is NEUTRAL")
		{
			REQUIRE((car.IsTurnedOn() && !car.TurnOnEngine()));
			REQUIRE(car.GetDirection() == MoveDirection::STAY);
			REQUIRE(car.GetGear() == Gear::NEUTRAL);
			REQUIRE(car.GetSpeed() == 0);
		}
	}

	SECTION("Car is created and turned on, REAR or FIRST gear can be choosed")
	{
		WHEN("Its gear is NEUTRAL, its gear can be set FIRST")
		{
			CCar car{};
			car.TurnOnEngine();
			car.SetGear(1);
			THEN("Car's engine is on and can't be turned on again, speed is 0, move direction is STAY and gear can be set FIRST, because speed is 0")
			{
				REQUIRE((car.IsTurnedOn() && !car.TurnOnEngine()));
				REQUIRE(car.GetDirection() == MoveDirection::STAY);
				REQUIRE(car.GetGear() == Gear::FIRST);
				REQUIRE(car.GetSpeed() == 0);
			}
		}

		WHEN("Its gear is NEUTRAL, its gear can be set REAR")
		{
			CCar car{};
			car.TurnOnEngine();
			car.SetGear(-1);
			THEN("Car's engine is on and can't be turned on again, speed is 0, move direction is STAY and gear can be set REAR, because speed is 0")
			{
				REQUIRE((car.IsTurnedOn() && !car.TurnOnEngine()));
				REQUIRE(car.GetDirection() == MoveDirection::STAY);
				REQUIRE(car.GetGear() == Gear::REAR);
				REQUIRE(car.GetSpeed() == 0);
			}
		}

		WHEN("Its gear is NEUTRAL, its gear can't be set FIFTH")
		{
			CCar car{};
			car.TurnOnEngine();
			car.SetGear(5);
			THEN("Car's engine is on and can't be turned on again, speed is 0, move direction is STAY and gear can't be set FIFTH, because speed is 0 -> gear is NEUTRAL")
			{
				REQUIRE((car.IsTurnedOn() && !car.TurnOnEngine()));
				REQUIRE(car.GetDirection() == MoveDirection::STAY);
				REQUIRE(car.GetGear() == Gear::NEUTRAL);
				REQUIRE(car.GetSpeed() == 0);
			}
		}

		WHEN("Car created, its gear can't be changed by weird value not between in -1 and 5")
		{
			CCar car{};
			car.TurnOnEngine();
			car.SetGear(15);
			THEN("Car's engine is on and can't be turned on again, speed is 0, move direction is STAY and gear didn't changed, gear is NEUTRAL")
			{
				REQUIRE((car.IsTurnedOn() && !car.TurnOnEngine()));
				REQUIRE(car.GetDirection() == MoveDirection::STAY);
				REQUIRE(car.GetGear() == Gear::NEUTRAL);
				REQUIRE(car.GetSpeed() == 0);
			}
		}

		WHEN("Car created, its gear can be set NEUTRAL again")
		{
			CCar car{};
			car.TurnOnEngine();
			car.SetGear(0);
			THEN("Car's engine is on and can't be turned on again, speed is 0, move direction is STAY and gear is set NEUTRAL")
			{
				REQUIRE((car.IsTurnedOn() && !car.TurnOnEngine()));
				REQUIRE(car.GetDirection() == MoveDirection::STAY);
				REQUIRE(car.GetGear() == Gear::NEUTRAL);
				REQUIRE(car.GetSpeed() == 0);
			}
		}
	}

	SECTION("Car created, engine turned on, gear is FIRST")
	{
		WHEN("Speed can be set between 0 and 30")
		{
			CCar car{};
			car.TurnOnEngine();
			car.SetGear(1);
			car.SetSpeed(30);
			THEN("Speed is 30, engine is on and can't be turned on again, gear is FIRST, move direction is FORWARD")
			{
				REQUIRE((car.IsTurnedOn() && !car.TurnOnEngine()));
				REQUIRE(car.GetDirection() == MoveDirection::FORWARD);
				REQUIRE(car.GetGear() == Gear::FIRST);
				REQUIRE(car.GetSpeed() == 30);
			}
		}
	}
}
