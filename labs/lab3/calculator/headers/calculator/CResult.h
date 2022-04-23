#pragma once

#include "../std_lib.h"

class Result
{
public:
	Result(bool status);
	Result(bool status, std::string message);

	bool HasMessage() const;
	bool IsOk() const;
	std::string Message() const;

private:
	bool m_status;
	std::optional<std::string> m_oMessage;
};
