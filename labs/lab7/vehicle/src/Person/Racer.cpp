#include "../../headers/Person/Racer.h"

Racer::Racer(std::string name, size_t awardsCount)
	: Base(std::move(name), s_type)
	, m_awardsCount(awardsCount)
{
}

size_t Racer::GetAwardsCount() const
{
	return m_awardsCount;
}
