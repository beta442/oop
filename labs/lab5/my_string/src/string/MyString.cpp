#include "../../headers/string/CMyString.h"

MyString::MyString()
	: m_size(0)
	, m_ptr(std::make_unique<char[]>(1))
{
	m_ptr[0] = 0;
}

MyString::MyString(const char* pString)
	: m_size(std::strlen(pString))
	, m_ptr(std::make_unique<char[]>(std::strlen(pString) + 1))
{
	std::memcpy(m_ptr.get(), pString, m_size);
	m_ptr[m_size] = 0;
}

MyString::MyString(const char* pString, size_t length)
	: m_size(length)
	, m_ptr(std::make_unique<char[]>(length + 1))
{
	std::memcpy(m_ptr.get(), pString, m_size);
	m_ptr[m_size] = 0;
}

MyString::MyString(MyString const& other)
	: MyString(other.GetStringData(), other.GetLength())
{
}

MyString::MyString(MyString&& other) noexcept
	: m_size(0)
	, m_ptr(nullptr)
{
	std::swap(m_size, other.m_size);
	std::swap(m_ptr, other.m_ptr);
}

MyString::MyString(std::string const& stlString)
	: MyString(stlString.c_str(), stlString.size())
{
}

size_t MyString::GetLength() const
{
	return m_size;
}

static inline const auto DEFAULT_VALUE = '\0';

const char* MyString::GetStringData() const
{
	return m_size == 0 ? &DEFAULT_VALUE : m_ptr.get();
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
	m_size = 0;
}

MyString& MyString::operator=(const MyString& other)
{
	if (std::addressof(other) != this)
	{
		MyString temp(other);
		std::swap(m_size, temp.m_size);
		std::swap(m_ptr, temp.m_ptr);
	}
	return *this;
}

MyString& MyString::operator=(MyString&& other) noexcept
{
	if (&other != this)
	{
		m_ptr = nullptr;
		m_size = 0;
		std::swap(m_size, other.m_size);
		std::swap(m_ptr, other.m_ptr);
	}
	return *this;
}

MyString MyString::operator+(const MyString& other) const
{
	size_t thisStrLength = this->GetLength(), otherStrLength = other.GetLength();

	bool overflow = std::numeric_limits<size_t>::max() - thisStrLength < otherStrLength;
	size_t newStrSize = overflow ? std::numeric_limits<size_t>::max() - 1 : thisStrLength + otherStrLength;

	MyString newStr{};
	newStr.Resize(newStrSize);

	std::memcpy(newStr.m_ptr.get(), m_ptr.get(), thisStrLength);
	std::memcpy(newStr.m_ptr.get() + thisStrLength, other.GetStringData(), otherStrLength);
	newStr[newStrSize] = 0;

	return newStr;
}

MyString operator+(const MyString& mStrFirst, const std::string& strSecond)
{
	return mStrFirst + MyString(strSecond);
}

MyString operator+(const std::string& strFirst, const MyString& mStrSecond)
{
	return MyString(strFirst) + mStrSecond;
}

MyString operator+(const MyString& mStrFirst, const char* strSecond)
{
	return mStrFirst + MyString(strSecond);
}

MyString operator+(const char* strFirst, const MyString& mStrSecond)
{
	return MyString(strFirst) + mStrSecond;
}

MyString& MyString::operator+=(const MyString& other)
{
	*this = *this + other;

	return *this;
}

bool MyString::operator==(const MyString& other) const
{
	return std::equal(begin(), end(), other.begin(), other.end());
}

bool MyString::operator==(const char* other) const
{
	return std::equal(begin(), end(), other, other + GetLength());
}

bool MyString::operator!=(const MyString& other) const
{
	return !(*this == other);
}

bool MyString::operator!=(const char* other) const
{
	return !(*this == other);
}

bool MyString::operator<(const MyString& other) const
{
	return std::lexicographical_compare(begin(), end(), other.begin(), other.end());
}

bool MyString::operator>(const MyString& other) const
{
	return other < *this;
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
	if (index > m_size)
	{
		throw std::out_of_range("Failed to return char reference. Index is out of range");
	}
	return m_ptr[index];
}

const char& MyString::operator[](size_t index) const
{
	if (index > m_size)
	{
		throw std::out_of_range("Failed to return const char reference. Index is out of range");
	}
	return m_ptr[index];
}

void MyString::Resize(size_t size)
{
	m_ptr.reset();
	m_size = size;
	m_ptr = std::make_unique<char[]>(m_size + 1);
	m_ptr[m_size] = 0;
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

	str = MyString(buffer);

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

using ConstIterator = MyString::ConstIterator;
using Iterator = MyString::Iterator;
using ConstReverseIterator = MyString::ConstReverseIterator;
using ReverseIterator = MyString::ReverseIterator;

ConstIterator MyString::begin() const
{
	return ConstIterator(m_ptr.get());
}

Iterator MyString::begin()
{
	return Iterator(m_ptr.get());
}

ConstReverseIterator MyString::rbegin() const
{
	return std::make_reverse_iterator(end());
}

ReverseIterator MyString::rbegin()
{
	return std::make_reverse_iterator(end());
}

ConstIterator MyString::end() const
{
	return ConstIterator(m_ptr.get() + m_size);
}

Iterator MyString::end()
{
	return Iterator(m_ptr.get() + m_size);
}

ConstReverseIterator MyString::rend() const
{
	return std::make_reverse_iterator(begin());
}

ReverseIterator MyString::rend()
{
	return std::make_reverse_iterator(begin());
}
