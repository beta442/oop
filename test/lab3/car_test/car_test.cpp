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
		THEN("Car's engine is off -> car's speed, move direction are can't be changed, engine can't be turned on, gear can be set NEUTRAL, but can't be set by other value")
		{
			REQUIRE((!car.TurnOffEngine() && !car.IsTurnedOn()));
			REQUIRE((car.SetGear(0) && car.GetGear() == Gear::NEUTRAL));
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
		REQUIRE(car.TurnOnEngine());
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
		REQUIRE(car.TurnOnEngine());
		REQUIRE(!car.SetSpeed(-20));
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
		REQUIRE(car.TurnOnEngine());
		REQUIRE(!car.SetSpeed(20));
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
			REQUIRE(car.TurnOnEngine());
			REQUIRE(car.SetGear(1));
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
			REQUIRE(car.TurnOnEngine());
			REQUIRE(car.SetGear(-1));
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
			REQUIRE(car.TurnOnEngine());
			REQUIRE(!car.SetGear(5));
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
			REQUIRE(car.TurnOnEngine());
			REQUIRE(!car.SetGear(15));
			REQUIRE(!car.SetGear(-10));
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
			REQUIRE(car.TurnOnEngine());
			REQUIRE(car.SetGear(0));
			THEN("Car's engine is on and can't be turned on again, speed is 0, move direction is STAY and gear is set NEUTRAL")
			{
				REQUIRE((car.IsTurnedOn() && !car.TurnOnEngine()));
				REQUIRE(car.GetDirection() == MoveDirection::STAY);
				REQUIRE(car.GetGear() == Gear::NEUTRAL);
				REQUIRE(car.GetSpeed() == 0);
			}
		}
	}

	SECTION("Car's gear is FIRST")
	{
		CCar car{};
		car.TurnOnEngine();
		car.SetGear(1);

		SECTION("Testing speed changing")
		{
			WHEN("Speed can be set between 0 and 30")
			{
				REQUIRE(car.SetSpeed(30));
				THEN("Speed is 30, engine is on and can't be turned on again, gear is FIRST, move direction is FORWARD")
				{
					REQUIRE((car.IsTurnedOn() && !car.TurnOnEngine()));
					REQUIRE(car.GetDirection() == MoveDirection::FORWARD);
					REQUIRE(car.GetGear() == Gear::FIRST);
					REQUIRE(car.GetSpeed() == 30);
				}

				REQUIRE(car.SetSpeed(15));
				THEN("Speed is 15, engine is on and can't be turned on again, gear is FIRST, move direction is FORWARD")
				{
					REQUIRE((car.IsTurnedOn() && !car.TurnOnEngine()));
					REQUIRE(car.GetDirection() == MoveDirection::FORWARD);
					REQUIRE(car.GetGear() == Gear::FIRST);
					REQUIRE(car.GetSpeed() == 15);
				}

				REQUIRE(car.SetSpeed(0));
				THEN("Speed is 0, engine is on and can't be turned on again, gear is FIRST, move direction now is STAY")
				{
					REQUIRE((car.IsTurnedOn() && !car.TurnOnEngine()));
					REQUIRE(car.GetDirection() == MoveDirection::STAY);
					REQUIRE(car.GetGear() == Gear::FIRST);
					REQUIRE(car.GetSpeed() == 0);
				}

				const int previousCarSpeed = car.GetSpeed();
				WHEN("Speed can't be set by value from invalid range")
				{
					REQUIRE(!car.SetSpeed(31));
					REQUIRE(!car.SetSpeed(-1));
					THEN("Speed is still 0, engine is on and can't be turned on again, gear is FIRST, move direction is still STAY")
					{
						REQUIRE((car.IsTurnedOn() && !car.TurnOnEngine()));
						REQUIRE(car.GetDirection() == MoveDirection::STAY);
						REQUIRE(car.GetGear() == Gear::FIRST);
						REQUIRE(car.GetSpeed() == previousCarSpeed);
					}
				}
			}
		}

		SECTION("Testing car's gear change")
		{
			WHEN("Car's speed is 0, gear can be set NEUTRAL")
			{
				REQUIRE(car.GetSpeed() == 0);
				REQUIRE(car.SetGear(0));
				THEN("Gear is NEUTRAL")
				{
					REQUIRE(car.GetGear() == Gear::NEUTRAL);
				}
				car.SetGear(1);
			}

			WHEN("Car's speed isn't 0, gear can be set NEUTRAL")
			{
				car.SetSpeed(10);
				REQUIRE(car.GetSpeed() != 0);
				REQUIRE(car.SetGear(0));
				THEN("Gear is NEUTRAL")
				{
					REQUIRE(car.GetGear() == Gear::NEUTRAL);
				}
			}

			WHEN("Car's gear can be set FIRST again")
			{
				REQUIRE(car.SetGear(1));
				THEN("Gear is FIRST")
				{
					REQUIRE(car.GetGear() == Gear::FIRST);
				}
			}

			WHEN("Car's speed is 0, gear can be set REAR")
			{
				car.SetSpeed(0);
				REQUIRE(car.SetGear(-1));
				THEN("Gear is REAR")
				{
					REQUIRE(car.GetGear() == Gear::REAR);
				}
				car.SetGear(1);
			}

			WHEN("Car's speed isn't 0, gear can't be set REAR")
			{
				car.SetSpeed(25);
				REQUIRE(!car.SetGear(-1));
				THEN("Gear is still FIRST")
				{
					REQUIRE(car.GetGear() == Gear::FIRST);
				}
			}

			WHEN("Speed is in FIRST gear interval")
			{
				REQUIRE((car.GetSpeed() >= 0 && car.GetSpeed() <= 30));
				THEN("Gear can't be set FOURTH, FIFTH")
				{
					REQUIRE(!car.SetGear(4));
					REQUIRE(!car.SetGear(5));
					REQUIRE(car.GetGear() == Gear::FIRST);
				}
			}

			WHEN("Car's speed is >= 20, gear can be set SECOND")
			{
				car.SetSpeed(20);
				REQUIRE(car.SetGear(2));
				THEN("Gear is SECOND")
				{
					REQUIRE(car.GetGear() == Gear::SECOND);
				}
			}

			WHEN("Car's speed is 30, gear can be set THIRD")
			{
				car.SetSpeed(30);
				REQUIRE(car.SetGear(3));
				THEN("Gear is THIRD")
				{
					REQUIRE(car.GetGear() == Gear::THIRD);
				}
			}
		}

		SECTION("Testing car's move direction changing")
		{
			WHEN("Car speed is 0")
			{
				car.SetSpeed(0);
				THEN("Car's move direction is STAY")
				{
					REQUIRE(car.GetDirection() == MoveDirection::STAY);
				}
			}

			WHEN("Car's speed was increased from 0")
			{
				car.SetSpeed(10);
				THEN("Car's move direction changed from STAY to FORWARD")
				{
					REQUIRE(car.GetDirection() == MoveDirection::FORWARD);
				}
			}

			WHEN("Car's speed was decreased, but speed still isn't 0")
			{
				car.SetSpeed(5);
				const MoveDirection savedCarMoveDirection = car.GetDirection();
				THEN("Car's move direction still the same")
				{
					REQUIRE(savedCarMoveDirection == car.GetDirection());
				}
			}

			WHEN("Car speed was decreased to 0")
			{
				car.SetSpeed(0);
				THEN("Car's move direction is STAY")
				{
					REQUIRE(car.GetDirection() == MoveDirection::STAY);
				}
			}
		}
	}

	SECTION("Car's gear is SECOND")
	{
		CCar car{};
		car.TurnOnEngine();
		car.SetGear(1);
		car.SetSpeed(20);
		car.SetGear(2);

		SECTION("Testing speed changing")
		{
			WHEN("Speed can be set between 20 and 50")
			{
				REQUIRE(car.SetSpeed(50));
				THEN("Speed is 50, engine is on and can't be turned on again, gear is SECOND, move direction is FORWARD")
				{
					REQUIRE((car.IsTurnedOn() && !car.TurnOnEngine()));
					REQUIRE(car.GetDirection() == MoveDirection::FORWARD);
					REQUIRE(car.GetGear() == Gear::SECOND);
					REQUIRE(car.GetSpeed() == 50);
				}

				REQUIRE(car.SetSpeed(35));
				THEN("Speed is 35, engine is on and can't be turned on again, gear is SECOND, move direction is FORWARD")
				{
					REQUIRE((car.IsTurnedOn() && !car.TurnOnEngine()));
					REQUIRE(car.GetDirection() == MoveDirection::FORWARD);
					REQUIRE(car.GetGear() == Gear::SECOND);
					REQUIRE(car.GetSpeed() == 35);
				}

				REQUIRE(car.SetSpeed(20));
				THEN("Speed is 20, engine is on and can't be turned on again, gear is SECOND, move direction now is FORWARD")
				{
					REQUIRE((car.IsTurnedOn() && !car.TurnOnEngine()));
					REQUIRE(car.GetDirection() == MoveDirection::FORWARD);
					REQUIRE(car.GetGear() == Gear::SECOND);
					REQUIRE(car.GetSpeed() == 20);
				}

				const int previousCarSpeed = car.GetSpeed();
				WHEN("Speed can't be set by value from invalid range")
				{
					REQUIRE(!car.SetSpeed(51));
					REQUIRE(!car.SetSpeed(19));
					THEN("Speed is still 0, engine is on and can't be turned on again, gear is SECOND, move direction is still STAY")
					{
						REQUIRE((car.IsTurnedOn() && !car.TurnOnEngine()));
						REQUIRE(car.GetDirection() == MoveDirection::FORWARD);
						REQUIRE(car.GetGear() == Gear::SECOND);
						REQUIRE(car.GetSpeed() == previousCarSpeed);
					}
				}
			}
		}

		SECTION("Testing car's gear change")
		{
			WHEN("Car's speed is 20, gear can be set NEUTRAL")
			{
				REQUIRE(car.GetSpeed() == 20);
				REQUIRE(car.SetGear(0));
				THEN("Gear is NEUTRAL")
				{
					REQUIRE(car.GetGear() == Gear::NEUTRAL);
				}
				car.SetGear(2);
			}

			WHEN("Car's gear can be set SECOND again")
			{
				REQUIRE(car.SetGear(2));
				THEN("Gear is SECOND")
				{
					REQUIRE(car.GetGear() == Gear::SECOND);
				}
			}

			WHEN("Car's speed isn't 0, gear can't be set REAR")
			{
				REQUIRE(car.GetSpeed() != 0);
				REQUIRE(!car.SetGear(-1));
				THEN("Gear is SECOND")
				{
					REQUIRE(car.GetGear() == Gear::SECOND);
				}
			}

			WHEN("Car's speed is >= 30, gear can be set THRID")
			{
				car.SetSpeed(30);
				REQUIRE(car.SetGear(3));
				THEN("Gear is THIRD")
				{
					REQUIRE(car.GetGear() == Gear::THIRD);
				}
			}

			WHEN("Car's speed is >= 40, gear can be set FOURTH")
			{
				car.SetSpeed(40);
				REQUIRE(car.SetGear(4));
				THEN("Gear is FOURTH")
				{
					REQUIRE(car.GetGear() == Gear::FOURTH);
				}
			}

			WHEN("Car's speed is 50, gear can be set FOURTH")
			{
				car.SetSpeed(50);
				REQUIRE(car.SetGear(5));
				THEN("Gear is FIFTH")
				{
					REQUIRE(car.GetGear() == Gear::FIFTH);
				}
			}

			WHEN("Car's speed is <= 30, gear can be set FIRST")
			{
				car.SetSpeed(30);
				REQUIRE(car.SetGear(1));
				THEN("Gear is FIRST")
				{
					REQUIRE(car.GetGear() == Gear::FIRST);
				}
			}
		}

		SECTION("Testing car's move direction changing")
		{
			WHEN("Car speed is 20")
			{
				car.SetSpeed(20);
				THEN("Car's move direction is FORWARD")
				{
					REQUIRE(car.GetDirection() == MoveDirection::FORWARD);
				}
			}

			WHEN("Car's speed was increased from 20")
			{
				car.SetSpeed(30);
				const MoveDirection savedCarMoveDirection = car.GetDirection();
				REQUIRE(savedCarMoveDirection == MoveDirection::FORWARD);
				THEN("Car's move direction still FORWARD")
				{
					REQUIRE(savedCarMoveDirection == car.GetDirection());
				}
			}

			WHEN("Car's speed was decreased from 30")
			{
				car.SetSpeed(20);
				const MoveDirection savedCarMoveDirection = car.GetDirection();
				REQUIRE(savedCarMoveDirection == MoveDirection::FORWARD);
				THEN("Car's move direction still FORWARD")
				{
					REQUIRE(savedCarMoveDirection == car.GetDirection());
				}
			}
		}
	}

	SECTION("Car's gear is THIRD")
	{
		CCar car{};
		car.TurnOnEngine();
		car.SetGear(1);
		car.SetSpeed(30);
		car.SetGear(3);

		SECTION("Testing speed changing")
		{
			WHEN("Speed can be set between 30 and 60")
			{
				REQUIRE(car.SetSpeed(30));
				THEN("Speed is 30, engine is on and can't be turned on again, gear is THIRD, move direction is FORWARD")
				{
					REQUIRE((car.IsTurnedOn() && !car.TurnOnEngine()));
					REQUIRE(car.GetDirection() == MoveDirection::FORWARD);
					REQUIRE(car.GetGear() == Gear::THIRD);
					REQUIRE(car.GetSpeed() == 30);
				}

				REQUIRE(car.SetSpeed(60));
				THEN("Speed is 60, engine is on and can't be turned on again, gear is THIRD, move direction is FORWARD")
				{
					REQUIRE((car.IsTurnedOn() && !car.TurnOnEngine()));
					REQUIRE(car.GetDirection() == MoveDirection::FORWARD);
					REQUIRE(car.GetGear() == Gear::THIRD);
					REQUIRE(car.GetSpeed() == 60);
				}

				REQUIRE(car.SetSpeed(45));
				THEN("Speed is 45, engine is on and can't be turned on again, gear is THIRD, move direction now is FORWARD")
				{
					REQUIRE((car.IsTurnedOn() && !car.TurnOnEngine()));
					REQUIRE(car.GetDirection() == MoveDirection::FORWARD);
					REQUIRE(car.GetGear() == Gear::THIRD);
					REQUIRE(car.GetSpeed() == 45);
				}

				const int previousCarSpeed = car.GetSpeed();
				WHEN("Speed can't be set by value from invalid range")
				{
					REQUIRE(!car.SetSpeed(61));
					REQUIRE(!car.SetSpeed(29));
					THEN("Speed is still 0, engine is on and can't be turned on again, gear is THIRD, move direction is still STAY")
					{
						REQUIRE((car.IsTurnedOn() && !car.TurnOnEngine()));
						REQUIRE(car.GetDirection() == MoveDirection::FORWARD);
						REQUIRE(car.GetGear() == Gear::THIRD);
						REQUIRE(car.GetSpeed() == previousCarSpeed);
					}
				}
			}
		}

		SECTION("Testing car's gear change")
		{
			WHEN("Car's speed is 30, gear can be set NEUTRAL")
			{
				REQUIRE(car.GetSpeed() == 30);
				REQUIRE(car.SetGear(0));
				THEN("Gear is NEUTRAL")
				{
					REQUIRE(car.GetGear() == Gear::NEUTRAL);
				}
				car.SetGear(3);
			}

			WHEN("Car's gear can be set THIRD again")
			{
				REQUIRE(car.SetGear(3));
				THEN("Gear is THIRD")
				{
					REQUIRE(car.GetGear() == Gear::THIRD);
				}
			}

			WHEN("Car's speed isn't 0, gear can't be set REAR")
			{
				REQUIRE(car.GetSpeed() != 0);
				REQUIRE(!car.SetGear(-1));
				THEN("Gear is THIRD")
				{
					REQUIRE(car.GetGear() == Gear::THIRD);
				}
			}

			WHEN("Car's speed is >= 40, gear can be set FOURTH")
			{
				car.SetSpeed(40);
				REQUIRE(car.SetGear(4));
				THEN("Gear is FOURTH")
				{
					REQUIRE(car.GetGear() == Gear::FOURTH);
				}
			}
			
			WHEN("Car's speed is >= 50, gear can be set FIFTH")
			{
				car.SetSpeed(50);
				REQUIRE(car.SetGear(5));
				THEN("Gear is FIFTH")
				{
					REQUIRE(car.GetGear() == Gear::FIFTH);
				}
			}

			WHEN("Car's speed is <= 50, gear can be set SECOND")
			{
				car.SetSpeed(50);
				REQUIRE(car.SetGear(2));
				THEN("Gear is SECOND")
				{
					REQUIRE(car.GetGear() == Gear::SECOND);
				}
				car.SetGear(3);
			}

			WHEN("Car's speed is 30, gear can be set FIRST")
			{
				car.SetSpeed(30);
				REQUIRE(car.SetGear(1));
				THEN("Gear is FIRST")
				{
					REQUIRE(car.GetGear() == Gear::FIRST);
				}
				car.SetGear(3);
			}
		}

		SECTION("Testing car's move direction changing")
		{
			WHEN("Car speed is 20")
			{
				car.SetSpeed(30);
				THEN("Car's move direction is FORWARD")
				{
					REQUIRE(car.GetDirection() == MoveDirection::FORWARD);
				}
			}

			WHEN("Car's speed was increased from 60")
			{
				car.SetSpeed(60);
				const MoveDirection savedCarMoveDirection = car.GetDirection();
				REQUIRE(savedCarMoveDirection == MoveDirection::FORWARD);
				THEN("Car's move direction still FORWARD")
				{
					REQUIRE(savedCarMoveDirection == car.GetDirection());
				}
			}

			WHEN("Car's speed was decreased from 60")
			{
				car.SetSpeed(30);
				const MoveDirection savedCarMoveDirection = car.GetDirection();
				REQUIRE(savedCarMoveDirection == MoveDirection::FORWARD);
				THEN("Car's move direction still FORWARD")
				{
					REQUIRE(savedCarMoveDirection == car.GetDirection());
				}
			}
		}
	}

	SECTION("Car's gear is FOURTH")
	{
		CCar car{};
		car.TurnOnEngine();
		car.SetGear(1);
		car.SetSpeed(30);
		car.SetGear(3);
		car.SetSpeed(40);
		car.SetGear(4);

		SECTION("Testing speed changing")
		{
			WHEN("Speed can be set between 40 and 90")
			{
				REQUIRE(car.SetSpeed(40));
				THEN("Speed is 40, engine is on and can't be turned on again, gear is FOURTH, move direction is FORWARD")
				{
					REQUIRE((car.IsTurnedOn() && !car.TurnOnEngine()));
					REQUIRE(car.GetDirection() == MoveDirection::FORWARD);
					REQUIRE(car.GetGear() == Gear::FOURTH);
					REQUIRE(car.GetSpeed() == 40);
				}

				REQUIRE(car.SetSpeed(90));
				THEN("Speed is 90, engine is on and can't be turned on again, gear is FOURTH, move direction is FORWARD")
				{
					REQUIRE((car.IsTurnedOn() && !car.TurnOnEngine()));
					REQUIRE(car.GetDirection() == MoveDirection::FORWARD);
					REQUIRE(car.GetGear() == Gear::FOURTH);
					REQUIRE(car.GetSpeed() == 90);
				}

				REQUIRE(car.SetSpeed(65));
				THEN("Speed is 65, engine is on and can't be turned on again, gear is FOURTH, move direction now is FORWARD")
				{
					REQUIRE((car.IsTurnedOn() && !car.TurnOnEngine()));
					REQUIRE(car.GetDirection() == MoveDirection::FORWARD);
					REQUIRE(car.GetGear() == Gear::FOURTH);
					REQUIRE(car.GetSpeed() == 65);
				}

				const int previousCarSpeed = car.GetSpeed();
				WHEN("Speed can't be set by value from invalid range")
				{
					REQUIRE(!car.SetSpeed(91));
					REQUIRE(!car.SetSpeed(39));
					THEN("Speed is still 0, engine is on and can't be turned on again, gear is FOURTH, move direction is still STAY")
					{
						REQUIRE((car.IsTurnedOn() && !car.TurnOnEngine()));
						REQUIRE(car.GetDirection() == MoveDirection::FORWARD);
						REQUIRE(car.GetGear() == Gear::FOURTH);
						REQUIRE(car.GetSpeed() == previousCarSpeed);
					}
				}
			}
		}

		SECTION("Testing car's gear change")
		{
			WHEN("Car's speed is 40, gear can be set NEUTRAL")
			{
				REQUIRE(car.GetSpeed() == 40);
				REQUIRE(car.SetGear(0));
				THEN("Gear is NEUTRAL")
				{
					REQUIRE(car.GetGear() == Gear::NEUTRAL);
				}
				car.SetGear(4);
			}

			WHEN("Car's gear can be set FOURTH again")
			{
				REQUIRE(car.SetGear(4));
				THEN("Gear is FOURTH")
				{
					REQUIRE(car.GetGear() == Gear::FOURTH);
				}
			}

			WHEN("Car's speed isn't 0, gear can't be set REAR")
			{
				REQUIRE(car.GetSpeed() != 0);
				REQUIRE(!car.SetGear(-1));
				THEN("Gear is FOURTH")
				{
					REQUIRE(car.GetGear() == Gear::FOURTH);
				}
			}

			WHEN("Car's speed is >= 50, gear can be set FIFTH")
			{
				car.SetSpeed(50);
				REQUIRE(car.SetGear(5));
				THEN("Gear is FIFTH")
				{
					REQUIRE(car.GetGear() == Gear::FIFTH);
				}
			}

			WHEN("Car's speed is <= 60, gear can be set THIRD")
			{
				car.SetSpeed(50);
				REQUIRE(car.SetGear(3));
				THEN("Gear is THIRD")
				{
					REQUIRE(car.GetGear() == Gear::THIRD);
				}
				car.SetGear(4);
			}

			WHEN("Car's speed is <= 50, gear can be set SECOND")
			{
				car.SetSpeed(50);
				REQUIRE(car.SetGear(2));
				THEN("Gear is SECOND")
				{
					REQUIRE(car.GetGear() == Gear::SECOND);
				}
				car.SetGear(4);
			}

			WHEN("Car's speed is 40, gear can't be set FIRST")
			{
				car.SetSpeed(40);
				REQUIRE(!car.SetGear(1));
				THEN("Gear is FOURTH")
				{
					REQUIRE(car.GetGear() == Gear::FOURTH);
				}
			}
		}

		SECTION("Testing car's move direction changing")
		{
			WHEN("Car speed is 40")
			{
				car.SetSpeed(40);
				THEN("Car's move direction is FORWARD")
				{
					REQUIRE(car.GetDirection() == MoveDirection::FORWARD);
				}
			}

			WHEN("Car's speed was increased from 40")
			{
				car.SetSpeed(90);
				const MoveDirection savedCarMoveDirection = car.GetDirection();
				REQUIRE(savedCarMoveDirection == MoveDirection::FORWARD);
				THEN("Car's move direction still FORWARD")
				{
					REQUIRE(savedCarMoveDirection == car.GetDirection());
				}
			}

			WHEN("Car's speed was decreased from 90")
			{
				car.SetSpeed(90);
				const MoveDirection savedCarMoveDirection = car.GetDirection();
				REQUIRE(savedCarMoveDirection == MoveDirection::FORWARD);
				THEN("Car's move direction still FORWARD")
				{
					REQUIRE(savedCarMoveDirection == car.GetDirection());
				}
			}
		}
	}

	SECTION("Car's gear is FIFTH")
	{
		CCar car{};
		car.TurnOnEngine();
		car.SetGear(1);
		car.SetSpeed(30);
		car.SetGear(3);
		car.SetSpeed(40);
		car.SetGear(4);
		car.SetSpeed(50);
		car.SetGear(5);

		SECTION("Testing speed changing")
		{
			WHEN("Speed can be set between 50 and 150")
			{
				REQUIRE(car.SetSpeed(50));
				THEN("Speed is 50, engine is on and can't be turned on again, gear is FIFTH, move direction is FORWARD")
				{
					REQUIRE((car.IsTurnedOn() && !car.TurnOnEngine()));
					REQUIRE(car.GetDirection() == MoveDirection::FORWARD);
					REQUIRE(car.GetGear() == Gear::FIFTH);
					REQUIRE(car.GetSpeed() == 50);
				}

				REQUIRE(car.SetSpeed(150));
				THEN("Speed is 150, engine is on and can't be turned on again, gear is FIFTH, move direction is FORWARD")
				{
					REQUIRE((car.IsTurnedOn() && !car.TurnOnEngine()));
					REQUIRE(car.GetDirection() == MoveDirection::FORWARD);
					REQUIRE(car.GetGear() == Gear::FIFTH);
					REQUIRE(car.GetSpeed() == 150);
				}

				REQUIRE(car.SetSpeed(100));
				THEN("Speed is 100, engine is on and can't be turned on again, gear is FIFTH, move direction now is FORWARD")
				{
					REQUIRE((car.IsTurnedOn() && !car.TurnOnEngine()));
					REQUIRE(car.GetDirection() == MoveDirection::FORWARD);
					REQUIRE(car.GetGear() == Gear::FIFTH);
					REQUIRE(car.GetSpeed() == 100);
				}

				const int previousCarSpeed = car.GetSpeed();
				WHEN("Speed can't be set by value from invalid range")
				{
					REQUIRE(!car.SetSpeed(151));
					REQUIRE(!car.SetSpeed(49));
					THEN("Speed is still 0, engine is on and can't be turned on again, gear is FIFTH, move direction is still STAY")
					{
						REQUIRE((car.IsTurnedOn() && !car.TurnOnEngine()));
						REQUIRE(car.GetDirection() == MoveDirection::FORWARD);
						REQUIRE(car.GetGear() == Gear::FIFTH);
						REQUIRE(car.GetSpeed() == previousCarSpeed);
					}
				}
			}
		}

		SECTION("Testing car's gear change")
		{
			WHEN("Car's speed is 50, gear can be set NEUTRAL")
			{
				REQUIRE(car.GetSpeed() == 50);
				REQUIRE(car.SetGear(0));
				THEN("Gear is NEUTRAL")
				{
					REQUIRE(car.GetGear() == Gear::NEUTRAL);
				}
				car.SetGear(5);
			}

			WHEN("Car's gear can be set FIFTH again")
			{
				REQUIRE(car.SetGear(5));
				THEN("Gear is FIFTH")
				{
					REQUIRE(car.GetGear() == Gear::FIFTH);
				}
			}

			WHEN("Car's speed isn't 0, gear can't be set REAR")
			{
				REQUIRE(car.GetSpeed() != 0);
				REQUIRE(!car.SetGear(-1));
				THEN("Gear is FIFTH")
				{
					REQUIRE(car.GetGear() == Gear::FIFTH);
				}
			}

			WHEN("Car's speed is <= 90, gear can be set FOURTH")
			{
				car.SetSpeed(90);
				REQUIRE(car.SetGear(4));
				THEN("Gear is FOURTH")
				{
					REQUIRE(car.GetGear() == Gear::FOURTH);
				}
				car.SetGear(5);
			}

			WHEN("Car's speed is <= 60, gear can be set THIRD")
			{
				car.SetSpeed(60);
				REQUIRE(car.SetGear(3));
				THEN("Gear is THIRD")
				{
					REQUIRE(car.GetGear() == Gear::THIRD);
				}
				car.SetGear(5);
			}

			WHEN("Car's speed is 50, gear can be set SECOND")
			{
				car.SetSpeed(50);
				REQUIRE(car.SetGear(2));
				THEN("Gear is SECOND")
				{
					REQUIRE(car.GetGear() == Gear::SECOND);
				}
				car.SetGear(5);
			}

			WHEN("Car's speed is 50, gear can't be set FIRST")
			{
				car.SetSpeed(50);
				REQUIRE(!car.SetGear(1));
				THEN("Gear is SECOND")
				{
					REQUIRE(car.GetGear() == Gear::FIFTH);
				}
				car.SetGear(5);
			}
		}

		SECTION("Testing car's move direction changing")
		{
			WHEN("Car speed is 50")
			{
				car.SetSpeed(50);
				THEN("Car's move direction is FORWARD")
				{
					REQUIRE(car.GetDirection() == MoveDirection::FORWARD);
				}
			}

			WHEN("Car's speed was increased from 50")
			{
				car.SetSpeed(150);
				const MoveDirection savedCarMoveDirection = car.GetDirection();
				REQUIRE(savedCarMoveDirection == MoveDirection::FORWARD);
				THEN("Car's move direction still FORWARD")
				{
					REQUIRE(savedCarMoveDirection == car.GetDirection());
				}
			}

			WHEN("Car's speed was decreased from 150")
			{
				car.SetSpeed(100);
				const MoveDirection savedCarMoveDirection = car.GetDirection();
				REQUIRE(savedCarMoveDirection == MoveDirection::FORWARD);
				THEN("Car's move direction still FORWARD")
				{
					REQUIRE(savedCarMoveDirection == car.GetDirection());
				}
			}
		}
	}

	SECTION("Car's gear is NEUTRAL, car has speed and forward move direction")
	{
		CCar car{};
		car.TurnOnEngine();
		car.SetGear(1);
		car.SetSpeed(30);
		car.SetGear(3);
		car.SetSpeed(50);
		car.SetGear(5);
		car.SetSpeed(150);
		car.SetGear(0);

		SECTION("Testing speed changing")
		{
			WHEN("Speed can be decreased only")
			{
				REQUIRE(car.SetSpeed(10));
				THEN("Speed is 10, engine is on and can't be turned on again, gear is NEUTRAL, move direction is FORWARD")
				{
					REQUIRE((car.IsTurnedOn() && !car.TurnOnEngine()));
					REQUIRE(car.GetDirection() == MoveDirection::FORWARD);
					REQUIRE(car.GetGear() == Gear::NEUTRAL);
					REQUIRE(car.GetSpeed() == 10);
				}

				REQUIRE(car.SetSpeed(0));
				THEN("Speed is 0, engine is on and can't be turned on again, gear is NEUTRAL, move direction is STAY")
				{
					REQUIRE((car.IsTurnedOn() && !car.TurnOnEngine()));
					REQUIRE(car.GetDirection() == MoveDirection::STAY);
					REQUIRE(car.GetGear() == Gear::NEUTRAL);
					REQUIRE(car.GetSpeed() == 0);
				}

				REQUIRE(!car.SetSpeed(20));
				THEN("Speed is can't be increased, engine is on and can't be turned on again, gear is NEUTRAL, move direction now is STAY")
				{
					REQUIRE((car.IsTurnedOn() && !car.TurnOnEngine()));
					REQUIRE(car.GetDirection() == MoveDirection::STAY);
					REQUIRE(car.GetGear() == Gear::NEUTRAL);
					REQUIRE(car.GetSpeed() == 0);
				}
			}
		}

		SECTION("Testing car's gear change on speed decreasing from 150")
		{
			WHEN("Car's speed is 150, gear can be set NEUTRAL again")
			{
				REQUIRE(car.GetSpeed() == 150);
				REQUIRE(car.SetGear(0));
				THEN("Gear is NEUTRAL")
				{
					REQUIRE(car.GetGear() == Gear::NEUTRAL);
				}
			}

			WHEN("Car's speed is 150, gear can be set FIFTH and back to NEUTRAL")
			{
				REQUIRE(car.GetSpeed() == 150);
				REQUIRE(car.SetGear(5));
				THEN("Gear is FIFTH")
				{
					REQUIRE(car.GetGear() == Gear::FIFTH);
				}
				REQUIRE(car.SetGear(0));
				THEN("Gear is NEUTRAL")
				{
					REQUIRE(car.GetGear() == Gear::NEUTRAL);
				}
			}

			WHEN("Car's speed is decreased to 90, gear can be set FOURTH and back to NEUTRAL")
			{
				REQUIRE(car.SetSpeed(90));
				REQUIRE(car.SetGear(4));
				THEN("Gear is FOURTH")
				{
					REQUIRE(car.GetGear() == Gear::FOURTH);
				}
				REQUIRE(car.SetGear(0));
				THEN("Gear is NEUTRAL")
				{
					REQUIRE(car.GetGear() == Gear::NEUTRAL);
				}
			}

			WHEN("Car's speed is decreased to 60, gear can be set THIRD and back to NEUTRAL")
			{
				REQUIRE(car.SetSpeed(60));
				REQUIRE(car.SetGear(3));
				THEN("Gear is THIRD")
				{
					REQUIRE(car.GetGear() == Gear::THIRD);
				}
				REQUIRE(car.SetGear(0));
				THEN("Gear is NEUTRAL")
				{
					REQUIRE(car.GetGear() == Gear::NEUTRAL);
				}
			}

			WHEN("Car's speed is decreased to 50, gear can be set SECOND and back to NEUTRAL")
			{
				REQUIRE(car.SetSpeed(50));
				REQUIRE(car.SetGear(2));
				THEN("Gear is SECOND")
				{
					REQUIRE(car.GetGear() == Gear::SECOND);
				}
				REQUIRE(car.SetGear(0));
				THEN("Gear is NEUTRAL")
				{
					REQUIRE(car.GetGear() == Gear::NEUTRAL);
				}
			}

			WHEN("Car's speed is decreased to 30, gear can be set FIRST and back to NEUTRAL")
			{
				REQUIRE(car.SetSpeed(30));
				REQUIRE(car.SetGear(1));
				THEN("Gear is FIRST")
				{
					REQUIRE(car.GetGear() == Gear::FIRST);
				}
				REQUIRE(car.SetGear(0));
				THEN("Gear is NEUTRAL")
				{
					REQUIRE(car.GetGear() == Gear::NEUTRAL);
				}
			}

			WHEN("Car's speed is 0, gear can be set REAR")
			{
				car.SetSpeed(0);
				REQUIRE(car.SetGear(-1));
				THEN("Gear is REAR")
				{
					REQUIRE(car.GetGear() == Gear::REAR);
				}
				car.SetGear(1);
			}
		}

		SECTION("Testing car's move direction changing")
		{
			WHEN("Car speed is 150")
			{
				THEN("Car's move direction is FORWARD")
				{
					REQUIRE(car.GetDirection() == MoveDirection::FORWARD);
				}
			}

			WHEN("Car's speed was increased from 0")
			{
				car.SetSpeed(0);
				THEN("Car's move direction changed from STAY to FORWARD")
				{
					REQUIRE(car.GetDirection() == MoveDirection::STAY);
				}
			}
		}
	}

	SECTION("Testing REAR gear and move direction")
	{
		CCar car{};
		car.TurnOnEngine();
		car.SetGear(1);
		car.SetSpeed(20);

		GIVEN("Car's gear is FIRST, car moves FORWARD, car's speed is 20")
		{
			REQUIRE(car.GetDirection() == MoveDirection::FORWARD);
			REQUIRE(car.GetGear() == Gear::FIRST);
			REQUIRE(car.GetSpeed() == 20);
		}

		WHEN("Car's decreasing speed to 0")
		{
			REQUIRE(car.SetSpeed(0));
			THEN("Gear can be set REAR, move direction changing FORWARD->STAYS")
			{
				REQUIRE(car.GetDirection() == MoveDirection::STAY);
				REQUIRE(car.SetGear(-1));
			}

			car.SetGear(-1);
			THEN("Car's speed can be set only between 0 and 20")
			{
				REQUIRE(car.SetSpeed(20));
				REQUIRE(!car.SetSpeed(21));
			}

			car.SetSpeed(20);
			THEN("Move direction changed to BACKWARD")
			{
				REQUIRE(car.GetDirection() == MoveDirection::BACKWARD);
			}

			THEN("Car's speed can be set 0, and it's move direction will be STAY")
			{
				REQUIRE(car.SetSpeed(0));
				REQUIRE(car.GetDirection() == MoveDirection::STAY);
			}

			car.SetSpeed(0);
			THEN("Car's gear can be set FIRST, speed can be set 20, move direction will be FORWARD")
			{
				REQUIRE(car.SetGear(1));
				REQUIRE(car.SetSpeed(20));
				REQUIRE(car.GetDirection() == MoveDirection::FORWARD);
			}
		}
	}
}
