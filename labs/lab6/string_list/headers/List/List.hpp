#pragma once

#include "ListIterator.h"
#include "ListNode.hpp"

template <class T>
class List
{
public:
	using Node = ListNode<T>;
	using ValueType = typename Node::ValueType;
	using NodePointer = typename Node::NodePointer;
	using Pointer = typename Node::Pointer;
	using ConstPointer = typename Node::ConstPointer;
	using Reference = typename Node::Reference;
	using ConstReference = typename Node::ConstReference;

public:
	List()
		: m_beg(std::make_shared<ListNode<T>>())
		, m_end(std::make_shared<ListNode<T>>())
		, m_size(0)
	{
		m_beg->m_next = m_end;
		m_end->m_prev = m_beg;
	}

	~List()
	{
		Clear();
		m_beg->m_next = nullptr;
		m_end->m_prev = nullptr;
		m_beg.reset();
		m_end.reset();
	}
	
	void Clear()
	{
		NodePointer ptr = m_beg, tempPtr = m_beg->m_next;
		m_beg->m_next = m_end;
		m_end->m_prev = m_beg;
		while (ptr != m_end && tempPtr != m_end)
		{
			ptr = tempPtr->m_next;
			ptr->m_prev = nullptr;
			tempPtr.reset();
			tempPtr = ptr;
		}
		m_size = 0;
	}

	bool Empty() const
	{
		return m_size == 0;
	}

	size_t Size() const
	{
		return m_size;
	}

	inline void PushFront(T&& str)
	{
		Insert(m_beg->m_next, str);
	}

	inline void PushBack(T&& str)
	{
		Insert(m_end, str);
	}

	inline void PushFront(const T& str)
	{
		Insert(m_beg->m_next, str);
	}

	inline void PushBack(const T& str)
	{
		Insert(m_end, str);
	}

private:
	template <class T>
	inline NodePointer BuyNode(NodePointer prev, NodePointer next, T&& data)
	{
		return std::make_shared<Node>(std::forward<T>(data), prev, next);
	}

	template <class T>
	inline void Insert(const NodePointer ptr, T&& data)
	{
		const NodePointer nextNode = ptr;
		const NodePointer prevNode = nextNode->m_prev;

		const NodePointer newNode = BuyNode(prevNode, nextNode, std::forward<T>(data));
		m_size += 1;
		nextNode->m_prev = newNode;
		prevNode->m_next = newNode;
	}

	size_t m_size;
	NodePointer m_beg, m_end;
};
