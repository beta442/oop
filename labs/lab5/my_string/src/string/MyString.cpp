#include "../../headers/string/CMyString.h"

MyString::MyString()
	: m_size(0)
	, m_beginPtr(std::make_unique<char[]>({}))
{
}

MyString::MyString(const char* pString)
	: m_size(std::strlen(pString))
	, m_beginPtr(std::make_unique<char[]>(std::strlen(pString)))
{
	for (size_t i = 0; i < m_size; ++i)
	{
		m_beginPtr[i] = pString[i];
	}
}

MyString::MyString(const char* pString, size_t length)
	: m_size(length)
	, m_beginPtr(std::make_unique<char[]>(length))
{
	for (size_t i = 0; i < m_size; ++i)
	{
		m_beginPtr[i] = pString[i];
	}
}

MyString::MyString(MyString const& other)
	: m_size(other.GetLength())
	, m_beginPtr(std::make_unique<char[]>(other.GetLength()))
{
	for (size_t i = 0; i < m_size; ++i)
	{
		m_beginPtr[i] = other.m_beginPtr[i];
	}
}

MyString::MyString(MyString&& other)
{
}

MyString::MyString(std::string const& stlString)
	: m_size(stlString.size())
	, m_beginPtr(std::make_unique<char[]>(stlString.size()))
{
	for (size_t i = 0; i < m_size; ++i)
	{
		m_beginPtr[i] = stlString[i];
	}
}

size_t MyString::GetLength() const
{
	return m_size;
}

const char* MyString::GetStringData() const
{
	return m_beginPtr.get();
}

MyString MyString::SubString(size_t start, size_t length) const
{
	if (start > m_size)
	{
		return MyString();
	}

	return MyString(m_beginPtr.get() + start, (start + length > m_size) ? m_size - start : length);
}

void MyString::Clear()
{
	m_beginPtr.reset();
	m_beginPtr = std::make_unique<char[]>(0);
	m_size = 0;
}
