#include "../../headers/string/CMyString.h"

MyString::MyString()
	: m_size(0)
	, m_ptr(std::make_unique<char[]>(1))
{
}

MyString::MyString(const char* pString)
	: m_size(std::strlen(pString))
	, m_ptr(std::make_unique<char[]>((pString[0] == 0) ? 1 : std::strlen(pString) + 1))
{
	for (size_t i = 0; i < m_size; ++i)
	{
		m_ptr[i] = pString[i];
	}
}

MyString::MyString(const char* pString, size_t length)
	: m_size(length)
	, m_ptr(std::make_unique<char[]>(length + 1))
{
	for (size_t i = 0; i < m_size; ++i)
	{
		m_ptr[i] = pString[i];
	}
}

MyString::MyString(MyString const& other)
	: MyString(other.GetStringData(), other.GetLength())
{
}

MyString::MyString(MyString&& other)
	: m_size(0)
	, m_ptr(nullptr)
{
	std::swap(m_size, other.m_size);
	std::swap(m_ptr, other.m_ptr);
}

MyString::MyString(std::string const& stlString)
	: m_size(stlString.size())
	, m_ptr(std::make_unique<char[]>(stlString.size() + 1))
{
	for (size_t i = 0; i < m_size; ++i)
	{
		m_ptr[i] = stlString[i];
	}
}

size_t MyString::GetLength() const
{
	return m_size;
}

const char* MyString::GetStringData() const
{
	return m_ptr.get();
}

MyString MyString::SubString(size_t start, size_t length) const
{
	if (start > m_size)
	{
		return MyString();
	}

	return MyString(m_ptr.get() + start, (length > m_size - start) ? m_size - start : length);
}

void MyString::Clear()
{
	m_ptr.reset();
	m_ptr = std::make_unique<char[]>(1);
	m_size = 0;
}

void MyString::operator=(const MyString& other)
{
	m_size = other.m_size;
	m_ptr.reset();
	m_ptr = std::make_unique<char[]>(m_size);
	for (size_t i = 0; i <= m_size; ++i)
	{
		m_ptr[i] = other[i];
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
		newStr[i] = (*this)[i];
	}
	for (size_t i = thisStrLength; i < newStrSize; ++i)
	{
		newStr[i] = other[i - otherStrLength];
	}
	newStr[newStrSize] = 0;

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
		newStr[i] = mStrFirst[i];
	}
	for (size_t i = firstStrLength; i < newStrSize; ++i)
	{
		newStr[i] = strSecond[i - secondStrLength];
	}
	newStr[newStrSize] = 0;

	return newStr;
}

MyString operator+(const std::string& strFirst, const MyString& mStrSecond)
{
	size_t firstStrLength = strFirst.size(), secondStrLength = mStrSecond.GetLength();

	bool overflow = (size_t)-1 - firstStrLength < secondStrLength;
	size_t newStrSize = overflow ? (size_t)-1 : firstStrLength + secondStrLength;
	MyString newStr("", newStrSize);

	for (size_t i = 0; i < firstStrLength; ++i)
	{
		newStr[i] = strFirst[i];
	}
	for (size_t i = firstStrLength; i < newStrSize; ++i)
	{
		newStr[i] = mStrSecond[i - secondStrLength];
	}
	newStr[newStrSize] = 0;

	return newStr;
}

MyString operator+(const MyString& mStrFirst, const char* strSecond)
{
	size_t firstStrLength = mStrFirst.GetLength(), secondStrLength = std::strlen(strSecond);

	bool overflow = (size_t)-1 - firstStrLength < secondStrLength;
	size_t newStrSize = overflow ? (size_t)-1 : firstStrLength + secondStrLength;
	MyString newStr("", newStrSize);

	for (size_t i = 0; i < firstStrLength; ++i)
	{
		newStr[i] = mStrFirst[i];
	}
	for (size_t i = firstStrLength; i < newStrSize; ++i)
	{
		newStr[i] = strSecond[i - secondStrLength];
	}
	newStr[newStrSize] = 0;

	return newStr;
}

MyString operator+(const char* strFirst, const MyString& mStrSecond)
{
	size_t firstStrLength = std::strlen(strFirst), secondStrLength = mStrSecond.GetLength();

	bool overflow = (size_t)-1 - firstStrLength < secondStrLength;
	size_t newStrSize = overflow ? (size_t)-1 : firstStrLength + secondStrLength;
	MyString newStr("", newStrSize);

	for (size_t i = 0; i < firstStrLength; ++i)
	{
		newStr[i] = strFirst[i];
	}
	for (size_t i = firstStrLength; i < newStrSize; ++i)
	{
		newStr[i] = mStrSecond[i - secondStrLength];
	}
	newStr[newStrSize] = 0;

	return newStr;
}

MyString& MyString::operator+=(const MyString& other)
{
	size_t thisStrLength = this->GetLength(), otherStrLength = other.GetLength();

	bool overflow = (size_t)-1 - thisStrLength < otherStrLength;
	size_t newStrSize = overflow ? (size_t)-1 : thisStrLength + otherStrLength;

	MyString temp(this->GetStringData(), thisStrLength);
	m_size = newStrSize;
	m_ptr.reset();
	m_ptr = std::make_unique<char[]>(m_size + 1);

	for (size_t i = 0; i < temp.GetLength(); ++i)
	{
		m_ptr[i] = temp[i];
	}
	for (size_t i = thisStrLength; i < m_size; ++i)
	{
		m_ptr[i] = other[i - thisStrLength];
	}
	m_ptr[newStrSize] = 0;

	return *this;
}

bool MyString::operator==(const MyString& other) const
{
	if (GetLength() != other.GetLength())
	{
		return false;
	}
	for (size_t i = 0; i < GetLength(); ++i)
	{
		if (m_ptr[i] != other[i])
		{
			return false;
		}
	}
	return true;
}

bool MyString::operator==(const char* other) const
{
	const size_t thisStrLength = GetLength();
	if (thisStrLength < std::strlen(other))
	{
		return false;
	}
	for (size_t i = 0; i < thisStrLength; ++i)
	{
		if (m_ptr[i] != other[i])
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

bool MyString::operator<(const MyString& other) const
{
	auto it1 = begin(), end1 = end(), it2 = other.begin(), end2 = other.end();

	while (it1 != end1)
	{
		if (*it2 < *it1)
		{
			return false;
		}
		else if (*it1 < *it2)
		{
			return true;
		}
		++it1;
		++it2;
	}
	return it2 != end2;
}

bool MyString::operator>(const MyString& other) const
{
	auto it1 = begin(), end1 = end(), it2 = other.begin(), end2 = other.end();

	while (it1 != end1)
	{
		if (*it2 < *it1)
		{
			return true;
		}
		else if (*it1 < *it2)
		{
			return false;
		}
		++it1;
		++it2;
	}
	return it2 == end2;
}

bool MyString::operator<=(const MyString& other) const
{
	return !(*this > other);
}

bool MyString::operator>=(const MyString& other) const
{
	return !(*this < other);
}

char& MyString::operator[](size_t index)
{
	return m_ptr[index];
}

char MyString::operator[](size_t index) const
{
	return m_ptr[index];
}

void MyString::Assign(size_t size, char value)
{
	m_ptr.reset();
	m_size = size;
	m_ptr = std::make_unique<char[]>(m_size);
}

std::istream& operator>>(std::istream& is, MyString& str)
{
	std::istream::sentry sentry(is);
	if (!sentry)
	{
		return is;
	}

	std::string buffer;
	is >> buffer;

	size_t bufferSize = buffer.size();
	str.Assign(bufferSize + 1);
	for (size_t i = 0; i < bufferSize; i++)
	{
		str[i] = buffer[i];
	}
	str[bufferSize] = 0;

	return is;
}

std::ostream& operator<<(std::ostream& os, const MyString& str)
{
	if (os.fail() || os.bad())
	{
		return os;
	}

	for (size_t i = 0; i < str.GetLength(); ++i)
	{
		os << str[i];
	}
	return os;
}

MyStringConstIterator MyString::begin() const
{
	return MyStringConstIterator(m_ptr.get());
}

MyStringIterator MyString::begin()
{
	return MyStringIterator(m_ptr.get());
}

MyStringConstIterator MyString::end() const
{
	return MyStringConstIterator(m_ptr.get() + m_size);
}

MyStringIterator MyString::end()
{
	return MyStringIterator(m_ptr.get() + m_size);
}
