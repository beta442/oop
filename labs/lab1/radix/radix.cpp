#include <iostream>
#include <string>
#include <map>

using namespace std;

map<int, string> GenerateValueMap(const int& size)
{
	map<int, char> res{};

	char val = 65; 
	for (int i = 2; i < size; i++)
	{
		if (i <= 10)
		{
			res.insert(pair<int, char>(i, i));
		}
		else
		{
			res.insert(pair<int, char>(i, val + i - 11));
		}
	}
	for (int i = 0; i < res.size(); i++)
	{
		cout << res[i] << endl;
	}

	return res;
}

constexpr auto BASE = "source notation";
constexpr auto NEED_BASE = "destination notation";
constexpr auto VALUE = "value";

int main(int argc, char* argv[])
{
	if (argc != 4)
	{
		printf("Invalid argument count\n");
		printf("Usage: radix.exe <%s> <%s> <%s>\n", BASE, NEED_BASE, VALUE);
	}
	else
	{
		
	}

	GenerateValueMap(36);

	return EXIT_SUCCESS;
}