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
	if (!m_isEngineOn || gear < -1 || gear > 5)
	{
		return false;
	}

	if (gear == -1 && m_speed == 0 ||
		gear == 0 ||
		gear == 1 && (m_speed == 0 && m_gear == Gear::NEUTRAL))
	{
		m_gear = Gear(gear);
		return true;
	}
	return false;
}

bool CCar::SetSpeed(int speed)
{
	if (!m_isEngineOn || speed < 0 || m_gear == Gear::NEUTRAL && speed > m_speed)
	{
		return false;
	}

	if ()
	{
		m_speed = speed;
		return true;
	}
	return false;
}
