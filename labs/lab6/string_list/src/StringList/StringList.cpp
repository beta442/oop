#include "../../headers/StringList/CStringList.h"

#include <list>
#include <string>

StringList::StringList()
	: m_beg(std::make_shared<ListNode<Data>>("").get())
	, m_end(std::make_shared<ListNode<Data>>("").get())
	, m_size(0)
{
	m_beg->m_next = m_end;
	m_end->m_prev = m_beg;
}

using Pointer = StringList::Pointer;

template <class Data>
Pointer BuyNode(Pointer prev, Pointer next, Data&& data)
{
	return std::make_shared<ListNode<Data>>(std::move(data), prev, next);
}

void StringList::Insert(const Pointer ptr, Data&& data)
{
	const Pointer nextNode = ptr;
	const Pointer prevNode = nextNode->m_prev;

	const auto newNode = BuyNode(prevNode, nextNode, std::move(data));
	m_size += 1;
	nextNode->m_prev = newNode;
	prevNode->m_next = newNode;
}

void StringList::Clear()
{
	auto& ptr = m_beg->m_next;
	auto& tempPtr = ptr;
	/*for (size_t i = 0, size = Size(); i < size; ++i)
	{
		if (ptr != nullptr)
		{
			ptr = ptr->m_next;
			tempPtr->m_prev = nullptr;
			tempPtr->m_next = nullptr;
			tempPtr
		}
	}*/
}

void StringList::PushFront(Data&& str)
{
	Insert(m_beg->m_next, std::move(str));
}

void StringList::PushFront(const Data& str)
{
	//Insert(m_beg->m_next, str);
}

void StringList::PushBack(Data&& str)
{
	Insert(m_end, std::move(str));
}

void StringList::PushBack(const Data& str)
{
	//Insert(m_end, str);
}

bool StringList::Empty() const
{
	return m_size == 0;
}

size_t StringList::Size() const
{
	return m_size;
}
