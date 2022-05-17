#pragma once

#include <memory>

template <class T>
class ListNode
{
public:
	using Pointer = std::shared_ptr<ListNode>;

public:
	inline ListNode()
		: m_data()
		, m_prev(nullptr)
		, m_next(nullptr)
	{
	}

	template <class T>
	inline ListNode(T&& data, Pointer const prev = nullptr, Pointer const next = nullptr)
		: m_data(std::forward<T>(data))
		, m_prev(prev)
		, m_next(next)
	{
	}

	T m_data;
	Pointer m_prev, m_next;
};
