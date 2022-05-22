#pragma once

#include "MyListIterator.hpp"
#include "MyListNode.hpp"

template <class T>
class MyList
{
public:
	using Node = MyListNode<T>;
	using NodePointer = typename Node::NodePointer;

	using ValueType = typename Node::ValueType;
	using Pointer = typename Node::Pointer;
	using ConstPointer = typename Node::ConstPointer;
	using Reference = typename Node::Reference;
	using ConstReference = typename Node::ConstReference;

	using Iterator = MyListIterator<MyList<T>>;
	using ConstIterator = MyListConstIterator<MyList<T>>;

	using ReverseIterator = std::reverse_iterator<Iterator>;
	using ConstReverseIterator = std::reverse_iterator<ConstIterator>;

public:
	MyList()
		: m_beg(std::make_shared<MyListNode<T>>())
		, m_end(std::make_shared<MyListNode<T>>())
		, m_size(0)
	{
		m_beg->m_next = m_end;
		m_end->m_prev = m_beg;
	}

	~MyList()
	{
		Clear();
		m_beg->m_next = nullptr;
		m_end->m_prev = nullptr;
		m_beg.reset();
		m_end.reset();
	}

	MyList(const MyList<T>& other) = delete;
	MyList(MyList<T>&& other) = delete;

	void Clear() noexcept
	{
		Iterator it = begin(), itTemp = begin();
		m_beg->m_next = m_end;
		m_end->m_prev = m_beg;
		const Iterator endIt = end();
		while (it != endIt && itTemp != endIt)
		{
			++it;
			it.m_ptr->m_prev = nullptr;
			itTemp.m_ptr.reset();
			itTemp = it;
		}
		m_size = 0;
	}

	_NODISCARD bool Empty() const noexcept
	{
		return m_size == 0;
	}

	template <class T>
	Iterator Emplace(ConstIterator it, T&& val)
	{
		if (it.m_ptr == m_beg)
		{
			throw std::out_of_range("List erase iterator outside of range");
		}
		Insert(it, val);
		return MakeIter(--it);
	}

	Iterator Erase(ConstIterator it)
	{
		if (it.m_ptr == m_beg || it.m_ptr == m_end)
		{
			throw std::out_of_range("List erase iterator outside of range");
		}
		NodePointer ptr = UnlinkNode(it++);
		ptr.reset();
		return MakeIter(it);
	}

	_NODISCARD size_t Size() const noexcept
	{
		return m_size;
	}

	inline void PushFront(T&& val)
	{
		Insert(begin(), val);
	}

	inline void PushBack(T&& val)
	{
		Insert(end(), val);
	}

	inline void PushFront(const T& val)
	{
		Insert(begin(), val);
	}

	inline void PushBack(const T& val)
	{
		Insert(end(), val);
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

public:
	MyList<T> operator=(const MyList<T>& other) = delete;
	MyList<T> operator=(MyList<T>&& other) = delete;

private:
	template <class T>
	inline NodePointer BuyNode(NodePointer prev, NodePointer next, T&& data)
	{
		return std::make_shared<Node>(std::forward<T>(data), prev, next);
	}

	template <class T>
	inline void Insert(ConstIterator it, T&& data)
	{
		const NodePointer nextNode = it.m_ptr;
		const NodePointer prevNode = nextNode->m_prev;

		const NodePointer newNode = BuyNode(prevNode, nextNode, std::forward<T>(data));
		m_size += 1;
		nextNode->m_prev = newNode;
		prevNode->m_next = newNode;
	}

	inline Iterator MakeIter(ConstIterator it) const noexcept
	{
		return Iterator(it.m_ptr);
	}

	inline NodePointer UnlinkNode(ConstIterator it)
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
