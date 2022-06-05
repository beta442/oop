#pragma once

class IBasicVehicle
{
public:
	IBasicVehicle(const IBasicVehicle&) = default;
	IBasicVehicle(const IBasicVehicle&&) noexcept = delete;
	IBasicVehicle& operator=(const IBasicVehicle&) = delete;
	IBasicVehicle& operator=(const IBasicVehicle&&) noexcept = delete;

	virtual bool IsEmpty() const = 0;
	virtual bool IsFull() const = 0;
	virtual size_t GetPlaceCount() const = 0;
	virtual size_t GetPassengerCount() const = 0;
	virtual void RemoveAllPassengers() = 0;

protected:
	IBasicVehicle() = default;
	~IBasicVehicle() = default;
};
