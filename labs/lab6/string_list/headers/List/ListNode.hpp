#pragma once

#include <memory>
#include <variant>

template <class MyList, class T>
class ListNode
{
public:
	using NodePointer = std::shared_ptr<ListNode>;
	using ValueType = T;
	using Pointer = ValueType*;
	using ConstPointer = const ValueType*;
	using Reference = ValueType&;
	using ConstReference = const ValueType&;

	friend MyList;
	friend ListConstIterator<MyList>;

public:
	ListNode()
		: m_data(nullptr)
		, m_prev(nullptr)
		, m_next(nullptr)
	{
	}

	template <class T>
	explicit ListNode(T&& data, NodePointer prev = nullptr, NodePointer next = nullptr)
		: m_data(std::forward<T>(data))
		, m_prev(std::move(prev))
		, m_next(std::move(next))
	{
	}

private:
	std::variant<T, Pointer> m_data;
	NodePointer m_prev, m_next;
};
