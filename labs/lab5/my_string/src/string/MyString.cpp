#include "../../headers/string/CMyString.h"

#include <iostream>

MyString::MyString()
	: m_size(0)
	, m_beginPtr(new char[0])
{
}

MyString::MyString(const char* pString)
	: m_size(std::strlen(pString))
	, m_beginPtr(new char[std::strlen(pString)])
{
	std::memcpy(m_beginPtr, pString, std::strlen(pString));
}

MyString::MyString(const char* pString, size_t length)
	: m_size(length)
	, m_beginPtr(new char[length])
{
	for (size_t i = 0; i < length; ++i)
	{
		m_beginPtr[i] = pString[i];
	}
}

MyString::MyString(MyString const& other)
{
}

MyString::MyString(MyString&& other)
{
}

MyString::MyString(std::string const& stlString)
{
}

MyString::~MyString()
{
	std::cout << "Destructor called!" << std::endl;
	delete [] m_beginPtr;
}

size_t MyString::GetLength() const
{
	return m_size;
}

const char* MyString::GetStringData() const
{
	return m_beginPtr;
}

MyString MyString::SubString(size_t start, size_t length) const
{
	return MyString();
}

void MyString::Clear()
{
}
