#pragma once

#include <cstddef>
#include <iterator>
#include <variant>

template <class MyList>
class MyListConstIterator
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
	_NODISCARD reference operator*() const
	{
		if (m_ptr->m_next == nullptr || m_ptr->m_prev == nullptr)
		{
			throw std::out_of_range("Cannot dereference end list iterator");
		}
		return std::get<value_type>(m_ptr->m_data);
	}

	_NODISCARD NodePointer operator->() const
	{
		if (m_ptr->m_next == nullptr || m_ptr->m_prev == nullptr)
		{
			throw std::out_of_range("Cannot get pointer of end list iterator");
		}
		return m_ptr;
	}

	MyListConstIterator& operator++()
	{
		if (m_ptr->m_next == nullptr)
		{
			throw std::out_of_range("Cannot increment end list iterator");
		}
		m_ptr = m_ptr->m_next;
		return *this;
	}

	MyListConstIterator operator++(int)
	{
		MyListConstIterator temp = *this;
		++*this;
		return temp;
	}

	MyListConstIterator& operator--()
	{
		if (m_ptr->m_prev == nullptr)
		{
			throw std::out_of_range("Cannot dereference end list iterator");
		}
		m_ptr = m_ptr->m_prev;
		return *this;
	}

	MyListConstIterator operator--(int)
	{
		MyListConstIterator temp = *this;
		--*this;
		return temp;
	}

	_NODISCARD bool operator==(const MyListConstIterator& other) const
	{
		return m_ptr == other.m_ptr;
	}

	_NODISCARD bool operator!=(const MyListConstIterator& other) const
	{
		return !(*this == other);
	}

protected:
	explicit MyListConstIterator()
		: m_ptr()
	{
	}

	explicit MyListConstIterator(NodePointer ptr)
		: m_ptr(ptr)
	{
	}

private:
	NodePointer m_ptr;
};

template <class MyList>
class MyListIterator : public MyListConstIterator<MyList>
{
public:
	using MyBase = MyListConstIterator<MyList>;
	using NodePointer = typename MyList::NodePointer;

	using iterator_category = typename MyBase::iterator_category;

	using value_type = typename MyList::ValueType;
	using difference_type = ptrdiff_t;
	using pointer = typename MyList::Pointer;
	using reference = value_type&;

	friend MyList;

public:
	_NODISCARD reference operator*() const
	{
		return (reference)(MyBase::operator*());
	}

	_NODISCARD NodePointer operator->() const
	{
		return static_cast<NodePointer>(MyBase::operator->());
	}

	MyListIterator& operator++()
	{
		++(*(MyBase*)this);
		return *this;
	}

	MyListIterator operator++(int)
	{
		MyListIterator temp = *this;
		++*this;
		return temp;
	}

	MyListIterator& operator--()
	{
		--(*(MyBase*)this);
		return *this;
	}

	MyListIterator operator--(int)
	{
		MyListIterator temp = *this;
		--*this;
		return temp;
	}

protected:
	explicit MyListIterator()
		: MyListConstIterator()
	{
	}

	explicit MyListIterator(NodePointer ptr)
		: MyBase(ptr)
	{
	}
};
