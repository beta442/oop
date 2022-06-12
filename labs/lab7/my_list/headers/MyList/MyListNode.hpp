#pragma once

#include <memory>
#include <variant>

template <class MyList, class T>
class MyListNode
{
public:
	using NodePointer = std::shared_ptr<MyListNode>;
	using ValueType = T;
	using Pointer = ValueType*;
	using ConstPointer = const ValueType*;
	using Reference = ValueType&;
	using ConstReference = const ValueType&;

	friend MyList;
	friend MyListConstIterator<MyList>;

public:
	MyListNode()
		: m_data(nullptr)
		, m_prev(nullptr)
		, m_next(nullptr)
	{
	}

	template <class T>
	explicit MyListNode(T&& data, NodePointer prev = nullptr, NodePointer next = nullptr)
		: m_data(std::forward<T>(data))
		, m_prev(std::move(prev))
		, m_next(std::move(next))
	{
	}

private:
	std::variant<T, Pointer> m_data;
	NodePointer m_prev, m_next;
};
