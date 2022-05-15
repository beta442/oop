#include "headers/pch.h"

#include "headers/StringList/CStringList.h"

int main()
{
	StringList list{};
	list.PushBack("haha1");
	list.PushBack("haha2");
	list.PushFront("001");
	list.PushFront("002");
	list.Clear();
	return 0;
}
