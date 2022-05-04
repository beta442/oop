#include "headers/stdafx.h"

#include "headers/string/CMyString.h"

int main()
{
	{
		const char* some = new char[10]{ '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
		std::cout << some << "." << std::endl;
		MyString str(some);
		std::cout << str.GetLength() << std::endl;
	}

	{
		const char* some = new char[0]{};
		std::cout << some << ". Length is: " << std::strlen(some) << std::endl;
		MyString str(some, 10);
		std::cout << str.GetLength() << std::endl;
	}
}
