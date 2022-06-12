#pragma once

#include "ListIterator.hpp"
#include "ListNode.hpp"

template <class T>
class List
{
public:
	using Node = ListNode<List, T>;
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
		: m_beg(std::make_shared<Node>())
		, m_end(std::make_shared<Node>())
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

	List(const List<T>& other) = delete;
	List(List<T>&& other) = delete;
	
	void Clear() noexcept
	{
		Iterator it = begin();
		m_beg->m_next = m_end;
		m_end->m_prev = m_beg;
		const Iterator endIt = end();
		while (it != endIt)
		{
			++it;
			auto itTemp = Iterator(it.m_ptr->m_prev);
			it.m_ptr->m_prev = nullptr;
			itTemp.m_ptr.reset();
			itTemp = it;
		}
		m_size = 0;
	}

	bool Empty() const noexcept
	{
		return m_size == 0;
	}

	template <class T>
	Iterator Emplace(ConstIterator it, T&& val)
	{
		if (it.m_ptr == nullptr)
		{
			throw std::out_of_range("List emplace iterator references to nullptr");
		}
		if (it.m_ptr == m_beg)
		{
			throw std::out_of_range("List emplace iterator is out of range");
		}
		Insert(it, std::forward<T>(val));
		return MakeIter(--it);
	}

	Iterator Erase(ConstIterator it)
	{
		if (it.m_ptr == nullptr)
		{
			throw std::out_of_range("List erase iterator references to nullptr");
		}
		if (it.m_ptr == m_beg || it.m_ptr == m_end)
		{
			throw std::out_of_range("List erase iterator is out of range");
		}
		NodePointer ptr = UnlinkNode(it++);
		ptr.reset();
		return MakeIter(it);
	}

	size_t Size() const noexcept
	{
		return m_size;
	}

	void PushFront(T&& val)
	{
		Insert(begin(), std::move(val));
	}

	void PushBack(T&& val)
	{
		Insert(end(), std::move(val));
	}

	void PushFront(const T& val)
	{
		Insert(begin(), val);
	}

	void PushBack(const T& val)
	{
		Insert(end(), val);
	}

	Iterator begin() noexcept
	{
		return Iterator(m_beg->m_next);
	}

	ConstIterator begin() const noexcept
	{
		return ConstIterator(m_beg->m_next);
	}

	Iterator end() noexcept
	{
		return Iterator(m_end);
	}

	ConstIterator end() const noexcept
	{
		return ConstIterator(m_end);
	}

	ReverseIterator rbegin() noexcept
	{
		return ReverseIterator(end());
	}

	ConstReverseIterator rbegin() const noexcept
	{
		return ConstReverseIterator(end());
	}

	ReverseIterator rend() noexcept
	{
		return ReverseIterator(begin());
	}

	ConstReverseIterator rend() const noexcept
	{
		return ConstReverseIterator(begin());
	}

	ConstIterator cbegin() const noexcept
	{
		return begin();
	}

	ConstIterator cend() const noexcept
	{
		return end();
	}

	ConstReverseIterator crbegin() const noexcept
	{
		return rbegin();
	}

	ConstReverseIterator crend() const noexcept
	{
		return rend();
	}

public:
	List<T> operator=(const List<T>& other) = delete;
	List<T> operator=(List<T>&& other) = delete;

private:
	template <class T>
	NodePointer BuyNode(NodePointer prev, NodePointer next, T&& data)
	{
		return std::make_shared<Node>(std::forward<T>(data), prev, next);
	}

	template <class T>
	void Insert(ConstIterator it, T&& data)
	{
		const NodePointer nextNode = it.m_ptr;
		const NodePointer prevNode = nextNode->m_prev;

		const NodePointer newNode = BuyNode(prevNode, nextNode, std::forward<T>(data));
		m_size += 1;
		nextNode->m_prev = newNode;
		prevNode->m_next = newNode;
	}

	Iterator MakeIter(ConstIterator it) const noexcept
	{
		return Iterator(it.m_ptr);
	}

	NodePointer UnlinkNode(ConstIterator it)
	{
		NodePointer ptr = it.m_ptr;

		ptr->m_prev->m_next = ptr->m_next;
		ptr->m_next->m_prev = ptr->m_prev;

		--m_size;
		return ptr;
	}

	size_t m_size;
	NodePointer m_beg, m_end;
};
