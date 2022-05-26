#pragma once

#include <memory>
#include <string>
#include <optional>

#include "IBasicVehicle.h"

template <typename Passenger>
class IVehicle : public IBasicVehicle
{
public:
	~IVehicle() = default;

	virtual void AddPassenger(std::shared_ptr<Passenger> pPassenger) = 0;
	virtual Passenger const& GetPassenger(size_t index) const = 0;
	virtual void RemovePassenger(size_t index) = 0;
	virtual std::optional<size_t> GetIndexOfPassenger(const std::string& name) const = 0;
};
