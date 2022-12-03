#include "pch.h"
#include "../laba3/SortFunctions.cpp"

const int ch_MAX = 26;
std::string RandomString(int ch)
{
	char alpha[ch_MAX] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g',
						  'h', 'i', 'j', 'k', 'l', 'm', 'n',
						  'o', 'p', 'q', 'r', 's', 't', 'u',
						  'v', 'w', 'x', 'y', 'z' };
	std::string result = "";
	for (int i = 0; i < ch; i++)
		result = result + alpha[rand() % ch_MAX];

	return result;
}

TEST(ArraySortInsert, InsertIntNumbers) {
	int* innerArray = new int[32];

	for (int i = 0; i < 32; i++)
	{
		innerArray[i] = 31 - i;
	}

	//PrintArray(innerArray, innerArray + 32);

	InsertSort(innerArray, innerArray + 31, [](int a, int b) { return a < b; });

	for (size_t i = 0; i < 32; i++)
	{
		EXPECT_EQ(innerArray[i], i);
	}
}

TEST(ArraySortInsert, InsertStringNumbers) {
	std::string* innerArray = new std::string[32];

	for (int i = 0; i < 32; i++)
	{
		innerArray[i] = RandomString(i + 1);
	}

	//PrintArray(innerArray, innerArray + 32);

	InsertSort(innerArray, innerArray + 31, [](std::string a, std::string b) { return a.length() < b.length(); });

	for (int i = 0; i < 32; i++)
	{
		EXPECT_EQ(innerArray[i].length(), i + 1);
	}
}


TEST(ArraySortQuick, InsertIntNumbers) 
{
	int* innerArray = new int[32];

	for (int i = 0; i < 32; i++)
	{
		innerArray[i] = 31 - i;
	}

	//PrintArray(innerArray, innerArray + 32);

	OptimazedQuicSort(innerArray, innerArray + 31, [](int a, int b) { return a < b; });

	for (int i = 0; i < 32; i++)
	{
		EXPECT_EQ(innerArray[i], i);
	}
}

TEST(ArraySortQuick, InsertStringNumbers) 
{
	std::string* innerArray = new std::string[32];

	for (int i = 0; i < 32; i++)
	{
		innerArray[i] = RandomString(i + 1);
	}

	//PrintArray(innerArray, innerArray + 32);

	OptimazedQuicSort(innerArray, innerArray + 31, [](std::string a, std::string b) { return a.length() < b.length(); });

	for (int i = 0; i < 32; i++)
	{
		EXPECT_EQ(innerArray[i].length(), i + 1);
	}
}