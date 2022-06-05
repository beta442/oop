#pragma once

#include "IRacer.h"
#include "PersonImpl.hpp"

class Racer : public PersonImpl<IRacer>
{
public:
	using Base = PersonImpl<IRacer>;

	static inline const std::string s_type = "Racer";

public:
	Racer(const std::string& name, size_t awardsCount);

	size_t GetAwardsCount() const override final;

private:
	size_t m_awardsCount;
};
