#include "../headers/car_controller.h"
#include "../headers/main_utils.h"

using namespace std::placeholders;

CCarController::CCarController(std::istream& input, std::ostream& output, CCar& car)
	: m_input(input)
	, m_output(output)
	, m_car(car)
	, m_actions({ { HELP_COMMAND, std::bind(&CCarController::Help, this) },
		  { INFO_COMMAND, std::bind(&CCarController::Info, this) },
		  { ENGINE_ON_COMMAND, std::bind(&CCarController::EngineOn, this, _1) },
		  { ENGINE_OFF_COMMAND, std::bind(&CCarController::EngineOff, this, _1) },
		  { SET_GEAR_COMMAND, std::bind(&CCarController::SetGear, this, _1) },
		  { SET_SPEED_COMMAND, std::bind(&CCarController::SetSpeed, this, _1) } })
{
}

CCarController::~CCarController()
{
}

bool CCarController::HandleCommand()
{
	std::string commandLine;
	std::getline(m_input, commandLine);
	std::istringstream stream(commandLine);

	std::string action;
	stream >> action;

	auto it = m_actions.find(action);
	if (it != m_actions.end())
	{
		return it->second(stream);
	}
	return false;
}

bool CCarController::Help()
{
	PrintMapCommandDescription(commandDescription, m_output);
	return true;
}

bool CCarController::Info()
{
	std::string info;

	if (m_car.IsTurnedOn())
	{
		info += "Engine is turned on \nCar " + GetDirection() + "\nSpeed is: " + std::to_string(m_car.GetSpeed()) + "\nGear is: " + GetGear();
	}
	else
	{
		info += "Engine is turned off";
	}

	m_output << info << std::endl;

	return true;
}

bool CCarController::EngineOn(std::istream& arguments)
{
	if (!m_car.IsTurnedOn())
	{
		m_car.TurnOnEngine();
	}
	else
	{
		m_output << "Engine is already turned on" << std::endl;
	}
	return true;
}

bool CCarController::EngineOff(std::istream& arguments)
{
	if (!m_car.IsTurnedOn())
	{
		m_output << "Engine is not turned on" << std::endl;
	}
	else if (!m_car.TurnOffEngine())
	{
		m_output << "Engine avalable to turn off only if speed equal 0 and gear are neutral" << std::endl;
	}

	return true;
}

bool CCarController::SetGear(std::istream& arguments)
{
	int gear;
	arguments >> gear;

	if (!m_car.IsTurnedOn())
	{
		m_output << "The engine is not turned on" << std::endl;
	}
	else if (!m_car.SetGear(gear))
	{
		m_output << "The vehicle speed is not suitable" << std::endl;
	}

	return true;
}

bool CCarController::SetSpeed(std::istream& arguments)
{
	int speed;
	arguments >> speed;

	if (!m_car.IsTurnedOn())
	{
		m_output << "The engine is not turned on" << std::endl;
	}
	else if (!m_car.SetSpeed(speed))
	{
		m_output << "The vehicle gear is not suitable for this speed" << std::endl;
	}

	return true;
}

std::string CCarController::GetDirection()
{
	switch (m_car.GetDirection())
	{
	case MoveDirection::BACKWARD:
		return "going backward";
	case MoveDirection::STAY:
		return "is staying";
	case MoveDirection::FORWARD:
		return "is going forward";
	default:
		return "";
		break;
	}
}

std::string CCarController::GetGear()
{
	switch (m_car.GetGear())
	{
	case Gear::REAR:
		return "rear";
	case Gear::NEUTRAL:
		return "neutral";
	case Gear::FIRST:
		return "first";
	case Gear::SECOND:
		return "second";
	case Gear::THIRD:
		return "third";
	case Gear::FOURTH:
		return "fourth";
	case Gear::FIFTH:
		return "fifth";
	default:
		return "";
		break;
	}
}
