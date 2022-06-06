#pragma once

#include "IRacer.h"
#include "PersonImpl.hpp"

class Racer : public PersonImpl<IRacer>
{
public:
	using Base = PersonImpl<IRacer>;

public:
	Racer(std::string name, size_t awardsCount);

	size_t GetAwardsCount() const final;

private:
	static inline const std::string s_type = "Racer";

	size_t m_awardsCount;
};
