#pragma once

#include <string>

class MyString
{
public:
	MyString();
	MyString(const char* pString);
	MyString(const char* pString, size_t length);
	MyString(MyString const& other);
	// ������������ ����������� (��� ������������, ����������� � C++11)
	// ����������� ��������� � ������������ ���������� ������������
	MyString(MyString&& other);
	// �����������, ���������������� ������ ������� ��
	// ������ ����������� ���������� C++
	MyString(std::string const& stlString);
	size_t GetLength() const;
	// ���������� ��������� �� ������ �������� ������.
	// � ����� ������� ����������� ������ ���� ����������� ������� ������
	// ���� ���� ������ ������
	const char* GetStringData() const;
	MyString SubString(size_t start, size_t length = SIZE_MAX) const;
	void Clear();

private:
	size_t m_size;
	std::unique_ptr<char[]> m_beginPtr;
};
