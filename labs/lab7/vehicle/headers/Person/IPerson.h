#pragma once

#include <string>

class IPerson
{
public:	
	IPerson(const IPerson&) = delete;
	IPerson(const IPerson&&) noexcept = delete;
	IPerson& operator=(const IPerson&) = delete;
	IPerson& operator=(const IPerson&&) noexcept = delete;

	virtual std::string GetName() const = 0;
	virtual std::string GetType() const = 0;

protected:
	IPerson() = default;
	virtual ~IPerson() = default;
};
