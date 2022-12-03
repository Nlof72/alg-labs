#include "pch.h"
#include "string.h"
#include "../Laba2/Array.cpp"
using namespace std;

TEST(Array, InsertIntNumbers)
{
	Array<int> a;
	for (int i = 0; i < 10; ++i) {
		a.Insert(i + 1);
		EXPECT_EQ(a[i], i+1);
	}

	EXPECT_EQ(a.Size(), 10);
}

TEST(Array, InsertConstIntNumbers)
{
	Array<int> a;
	for (int i = 0; i < 10; ++i) {
		const int temp = i + 1;
		a.Insert(temp);
		EXPECT_EQ(a[i], i + 1);
	}

	EXPECT_EQ(a.Size(), 10);
}

TEST(Array, Iterator) 
{
	Array<int> a;
	Array<int> b;
	for (int i = 0; i < 20; ++i) {
		a.Insert(i + 1);
	}

	for (auto it = a.Iterator(); it.HasNext(); it.Next())
		b.Insert(it.Get());

	for (size_t i = 0; i < b.Size(); i++)
	{
		EXPECT_EQ(a[i], b[i]);
	}
	EXPECT_EQ(a.Size(), b.Size());
}

TEST(Array, ReverseIterator) 
{
	Array<int> a;
	Array<int> b;
	for (int i = 0; i < 10; ++i) {
		a.Insert(i + 1);
	}

	for (auto it = a.ReverseIterator(); it.HasNext(); it.Next())
		b.Insert(it.Get());
	for (size_t i = 0; i < b.Size(); i++)
	{
		EXPECT_EQ(a[i], b[b.Size()-i-1]);
	}
	EXPECT_EQ(a.Size(), b.Size());
}

TEST(Array, RemoveElement) 
{
	Array<int> a;

	for (int i = 0; i < 10; ++i) {
		a.Insert(i + 1);
	}

	for (int i = 9; i >= 0; i--) {
		a.Remove(i);
	}

	
	EXPECT_EQ(a.Size(), 0);
}

TEST(Array, InsertStringItems)
{
	Array<string> a;

	for (int i = 0; i < 10; ++i) {
		a.Insert("iIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIiIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIiIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIiIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII");
		EXPECT_EQ(a[i], "iIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIiIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIiIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIiIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII");
	}

	EXPECT_EQ(a.Size(), 10);
}