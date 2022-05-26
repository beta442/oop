#pragma once

#include <string>

class IPerson
{
public:
	~IPerson() = default;
	
	virtual std::string GetName() const = 0;
	virtual std::string GetType() const = 0;
};
