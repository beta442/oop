//#pragma once
//
//#include <cstddef>
//#include <iterator>
//
//#include "CStringListNode.h"
//
//class ListConstIterator
//{
//public:
//	using iterator_category = std::random_access_iterator_tag;
//
//	using difference_type = ptrdiff_t;
//	using value_type = const ListNode<std::string>;
//	using pointer = value_type*;
//	using reference = value_type&;
//
//	using pointer_val = std::string* const;
//	using reference_val = const std::string&;
//
//	using ListConstReverseIterator = std::reverse_iterator<ListConstIterator>;
//
//public:
//	ListConstIterator(pointer ptr);
//
//	reference_val operator*() const;
//	const std::string& operator->() const;
//	ListConstIterator& operator++();
//	ListConstIterator operator++(int);
//	ListConstIterator& operator--();
//	ListConstIterator operator--(int);
//	ListConstIterator& operator+=(const difference_type offset);
//	ListConstIterator operator+(const difference_type offset) const;
//	ListConstIterator& operator-=(const difference_type offset);
//	ListConstIterator operator-(const difference_type offset) const;
//	difference_type operator-(const ListConstIterator& other) const;
//	reference_val operator[](const difference_type offset) const;
//	bool operator==(const ListConstIterator& other) const;
//	bool operator!=(const ListConstIterator& other) const;
//	bool operator<(const ListConstIterator& other) const;
//	bool operator>(const ListConstIterator& other) const;
//	bool operator<=(const ListConstIterator& other) const;
//	bool operator>=(const ListConstIterator& other) const;
//
//private:
//	pointer m_ptr;
//};
//
//class ListIterator : public ListConstIterator
//{
//public:
//	using difference_type = ptrdiff_t;
//	using value_type = ListNode<std::string>;
//	using pointer = value_type*;
//	using reference = value_type&;
//
//	using ListReverseIterator = std::reverse_iterator<ListIterator>;
//
//	ListIterator(pointer ptr);
//
//	reference operator*() const;
//	pointer operator->() const;
//	ListIterator& operator++();
//	ListIterator operator++(int);
//	ListIterator& operator--();
//	ListIterator operator--(int);
//	ListIterator& operator+=(const difference_type offset);
//	ListIterator operator+(const difference_type offset) const;
//	ListIterator& operator-=(const difference_type offset);
//	ListIterator operator-(const difference_type offset) const;
//	difference_type operator-(const ListIterator& other) const;
//	reference operator[](const difference_type offset) const;
//};
