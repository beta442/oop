#include "../../headers/string/CMyStringIterator.h"

#include <stdexcept>

MyStringConstIterator::MyStringConstIterator(pointer ptr)
	: m_ptr(ptr)
{
}

MyStringConstIterator::reference MyStringConstIterator::operator*() const
{
	if (m_ptr == nullptr)
	{
		throw std::logic_error("Can't dereference nullptr");
	}
	return *m_ptr;
}

MyStringConstIterator::pointer MyStringConstIterator::operator->() const
{
	return m_ptr;
}

MyStringConstIterator& MyStringConstIterator::operator++()
{
	++m_ptr;
	return *this;
}

MyStringConstIterator MyStringConstIterator::operator++(int)
{
	MyStringConstIterator temp(*this);
	++*this;
	return temp;
}

MyStringConstIterator& MyStringConstIterator::operator--()
{
	--m_ptr;
	return *this;
}

MyStringConstIterator MyStringConstIterator::operator--(int)
{
	MyStringConstIterator temp(*this);
	--*this;
	return temp;
}

MyStringConstIterator& MyStringConstIterator::operator+=(const difference_type offset)
{
	m_ptr += offset;
	return *this;
}

MyStringConstIterator MyStringConstIterator::operator+(const difference_type offset) const
{
	MyStringConstIterator temp = *this;
	return (temp += offset);
}

MyStringConstIterator& MyStringConstIterator::operator-=(const difference_type offset)
{
	m_ptr -= offset;
	return *this;
}

MyStringConstIterator MyStringConstIterator::operator-(const difference_type offset) const
{
	MyStringConstIterator temp = *this;
	return (temp -= offset);
}

MyStringConstIterator::difference_type MyStringConstIterator::operator-(const MyStringConstIterator& other) const
{
	return m_ptr - other.m_ptr;
}

MyStringConstIterator::reference MyStringConstIterator::operator[](const difference_type offset) const
{
	return *(*this + offset);
}

bool MyStringConstIterator::operator==(const MyStringConstIterator& other) const
{
	return m_ptr == other.m_ptr;
}

bool MyStringConstIterator::operator!=(const MyStringConstIterator& other) const
{
	return !(*this == other);
}

bool MyStringConstIterator::operator<(const MyStringConstIterator& other) const
{
	return m_ptr < other.m_ptr;
}

bool MyStringConstIterator::operator>(const MyStringConstIterator& other) const
{
	return m_ptr > other.m_ptr;
}

bool MyStringConstIterator::operator<=(const MyStringConstIterator& other) const
{
	return !(other < *this);
}

bool MyStringConstIterator::operator>=(const MyStringConstIterator& other) const
{
	return !(*this < other);
}

/*-------------------------------------------------------------------------------------------------------------------*/

MyStringIterator::MyStringIterator(pointer ptr)
	: MyStringConstIterator(ptr)
{
}

MyStringIterator::reference MyStringIterator::operator*() const
{
	return const_cast<reference>(MyStringConstIterator::operator*());
}

MyStringIterator::pointer MyStringIterator::operator->() const
{
	return const_cast<pointer>(MyStringConstIterator::operator->());
}

MyStringIterator& MyStringIterator::operator++()
{
	++*(MyStringConstIterator*)this;
	return *this;
}

MyStringIterator MyStringIterator::operator++(int)
{
	MyStringIterator temp = *this;
	++*this;
	return temp;
}

MyStringIterator& MyStringIterator::operator--()
{
	--*(MyStringConstIterator*)this;
	return *this;
}

MyStringIterator MyStringIterator::operator--(int)
{
	MyStringIterator temp = *this;
	--*this;
	return temp;
}

MyStringIterator& MyStringIterator::operator+=(const difference_type offset)
{
	*(MyStringConstIterator*)this += offset;
	return *this;
}

MyStringIterator MyStringIterator::operator+(const difference_type offset) const
{
	MyStringIterator temp = *this;
	return (temp += offset);
}

MyStringIterator& MyStringIterator::operator-=(const difference_type offset)
{
	*(MyStringConstIterator*)this -= offset;
	return *this;
}

MyStringIterator MyStringIterator::operator-(const difference_type offset) const
{
	MyStringIterator temp = *this;
	return (temp -= offset);
}

MyStringIterator::difference_type MyStringIterator::operator-(const MyStringIterator& other) const
{
	return (*(MyStringConstIterator*)this - other);
}

MyStringIterator::reference MyStringIterator::operator[](const difference_type offset) const
{
	return *(*this + offset);
}
