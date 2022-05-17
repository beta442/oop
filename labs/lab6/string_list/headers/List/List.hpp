#pragma once

#include "ListIterator.hpp"
#include "ListNode.hpp"

template <class T>
class List
{
public:
	using Node = ListNode<T>;
	using NodePointer = typename Node::NodePointer;

	using ValueType = typename Node::ValueType;
	using Pointer = typename Node::Pointer;
	using ConstPointer = typename Node::ConstPointer;
	using Reference = typename Node::Reference;
	using ConstReference = typename Node::ConstReference;

	using Iterator = ListIterator<List<T>>;
	using ConstIterator = ListConstIterator<List<T>>;

	using ReverseIterator = std::reverse_iterator<Iterator>;
	using ConstReverseIterator = std::reverse_iterator<ConstIterator>;

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

	_NODISCARD inline Iterator begin() noexcept
	{
		return Iterator(m_beg->m_next);
	}

	_NODISCARD inline ConstIterator begin() const noexcept
	{
		return ConstIterator(m_beg->m_next);
	}

	_NODISCARD inline Iterator end() noexcept
	{
		return Iterator(m_end);
	}

	_NODISCARD inline ConstIterator end() const noexcept
	{
		return ConstIterator(m_end);
	}

	_NODISCARD inline ReverseIterator rbegin() noexcept
	{
		return ReverseIterator(end());
	}

	_NODISCARD inline ConstReverseIterator rbegin() const noexcept
	{
		return ConstReverseIterator(end());
	}

	_NODISCARD inline ReverseIterator rend() noexcept
	{
		return ReverseIterator(begin());
	}

	_NODISCARD inline ConstReverseIterator rend() const noexcept
	{
		return ConstReverseIterator(begin());
	}

	_NODISCARD inline ConstIterator cbegin() const noexcept
	{
		return begin();
	}

	_NODISCARD inline ConstIterator cend() const noexcept
	{
		return end();
	}

	_NODISCARD inline ConstReverseIterator crbegin() const noexcept
	{
		return rbegin();
	}

	_NODISCARD inline ConstReverseIterator crend() const noexcept
	{
		return rend();
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
