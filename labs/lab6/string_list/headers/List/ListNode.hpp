#pragma once

#include <memory>
#include <variant>

template <class T>
class ListNode
{
public:
	using NodePointer = std::shared_ptr<ListNode>;
	using ValueType = T;
	using Pointer = ValueType*;
	using ConstPointer = const ValueType*;
	using Reference = ValueType&;
	using ConstReference = const ValueType&;

public:
	inline ListNode()
		: m_data(nullptr)
		, m_prev(nullptr)
		, m_next(nullptr)
	{
	}

	template <class T>
	inline ListNode(T&& data, NodePointer const prev = nullptr, NodePointer const next = nullptr)
		: m_data(std::forward<T>(data))
		, m_prev(prev)
		, m_next(next)
	{
	}

	std::variant<T, Pointer> m_data;
	NodePointer m_prev, m_next;
};
