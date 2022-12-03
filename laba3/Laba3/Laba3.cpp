#include <iostream>
#include <fstream>
#include <Windows.h>
#include <chrono>
#include "./SortFunctions.cpp"

constexpr int TEST_SIZE = 1000;
constexpr int PREPARE_EXP = 1000;
constexpr int REPEAT_TIMES = 10000;
constexpr int MAX_ELEMENT_COUNT = 50;

template <typename Func>
void TestFuncTime(int elementsCount, Func sortFunc) 
{
	int stime;
	long ltime;

	ltime = time(NULL);
	stime = (unsigned int)ltime / 2;
	srand(stime);

	int* innerArray;
	int* innerArray1;

	auto summ1 = 0;
	auto summ2 = 0;
	auto begin1 = std::chrono::steady_clock::now();
	auto begin2 = std::chrono::steady_clock::now();
	auto end1 = std::chrono::steady_clock::now();
	auto end2 = std::chrono::steady_clock::now();
	auto timeNano1 = std::chrono::duration_cast<std::chrono::nanoseconds>(end1 - begin1);
	auto timeNano2 = std::chrono::duration_cast<std::chrono::nanoseconds>(end2 - begin2);

	std::ofstream fileInsertSort("insert.txt");
	std::ofstream fileQuickSort("Quick.txt");

	for (int i = 1; i <= elementsCount; i++)
	{
		for (int j = 0; j < REPEAT_TIMES; j++)
		{
			innerArray = new int[i];
			innerArray1 = new int[i];

			for (int k = 0; k < i; k++)
			{
				innerArray[k] = i - k - 1;
				innerArray1[k] = rand() % elementsCount;
			}

			//PrintArray(innerArray, innerArray + i - 1);

			begin1 = std::chrono::steady_clock::now();
			InsertSort(innerArray, innerArray + i - 1, [](int a, int b) { return a < b; });
			end1 = std::chrono::steady_clock::now();

			timeNano1 = std::chrono::duration_cast<std::chrono::nanoseconds>(end1 - begin1);
			summ1 += timeNano1.count();

			begin2 = std::chrono::steady_clock::now();
			OptimazedQuicSort(innerArray1, innerArray1 + i - 1, [](int a, int b) { return a < b; });
			end2 = std::chrono::steady_clock::now();

			timeNano2 = std::chrono::duration_cast<std::chrono::nanoseconds>(end2 - begin2);
			summ2 += timeNano2.count();

			//PrintArray(innerArray1, innerArray1 + i - 1);
			//std::cout << summ1 << " " << summ2 << "\n";

			delete[] innerArray;
			delete[] innerArray1;
		}

		if (fileInsertSort.is_open())
			fileInsertSort << summ1 / REPEAT_TIMES << "\n";
		if (fileQuickSort.is_open())
			fileQuickSort << summ2 / REPEAT_TIMES << "\n";
		//std::cout << summ1/REPEAT_TIMES << " " << summ2/REPEAT_TIMES << "\n";
	}

	fileInsertSort.close();
	fileQuickSort.close();
}

int main()
{
	int* a = new int[TEST_SIZE];

	for (int i = 0; i < PREPARE_EXP; i++)
	{
		for (size_t j = 0; j < TEST_SIZE; j++)
		{
			a[j] = TEST_SIZE - j;
		}
		InsertSort(a, a + TEST_SIZE-1, [](int a, int b) { return a < b; });
	}

	delete[] a;

	//std::cout << "InsertSort" << "\n\n";
	TestFuncTime( MAX_ELEMENT_COUNT, [](int* start, int end) { InsertSort(start, start + end - 1, [](int a, int b) { return a < b; }); });

}