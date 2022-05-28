#pragma once

#include <string>

class IPerson
{
public:	
	virtual std::string GetName() const = 0;
	virtual std::string GetType() const = 0;

protected:
	~IPerson() = default;
};
