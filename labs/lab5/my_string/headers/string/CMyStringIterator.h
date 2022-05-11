#pragma once

#include <cstddef>

class MyStringConstIterator
{
public:
	using Difference = ptrdiff_t;
	using Value = char;
	using Pointer = Value*;
	using Reference = Value&;

public:
	MyStringConstIterator();
	MyStringConstIterator(Pointer ptr);

	Reference operator*() const;
	Pointer operator->() const;
	MyStringConstIterator& operator++();
	MyStringConstIterator operator++(int);
	MyStringConstIterator& operator--();
	MyStringConstIterator operator--(int);
	MyStringConstIterator& operator+=(const Difference offset);
	MyStringConstIterator operator+(const Difference offset) const;
	MyStringConstIterator& operator-=(const Difference offset);
	MyStringConstIterator operator-(const Difference offset) const;
	Difference operator-(const MyStringConstIterator& other) const;
	Reference operator[](const Difference offset) const;
	bool operator==(const MyStringConstIterator& other) const;
	bool operator!=(const MyStringConstIterator& other) const;
	bool operator<(const MyStringConstIterator& other) const;
	bool operator>(const MyStringConstIterator& other) const;
	bool operator<=(const MyStringConstIterator& other) const;
	bool operator>=(const MyStringConstIterator& other) const;

private:
	Pointer m_ptr;
};

class MyStringIterator : public MyStringConstIterator
{
public:
	MyStringIterator();
	MyStringIterator(Pointer ptr);

	Reference operator*() const;
	Pointer operator->() const;
	MyStringIterator& operator++();
	MyStringIterator operator++(int);
	MyStringIterator& operator--();
	MyStringIterator operator--(int);
	MyStringIterator& operator+=(const Difference offset);
	MyStringIterator operator+(const Difference offset) const;
	MyStringIterator& operator-=(const Difference offset);
	MyStringIterator operator-(const Difference offset) const;
	Difference operator-(const MyStringIterator& other) const;
	Reference operator[](const Difference offset) const;
};
