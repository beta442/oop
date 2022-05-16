#include "../../headers/StringList/CStringList.h"

#include <list>
#include <string>

StringList::StringList()
	: m_beg(std::make_shared<ListNode<Data>>(""))
	, m_end(std::make_shared<ListNode<Data>>(""))
	, m_size(0)
{
	m_beg->m_next = m_end;
	m_end->m_prev = m_beg;
}

StringList::~StringList()
{
	m_beg->m_next = nullptr;
	m_end->m_prev = nullptr;
	m_beg.reset();
	m_end.reset();
}

using Pointer = StringList::Pointer;
using Data = StringList::Data;
using Node = StringList::Node;

Pointer BuyNode(Pointer prev, Pointer next, Data&& data)
{
	return std::make_shared<Node>(std::move(data), prev, next);
}

void StringList::Insert(const Pointer ptr, Data&& data)
{
	const Pointer nextNode = ptr;
	const Pointer prevNode = nextNode->m_prev;

	const Pointer newNode = BuyNode(prevNode, nextNode, std::move(data));
	m_size += 1;
	nextNode->m_prev = newNode;
	prevNode->m_next = newNode;
}

void StringList::Clear()
{
	Pointer ptr = m_beg, tempPtr = m_beg->m_next;
	m_beg->m_next = m_end;
	m_end->m_prev = m_beg;
	while (ptr != m_end && tempPtr != m_end)
	{
		ptr = tempPtr->m_next;
		tempPtr.reset();
		tempPtr = ptr;
	}
	m_size = 0;
}

bool StringList::Empty() const
{
	return m_size == 0;
}

size_t StringList::Size() const
{
	return m_size;
}
