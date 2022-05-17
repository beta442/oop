//#include "../../headers/StringList/CStringListIterator.h"
//
//ListConstIterator::ListConstIterator(pointer ptr)
//	: m_ptr(ptr)
//{
//}
//
//ListConstIterator::reference_val ListConstIterator::operator*() const
//{
//	return m_ptr->m_data;
//}
//
//const std::string& ListConstIterator::operator->() const
//{
//	return m_ptr->m_data;
//}
//
//ListConstIterator& ListConstIterator::operator++()
//{
//	++m_ptr;
//	return *this;
//}
//
//ListConstIterator ListConstIterator::operator++(int)
//{
//	ListConstIterator temp(*this);
//	++*this;
//	return temp;
//}
//
//ListConstIterator& ListConstIterator::operator--()
//{
//	--m_ptr;
//	return *this;
//}
//
//ListConstIterator ListConstIterator::operator--(int)
//{
//	ListConstIterator temp(*this);
//	--*this;
//	return temp;
//}
//
//ListConstIterator& ListConstIterator::operator+=(const difference_type offset)
//{
//	m_ptr += offset;
//	return *this;
//}
//
//ListConstIterator ListConstIterator::operator+(const difference_type offset) const
//{
//	ListConstIterator temp = *this;
//	return (temp += offset);
//}
//
//ListConstIterator& ListConstIterator::operator-=(const difference_type offset)
//{
//	m_ptr -= offset;
//	return *this;
//}
//
//ListConstIterator ListConstIterator::operator-(const difference_type offset) const
//{
//	ListConstIterator temp = *this;
//	return (temp -= offset);
//}
//
//ListConstIterator::difference_type ListConstIterator::operator-(const ListConstIterator& other) const
//{
//	return m_ptr - other.m_ptr;
//}
//
//ListConstIterator::reference ListConstIterator::operator[](const difference_type offset) const
//{
//	return *(*this + offset);
//}
//
//bool ListConstIterator::operator==(const ListConstIterator& other) const
//{
//	return m_ptr == other.m_ptr;
//}
//
//bool ListConstIterator::operator!=(const ListConstIterator& other) const
//{
//	return !(*this == other);
//}
//
//bool ListConstIterator::operator<(const ListConstIterator& other) const
//{
//	return m_ptr < other.m_ptr;
//}
//
//bool ListConstIterator::operator>(const ListConstIterator& other) const
//{
//	return m_ptr > other.m_ptr;
//}
//
//bool ListConstIterator::operator<=(const ListConstIterator& other) const
//{
//	return !(other < *this);
//}
//
//bool ListConstIterator::operator>=(const ListConstIterator& other) const
//{
//	return !(*this < other);
//}
//
///*-------------------------------------------------------------------------------------------------------------------*/
//
//ListIterator::ListIterator(pointer ptr)
//	: ListConstIterator(ptr)
//{
//}
//
//ListIterator::reference ListIterator::operator*() const
//{
//	return const_cast<reference>(ListConstIterator::operator*());
//}
//
//ListIterator::pointer ListIterator::operator->() const
//{
//	return const_cast<pointer>(ListConstIterator::operator->());
//}
//
//ListIterator& ListIterator::operator++()
//{
//	++*(ListConstIterator*)this;
//	return *this;
//}
//
//ListIterator ListIterator::operator++(int)
//{
//	ListIterator temp = *this;
//	++*this;
//	return temp;
//}
//
//ListIterator& ListIterator::operator--()
//{
//	--*(ListConstIterator*)this;
//	return *this;
//}
//
//ListIterator ListIterator::operator--(int)
//{
//	ListIterator temp = *this;
//	--*this;
//	return temp;
//}
//
//ListIterator& ListIterator::operator+=(const difference_type offset)
//{
//	*(ListConstIterator*)this += offset;
//	return *this;
//}
//
//ListIterator ListIterator::operator+(const difference_type offset) const
//{
//	ListIterator temp = *this;
//	return (temp += offset);
//}
//
//ListIterator& ListIterator::operator-=(const difference_type offset)
//{
//	*(ListConstIterator*)this -= offset;
//	return *this;
//}
//
//ListIterator ListIterator::operator-(const difference_type offset) const
//{
//	ListIterator temp = *this;
//	return (temp -= offset);
//}
//
//ListIterator::difference_type ListIterator::operator-(const ListIterator& other) const
//{
//	return (*(ListConstIterator*)this - other);
//}
//
//ListIterator::reference ListIterator::operator[](const difference_type offset) const
//{
//	return *(*this + offset);
//}
