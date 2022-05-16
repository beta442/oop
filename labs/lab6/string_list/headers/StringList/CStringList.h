#pragma once

#include "CStringListNode.h"

class StringList
{
public:
	using Data = std::string;
	using Node = ListNode<Data>;
	using Pointer = Node::Pointer;

public:
	StringList();
	~StringList();

	void Clear();
	template <class Data>
	inline void PushFront(Data&& str)
	{
		Insert(m_beg->m_next, std::move(str));
	}

	template <class Data>
	void PushBack(Data&& str)
	{
		Insert(m_end, std::move(str));
	}

	bool Empty() const;
	size_t Size() const;

private:
	void Insert(const Pointer ptr, Data&& data);

	size_t m_size;
	Pointer m_beg, m_end;
};
