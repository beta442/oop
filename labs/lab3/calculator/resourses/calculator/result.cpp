#include "../../headers/calculator/CResult.h"

Result::Result(bool status, std::string message)
	: m_status(status)
	, m_oMessage(message)
{
}

Result::Result(bool status)
	: m_status(status)
	, m_oMessage(std::nullopt)
{
}

bool Result::IsOk() const
{
	return m_status;
}

bool Result::HasMessage() const
{
	return m_oMessage.has_value();
}

std::string Result::Message() const
{
	if (HasMessage())
	{
		return m_oMessage.value();
	}
	return "";
}
