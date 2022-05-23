#pragma once

#include <algorithm>
#include <vector>

template <typename T>
bool FindMax(std::vector<T> const& arr, T& maxValue)
{
	if (arr.size() == 0)
	{
		return false;
	}

	auto result = std::max_element(std::begin(arr), std::end(arr));
	maxValue = *result;

	return result != arr.end();
}

static inline bool CharStringCompare(const char* lhs, const char* rhs)
{
	return std::strcmp(lhs, rhs);
}

template <>
bool FindMax<const char*>(std::vector<const char*> const& arr, const char*& maxValue)
{
	if (arr.size() == 0)
	{
		return false;
	}

	auto result = std::max_element(std::begin(arr), std::end(arr), CharStringCompare);
	maxValue = *result;

	return result != arr.end();
}

template <typename T, typename Less>
bool FindMax(std::vector<T> const& arr, T& maxValue, Less const& less)
{
	if (arr.size() == 0)
	{
		return false;
	}

	auto result = std::max_element(std::begin(arr), std::end(arr), less);
	if (result == arr.end())
	{
		return false;
	}
	maxValue = *result;

	return true;
}
