#pragma once

#include "IPerson.h"

class IRacer : public IPerson
{
public:
	IRacer(const IRacer&) = default;
	IRacer(const IRacer&&) noexcept = delete;
	IRacer& operator=(const IRacer&) = delete;
	IRacer& operator=(const IRacer&&) noexcept = delete;

	virtual size_t GetAwardsCount() const = 0;

protected:
	IRacer() = default;
	virtual ~IRacer() = default;
};
