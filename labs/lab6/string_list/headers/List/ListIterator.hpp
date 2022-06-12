#pragma once

#include <cstddef>
#include <iterator>
#include <variant>

template <class MyList>
class ListConstIterator
{
public:
	using NodePointer = typename MyList::NodePointer;

	using iterator_category = std::bidirectional_iterator_tag;

	using value_type = typename MyList::ValueType;
	using difference_type = ptrdiff_t;
	using pointer = typename MyList::ConstPointer;
	using reference = const value_type&;

	friend MyList;

public:
	reference operator*() const
	{
		if (m_ptr->m_next == nullptr || m_ptr->m_prev == nullptr)
		{
			throw std::out_of_range("Cannot dereference end list iterator");
		}
		return std::get<value_type>(m_ptr->m_data);
	}

	NodePointer operator->() const
	{
		if (m_ptr->m_next == nullptr || m_ptr->m_prev == nullptr)
		{
			throw std::out_of_range("Cannot get pointer of end list iterator");
		}
		return m_ptr;
	}

	ListConstIterator& operator++()
	{
		if (m_ptr->m_next == nullptr)
		{
			throw std::out_of_range("Cannot increment end list iterator");
		}
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
		if (m_ptr->m_prev == nullptr)
		{
			throw std::out_of_range("Cannot dereference end list iterator");
		}
		m_ptr = m_ptr->m_prev;
		return *this;
	}

	ListConstIterator operator--(int)
	{
		ListConstIterator temp = *this;
		--*this;
		return temp;
	}

	bool operator==(const ListConstIterator& other) const
	{
		return m_ptr == other.m_ptr;
	}

	bool operator!=(const ListConstIterator& other) const
	{
		return !(*this == other);
	}
	
protected:
	explicit ListConstIterator()
		: m_ptr()
	{
	}

	explicit ListConstIterator(NodePointer ptr)
		: m_ptr(ptr)
	{
	}

private:
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
	using pointer = typename MyList::Pointer;
	using reference = value_type&;

	friend MyList;

public:
	reference operator*() const
	{
		return (reference)(MyBase::operator*());
	}

	NodePointer operator->() const
	{
		return static_cast<NodePointer>(MyBase::operator->());
	}

	ListIterator& operator++()
	{
		++(*(MyBase*)this);
		return *this;
	}

	ListIterator operator++(int)
	{
		ListIterator temp = *this;
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
		ListIterator temp = *this;
		--*this;
		return temp;
	}

protected:
	explicit ListIterator()
		: MyBase()
	{
	}

	explicit ListIterator(NodePointer ptr)
		: MyBase(ptr)
	{
	}
};
