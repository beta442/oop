#include "../headers/car.h"
#include "../headers/std_lib.h"

CCar::CCar()
{
	m_isEngineOn = false;
	m_direction = MoveDirection::STAY;
	m_gear = Gear::NEUTRAL;
	m_speed = 0;
}

CCar::~CCar()
{
}

bool CCar::IsTurnedOn()
{
	return m_isEngineOn;
}

MoveDirection CCar::GetDirection()
{
	return m_direction;
}

Gear CCar::GetGear()
{
	return m_gear;
}

int CCar::GetSpeed()
{
	return m_speed;
}

bool CCar::TurnOnEngine()
{
	if (!m_isEngineOn)
	{
		m_isEngineOn = true;
		return true;
	}
	return false;
}

bool CCar::TurnOffEngine()
{
	if (m_isEngineOn)
	{
		m_isEngineOn = false;
		return true;
	}
	return false;
}

bool CCar::SetGear(int gear)
{
	if (m_gear == Gear(gear))
	{
		return true;
	}

	if (!m_isEngineOn || gear < -1 || gear > 5)
	{
		return false;
	}

	switch (gear)
	{
	case -1:
		return SetRearGear();
	case 0:
		return SetNeutralGear();
	case 1:
		return SetFirstGear();
	case 2:
		return SetSecondGear();
	case 3:
		return SetThirdGear();
	case 4:
		return SetFourthGear();
	case 5:
		return SetFifthGear();
	}
	return false;
}

bool CCar::SetSpeed(int speed)
{
	if (!m_isEngineOn || speed < 0 || m_gear == Gear::NEUTRAL && speed > m_speed)
	{
		return false;
	}

	if (m_gear == Gear::REAR && speed >= 0 && speed <= 20)
	{
		m_speed = speed;
		m_direction = SwitchMoveDirection(speed);
		return true;
	}
	if (m_gear == Gear::NEUTRAL && m_speed >= speed)
	{
		m_speed = speed;
		m_direction = SwitchMoveDirection(speed);
		return true;
	}
	if (m_gear == Gear::FIRST && speed >= 0 && speed <= 30)
	{
		m_speed = speed;
		m_direction = SwitchMoveDirection(speed);
		return true;
	}
	if (m_gear == Gear::SECOND && speed >= 20 && speed <= 50)
	{
		m_speed = speed;
		return true;
	}
	if (m_gear == Gear::THIRD && speed >= 30 && speed <= 60)
	{
		m_speed = speed;
		return true;
	}
	if (m_gear == Gear::FOURTH && speed >= 40 && speed <= 90)
	{
		m_speed = speed;
		return true;
	}
	if (m_gear == Gear::FIFTH && speed >= 50 && speed <= 150)
	{
		m_speed = speed;
		return true;
	}

	return false;
}

bool CCar::SetRearGear()
{
	if (m_speed == 0 && m_isEngineOn)
	{
		m_gear = Gear::REAR;
		return true;
	}
	return false;
}

bool CCar::SetNeutralGear()
{
	m_gear = Gear::NEUTRAL;

	return true;
}

bool CCar::SetFirstGear()
{
	if (m_isEngineOn && m_speed <= 30 && m_speed >= 0 && (m_direction == MoveDirection::STAY || m_direction == MoveDirection::FORWARD))
	{
		m_gear = Gear::FIRST;
		return true;
	}

	return false;
}

bool CCar::SetSecondGear()
{
	if (m_isEngineOn && m_speed <= 50 && m_speed >= 20 && m_direction == MoveDirection::FORWARD)
	{
		m_gear = Gear::SECOND;
		return true;
	}

	return false;
}

bool CCar::SetThirdGear()
{
	if (m_isEngineOn && m_speed <= 60 && m_speed >= 30 && m_direction == MoveDirection::FORWARD)
	{
		m_gear = Gear::THIRD;
		return true;
	}

	return false;
}

bool CCar::SetFourthGear()
{
	if (m_isEngineOn && m_speed <= 90 && m_speed >= 40 && m_direction == MoveDirection::FORWARD)
	{
		m_gear = Gear::FOURTH;
		return true;
	}

	return false;
}

bool CCar::SetFifthGear()
{
	if (m_isEngineOn && m_speed <= 150 && m_speed >= 50 && m_direction == MoveDirection::FORWARD)
	{
		m_gear = Gear::FIFTH;
		return true;
	}

	return false;
}

MoveDirection CCar::SwitchMoveDirection(int speed)
{
	if (speed && m_gear != Gear::REAR && m_direction != MoveDirection::BACKWARD)
	{
		return MoveDirection::FORWARD;
	}
	if (speed && m_gear == Gear::REAR)
	{
		return MoveDirection::BACKWARD;
	}
	if (speed == 0)
	{
		return MoveDirection::STAY;
	}
	return m_direction;
}
