#pragma once

#include <vector>

#include "IVehicle.h"

template <typename Passenger, typename Base = IVehicle<Passenger>>
class VehicleImpl : public Base
{
public:
	VehicleImpl(size_t maxCapacity)
		: m_placeCount(maxCapacity)
		, m_passengersCount(0)
		, m_passengers()
	{
	}

	inline void AddPassenger(std::shared_ptr<Passenger> pPassenger) override
	{
		if (m_passengersCount == m_placeCount)
		{
			throw std::logic_error("Can't add a passenger, the transport is full");
		}

		m_passengers.push_back(pPassenger);
		++m_passengersCount;
	}

	inline Passenger const& GetPassenger(size_t index) const override
	{
		if (index >= m_passengersCount)
		{
			throw std::out_of_range("Failed to get passenger. Index is out of range");
		}

		return *m_passengers[index];
	}

	inline void RemovePassenger(size_t index) override
	{
		if (index >= m_passengersCount)
		{
			throw std::out_of_range("Failed to remove passenger. Index is out of range");
		}

		m_passengers.erase(m_passengers.begin() + index);
		--m_passengersCount;
	}

	inline bool IsEmpty() const
	{
		return m_passengersCount == 0;
	}

	inline bool IsFull() const
	{
		return m_passengersCount == m_placeCount;
	}

	inline size_t GetPlaceCount() const
	{
		return m_placeCount;
	}

	inline size_t GetPassengerCount() const
	{
		return m_passengersCount;
	}

	void RemoveAllPassengers()
	{
		m_passengersCount = 0;
		m_passengers.clear();
	}

private:
	size_t m_placeCount;
	size_t m_passengersCount;
	std::vector<std::shared_ptr<Passenger>> m_passengers;
};
