#pragma once

#include "std_lib.h"

constexpr auto PROGRAM_HELLO_MSG = "Virtual car\n--Enter these commands to work with virtual car:\n";

constexpr auto INFO_COMMAND = "Info";
constexpr auto ENGINE_ON_COMMAND = "EngineOn";
constexpr auto ENGINE_OFF_COMMAND = "EngineOff";
constexpr auto SET_GEAR_COMMAND = "SetGear";
constexpr auto SET_SPEED_COMMAND = "SetSpeed";

constexpr auto INFO_COMMAND_DESCRIPTION = "Shows car state: engine status, move direction, speed, gear";
constexpr auto ENGINE_ON_COMMAND_DESCRIPTION = "Turns on car's engine";
constexpr auto ENGINE_OFF_COMMAND_DESCRIPTION = "Turns off car's engine";
constexpr auto SET_GEAR_COMMAND_DESCRIPTION = "SetGear <value>, value is between -1 and 5";
constexpr auto SET_SPEED_COMMAND_DESCRIPTION = "SetSpeed <value>, value is positive";

const std::vector<std::string> commands{
	INFO_COMMAND,
	ENGINE_ON_COMMAND,
	ENGINE_OFF_COMMAND,
	SET_GEAR_COMMAND,
	SET_SPEED_COMMAND,
};

const std::map<std::string, std::string> commandDescription{
	{ INFO_COMMAND, INFO_COMMAND_DESCRIPTION },
	{ ENGINE_ON_COMMAND, ENGINE_ON_COMMAND_DESCRIPTION },
	{ ENGINE_OFF_COMMAND, ENGINE_OFF_COMMAND_DESCRIPTION },
	{ SET_GEAR_COMMAND, SET_GEAR_COMMAND_DESCRIPTION },
	{ SET_SPEED_COMMAND, SET_SPEED_COMMAND_DESCRIPTION },
};

void PrintHelloMsg();
void PrintMapCommandDescription(std::map<std::string, std::string> map);
