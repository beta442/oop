#pragma once

#include <cstddef>
#include <iterator>

template <class MyList, class Base = std::_Iterator_base0>
class ListUncheckedConstIterator : public Base
{
public:
	using iterator_category = std::bidirectional_iterator_tag;

	using NodePointer = typename MyList::NodePointer;

	using value_type = typename MyList::ValueType;
	using difference_type = ptrdiff_t;
	using pointer = typename MyList::ConstPointer;
	using reference = typename MyList::ConstReference;

public:
	ListUncheckedConstIterator(NodePointer ptr)
		: m_ptr(ptr)
	{
	}

	NodePointer m_ptr;
};

template <class MyList>
class ListUncheckedIterator : public ListUncheckedConstIterator<MyList>
{
public:
	using MyBase = ListUncheckedConstIterator<MyList>;
	using NodePointer = typename MyList::NodePointer;

	using iterator_category = typename MyBase::iterator_category;

	using value_type = typename MyList::ValueType;
	using difference_type = ptrdiff_t;
	using pointer = typename MyList::Pointer;
	using reference = typename MyList::Reference;

public:
	ListUncheckedIterator(NodePointer ptr)
		: MyBase(ptr)
	{
	}
};

template <class MyList>
class ListConstIterator : public ListUncheckedConstIterator<MyList, std::_Iterator_base>
{
public:
	using MyBase = ListUncheckedConstIterator<MyList, std::_Iterator_base>;
	using NodePointer = typename MyList::NodePointer;

	using iterator_category = typename MyBase::iterator_category;

	using value_type = typename MyList::ValueType;
	using difference_type = ptrdiff_t;
	using pointer = typename MyList::ConstPointer;
	using reference = typename MyList::ConstReference;

public:
	ListConstIterator(NodePointer ptr)
		: MyBase(ptr)
	{
	}
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

};
