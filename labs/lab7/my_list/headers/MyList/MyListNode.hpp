#pragma once

#include <memory>
#include <variant>

template <class T>
class MyListNode
{
public:
	using NodePointer = std::shared_ptr<MyListNode>;
	using ValueType = T;
	using Pointer = ValueType*;
	using ConstPointer = const ValueType*;
	using Reference = ValueType&;
	using ConstReference = const ValueType&;

public:
	inline MyListNode()
		: m_data(nullptr)
		, m_prev(nullptr)
		, m_next(nullptr)
	{
	}

	template <class T>
	inline MyListNode(T&& data, NodePointer const prev = nullptr, NodePointer const next = nullptr)
		: m_data(std::forward<T>(data))
		, m_prev(prev)
		, m_next(next)
	{
	}

	std::variant<T, Pointer> m_data;
	NodePointer m_prev, m_next;
};
