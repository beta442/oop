#pragma once

#include "std_lib.h"
#include "car.h"

class CCarController
{
public:
	CCarController(std::istream& input, std::ostream& output, CCar& car);
	~CCarController();

	bool HandleCommand();
	bool IsFinishedWork();

private:
	bool Help();
	bool Info();
	bool EngineOn(std::istream& arguments);
	bool EngineOff(std::istream& arguments);
	bool SetGear(std::istream& arguments);
	bool SetSpeed(std::istream& arguments);
	bool StopWorkflow();

	std::string GetDirection();
	std::string GetGear();

	using ActionsMap = std::map<std::string, std::function<bool(std::istream& arguments)>>;

	bool m_isWorkflowGoesOn;
	std::istream& m_input;
	std::ostream& m_output;
	std::string m_commandLine;
	const ActionsMap m_actions;
	CCar& m_car;
};
