#include "../../headers/Person/Racer.h"

Racer::Racer(const std::string& name, size_t awardsCount)
	: PersonImpl<IRacer>(name)
	, m_awardsCount(awardsCount)
{
}

size_t Racer::GetAwardsCount() const
{
	return m_awardsCount;
}