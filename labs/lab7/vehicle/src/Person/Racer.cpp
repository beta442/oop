#include "../../headers/Person/Racer.h"

Racer::Racer(const std::string& name, size_t awardsCount)
	: Base(name, s_type)
	, m_awardsCount(awardsCount)
{
}

size_t Racer::GetAwardsCount() const
{
	return m_awardsCount;
}
