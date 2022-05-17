#pragma once

#include <cstddef>
#include <iterator>

template <class MyList, class Base = std::_Iterator_base0>
class ListConstIterator : public Base
{
public:
	using NodePointer = typename MyList::NodePointer;

	using iterator_category = std::bidirectional_iterator_tag;

	using value_type = typename MyList::ValueType;
	using difference_type = ptrdiff_t;
	using pointer = typename MyList::ConstPointer;
	using reference = typename MyList::ConstReference;

public:
	ListConstIterator(NodePointer ptr)
		: m_ptr(ptr)
	{
	}

	_NODISCARD reference operator*() const
	{
		return m_ptr->m_data;
	}

	_NODISCARD pointer operator->() const
	{
		return &m_ptr->m_data;
	}

	ListConstIterator& operator++()
	{
		m_ptr = m_ptr->m_next;
		return *this;
	}

	ListConstIterator operator++(int)
	{
		ListConstIterator temp = *this;
		++*this;
		return temp;
	}

	ListConstIterator& operator--()
	{
		m_ptr = m_ptr->m_prev;
		return *this;
	}

	ListConstIterator operator--(int)
	{
		ListConstIterator temp = *this;
		--*this;
		return temp;
	}

	_NODISCARD bool operator==(const ListConstIterator& other) const
	{
		return m_ptr == other.m_ptr;
	}

	_NODISCARD bool operator!=(const ListConstIterator& other) const
	{
		return !(*this == other);
	}

	NodePointer m_ptr;
};

template <class MyList>
class ListIterator : public ListConstIterator<MyList>
{
public:
	using MyBase = ListConstIterator<MyList>;
	using NodePointer = typename MyList::NodePointer;

	using iterator_category = typename MyBase::iterator_category;

	using value_type = typename MyList::ValueType;
	using difference_type = ptrdiff_t;
	using pointer = typename MyList::ConstPointer;
	using reference = typename MyList::ConstReference;

public:
	ListIterator(NodePointer ptr)
		: MyBase(ptr)
	{
	}

	_NODISCARD reference operator*() const
	{
		return static_cast<reference>(MyBase::operator*());
	}

	_NODISCARD pointer operator->() const
	{
		return static_cast<pointer>(MyBase::operator->());
	}

	ListIterator& operator++()
	{
		++(*(MyBase*)this);
		return *this;
	}

	ListIterator operator++(int)
	{
		ListConstIterator temp = *this;
		++*this;
		return temp;
	}

	ListIterator& operator--()
	{
		--(*(MyBase*)this);
		return *this;
	}

	ListIterator operator--(int)
	{
		ListConstIterator temp = *this;
		--*this;
		return temp;
	}
};
