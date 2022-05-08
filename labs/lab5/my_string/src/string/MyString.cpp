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
		m_beginPtr[i] = i < std::strlen(pString) ? pString[i] : 0;
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
	: m_size(0)
	, m_beginPtr(nullptr)
{
	*this = std::move(other);
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

void MyString::operator=(const MyString& other)
{
	m_size = other.m_size;
	m_beginPtr.reset();
	m_beginPtr = std::make_unique<char[]>(m_size);
	for (size_t i = 0; i < m_size; ++i)
	{
		m_beginPtr[i] = other.GetStringData()[i];
	}
}

MyString MyString::operator+(const MyString& other) const
{
	size_t thisStrLength = this->GetLength(), otherStrLength = other.GetLength();

	bool overflow = (size_t)-1 - thisStrLength < otherStrLength;
	size_t newStrSize = overflow ? (size_t)-1 : thisStrLength + otherStrLength;
	MyString newStr("", newStrSize);

	for (size_t i = 0; i < thisStrLength; ++i)
	{
		newStr.m_beginPtr[i] = this->m_beginPtr[i];
	}
	for (size_t i = thisStrLength; i < newStrSize; ++i)
	{
		newStr.m_beginPtr[i] = other.m_beginPtr[i - otherStrLength];
	}

	return newStr;
}

MyString operator+(const MyString& mStrFirst, const std::string& strSecond)
{
	size_t firstStrLength = mStrFirst.GetLength(), secondStrLength = strSecond.size();

	bool overflow = (size_t)-1 - firstStrLength < secondStrLength;
	size_t newStrSize = overflow ? (size_t)-1 : firstStrLength + secondStrLength;
	MyString newStr("", newStrSize);

	for (size_t i = 0; i < firstStrLength; ++i)
	{
		newStr.m_beginPtr[i] = mStrFirst.m_beginPtr[i];
	}
	for (size_t i = firstStrLength; i < newStrSize; ++i)
	{
		newStr.m_beginPtr[i] = strSecond[i - secondStrLength];
	}

	return newStr;
}

MyString operator+(const std::string& strFirst, const MyString& mStrSecond)
{
	return mStrSecond + strFirst;
}

MyString operator+(const MyString& mStrFirst, const char* strSecond)
{
	size_t firstStrLength = mStrFirst.GetLength(), secondStrLength = std::strlen(strSecond);

	bool overflow = (size_t)-1 - firstStrLength < secondStrLength;
	size_t newStrSize = overflow ? (size_t)-1 : firstStrLength + secondStrLength;
	MyString newStr("", newStrSize);

	for (size_t i = 0; i < firstStrLength; ++i)
	{
		newStr.m_beginPtr[i] = mStrFirst.m_beginPtr[i];
	}
	for (size_t i = firstStrLength; i < newStrSize; ++i)
	{
		newStr.m_beginPtr[i] = strSecond[i - secondStrLength];
	}

	return newStr;
}

MyString operator+(const char* strFirst, const MyString& mStrSecond)
{
	return mStrSecond + strFirst;
}

void MyString::operator+=(const MyString& other)
{
	size_t thisStrLength = this->GetLength(), otherStrLength = other.GetLength();

	bool overflow = (size_t)-1 - thisStrLength < otherStrLength;
	size_t newStrSize = overflow ? (size_t)-1 : thisStrLength + otherStrLength;

	MyString temp(this->GetStringData(), thisStrLength);
	m_size = newStrSize;
	m_beginPtr.reset();
	m_beginPtr = std::make_unique<char[]>(m_size);

	for (size_t i = 0; i < temp.GetLength(); ++i)
	{
		m_beginPtr[i] = temp.m_beginPtr[i];
	}
	for (size_t i = thisStrLength; i < m_size; ++i)
	{
		m_beginPtr[i] = other.m_beginPtr[i - thisStrLength];
	}
}

bool MyString::operator==(const MyString& other) const
{
	if (GetLength() != other.GetLength())
	{
		return false;
	}
	for (size_t i = 0; i < GetLength(); ++i)
	{
		if (m_beginPtr[i] != other.m_beginPtr[i])
		{
			return false;
		}
	}
	return true;
}

bool MyString::operator!=(const MyString& other) const
{
	return !(*this == other);
}
