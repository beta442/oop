#pragma once

#include <string>

template <class Data>
class ListNode
{
public:
	using Pointer = std::shared_ptr<ListNode>;

public:
	inline ListNode(Data&& data, Pointer const prev = nullptr, Pointer const next = nullptr)
		: m_data(data)
		, m_prev(prev)
		, m_next(next)
	{
	}

	Data m_data;
	Pointer m_prev, m_next;
};
