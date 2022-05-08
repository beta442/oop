#pragma once

#include <string>

class MyString
{
public:
	MyString();
	MyString(const char* pString);
	MyString(const char* pString, size_t length);
	MyString(MyString const& other);
	// перемещающий конструктор (для компиляторов, совместимых с C++11)
	// реализуется совместно с перемещающим оператором присваивания
	MyString(MyString&& other);
	// конструктор, инициализирующий строку данными из
	// строки стандартной библиотеки C++
	MyString(std::string const& stlString);
	size_t GetLength() const;
	// возвращает указатель на массив символов строки.
	// В конце массива обязательно должен быть завершающий нулевой символ
	// даже если строка пустая
	const char* GetStringData() const;
	MyString SubString(size_t start, size_t length = SIZE_MAX) const;
	void Clear();

	void operator=(const MyString& other);
	MyString operator+(const MyString& other) const;
	friend MyString operator+(const MyString& mStrFirst, const std::string& strSecond);
	friend MyString operator+(const std::string& strFirst, const MyString& mStrSecond);
	friend MyString operator+(const MyString& mStrFirst, const char* strSecond);
	friend MyString operator+(const char* strFirst, const MyString& mStrSecond);
	void operator+=(const MyString& other);
	bool operator==(const MyString& other) const;
	bool operator!=(const MyString& other) const;

private:
	size_t m_size;
	std::unique_ptr<char[]> m_beginPtr;
};
