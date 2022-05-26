#pragma once

#include "IPerson.h"

class IRacer : public IPerson
{
public:
	~IRacer() = default;

	virtual size_t GetAwardsCount() const = 0;
};
