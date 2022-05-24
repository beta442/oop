#pragma once

#include "IRacer.h"
#include "PersonImpl.hpp"

class Racer : public PersonImpl<IRacer>
{
public:
	using Base = PersonImpl<IRacer>;

public:
	Racer(const std::string& name, size_t awardsCount);

	size_t GetAwardsCount() const override;

private:
	size_t m_awardsCount;
};
