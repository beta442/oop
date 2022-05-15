#pragma once

#include "CStringListNode.h"

class StringList
{
public:
	using Data = std::string;
	using Pointer = ListNode<Data>::Pointer;

public:
	StringList();

	void Clear();
	void PushFront(Data&& str);
	void PushFront(const Data& str);
	void PushBack(Data&& str);
	void PushBack(const Data& str);
	bool Empty() const;
	size_t Size() const;

private:
	void Insert(const Pointer ptr, Data&& data);

	size_t m_size;
	Pointer m_beg, m_end;
};
