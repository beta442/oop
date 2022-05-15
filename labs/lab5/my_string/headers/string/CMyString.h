#pragma once

#include <string>

#include "CMyStringIterator.h"

class MyString
{
public:
	using ConstIterator = MyStringConstIterator;
	using Iterator = MyStringIterator;
	using ConstReverseIterator = ConstIterator::MyStringConstReverseIterator;
	using ReverseIterator = Iterator::MyStringReverseIterator;

public:
	MyString();
	MyString(const char* pString);
	MyString(const char* pString, size_t length);
	MyString(MyString const& other);
	MyString(MyString&& other);
	MyString(std::string const& stlString);

	ConstIterator begin() const;
	Iterator begin();
	ConstReverseIterator rbegin() const;
	ReverseIterator rbegin();
	ConstIterator end() const;
	Iterator end();
	ConstReverseIterator rend() const;
	ReverseIterator rend();
	size_t GetLength() const;
	const char* GetStringData() const;
	MyString SubString(size_t start, size_t length = SIZE_MAX) const;
	void Clear();

	MyString& operator=(const MyString& other);
	MyString& operator=(MyString&& other);
	MyString operator+(const MyString& other) const;
	friend MyString operator+(const MyString& mStrFirst, const std::string& strSecond);
	friend MyString operator+(const std::string& strFirst, const MyString& mStrSecond);
	friend MyString operator+(const MyString& mStrFirst, const char* strSecond);
	friend MyString operator+(const char* strFirst, const MyString& mStrSecond);
	MyString& operator+=(const MyString& other);
	bool operator==(const MyString& other) const;
	bool operator==(const char* other) const;
	bool operator!=(const MyString& other) const;
	bool operator!=(const char* other) const;
	bool operator<(const MyString& other) const;
	bool operator<=(const MyString& other) const;
	bool operator>(const MyString& other) const;
	bool operator>=(const MyString& other) const;
	const char& operator[](size_t index) const;
	char& operator[](size_t index);
	friend std::istream& operator>>(std::istream& is, MyString& str);
	friend std::ostream& operator<<(std::ostream& os, const MyString& str);

private:
	void Assign(size_t size, char value = 0);

	size_t m_size;
	std::unique_ptr<char[]> m_ptr;
};
