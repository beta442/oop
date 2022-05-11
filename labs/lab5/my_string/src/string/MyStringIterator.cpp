#include "../../headers/string/CMyStringIterator.h"

MyStringConstIterator::MyStringConstIterator()
{
}

MyStringConstIterator::MyStringConstIterator(Pointer ptr)
	: m_ptr(ptr)
{
}

MyStringConstIterator::Reference MyStringConstIterator::operator*() const
{
	return *m_ptr;
}

MyStringConstIterator::Pointer MyStringConstIterator::operator->() const
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

MyStringConstIterator& MyStringConstIterator::operator+=(const Difference offset)
{
	m_ptr += offset;
	return *this;
}

MyStringConstIterator MyStringConstIterator::operator+(const Difference offset) const
{
	MyStringConstIterator temp = *this;
	return (temp += offset);
}

MyStringConstIterator& MyStringConstIterator::operator-=(const Difference offset)
{
	m_ptr -= offset;
	return *this;
}

MyStringConstIterator MyStringConstIterator::operator-(const Difference offset) const
{
	MyStringConstIterator temp = *this;
	return (temp -= offset);
}

MyStringConstIterator::Difference MyStringConstIterator::operator-(const MyStringConstIterator& other) const
{
	return m_ptr - other.m_ptr;
}

MyStringConstIterator::Reference MyStringConstIterator::operator[](const Difference offset) const
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

MyStringIterator::MyStringIterator()
{
}

MyStringIterator::MyStringIterator(Pointer ptr)
	: MyStringConstIterator(ptr)
{
}

MyStringIterator::Reference MyStringIterator::operator*() const
{
	return MyStringConstIterator::operator*();
}

MyStringIterator::Pointer MyStringIterator::operator->() const
{
	return MyStringConstIterator::operator->();
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

MyStringIterator& MyStringIterator::operator+=(const Difference offset)
{
	*(MyStringConstIterator*)this += offset;
	return *this;
}

MyStringIterator MyStringIterator::operator+(const Difference offset) const
{
	MyStringIterator temp = *this;
	return (temp += offset);
}

MyStringIterator& MyStringIterator::operator-=(const Difference offset)
{
	*(MyStringConstIterator*)this -= offset;
	return *this;
}

MyStringIterator MyStringIterator::operator-(const Difference offset) const
{
	MyStringIterator temp = *this;
	return (temp -= offset);
}

MyStringIterator::Difference MyStringIterator::operator-(const MyStringIterator& other) const
{
	return (*(MyStringConstIterator*)this - other);
}

MyStringIterator::Reference MyStringIterator::operator[](const Difference offset) const
{
	return *(*this + offset);
}
