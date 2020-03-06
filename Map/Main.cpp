#include <iostream>
#include <map>
#include <conio.h>
#include <vector>
#include <Windows.h>
#include <algorithm>
#include "stdlib.h" 
#include <time.h>  


using namespace std;

#include "Mallocator.h"

struct word
{
	char* ptr;
	size_t len;
};

struct cmpByChar
{
	bool operator()(const char* a, const char* b) const
	{
		return strcmp(a, b) == -1;
	}
};

int main()
{
	auto hFile = CreateFile("source.txt", GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	LARGE_INTEGER lFileSize;
	GetFileSizeEx(hFile, &lFileSize);
	char* ReadBuffer = new char[lFileSize.QuadPart + 1];


	DWORD nRead;
	if (FALSE == ReadFile(hFile, ReadBuffer, lFileSize.QuadPart, &nRead, NULL))
	{
		printf("Terminal failure: Unable to read from file.\n GetLastError=%08x\n", GetLastError());
		CloseHandle(hFile);

		delete ReadBuffer;
		return 0;
	}
	CloseHandle(hFile);

	unsigned int start_time = clock(); // начальное время

	char delim[] = " ,._\t\n;:\r";
	char *next_token1 = NULL;

	char *ptr = strtok_s(ReadBuffer, delim, &next_token1);

	map<char*, size_t, cmpByChar> words;

	

	while (ptr != NULL)
	{
		_strlwr_s(ptr, strlen(ptr) + 1);
		words[ptr]++;
		//printf("'%s'\n", ptr);
		//cout << ptr << endl;
		ptr = strtok_s(NULL, delim, &next_token1);
	}


	vector<pair<char*, int>>vec;
	for (auto x = words.begin(); x != words.end(); x++)
		vec.push_back(*x);
	sort(vec.begin(), vec.end(), [](pair<char*, int>elem1, pair<char*, int>elem2) {return elem1.second > elem2.second; });
	
	/*for (auto x : vec)
		cout << x.first <<" "<< x.second << endl;*/


	unsigned int end_time = clock(); // конечное время



	cout << "Длительность процесса: " << end_time - start_time;

	//cout << ReadBuffer;

	
/*
	char a[] = "fgsfdg";

	auto m = map<char*, int, cmpByChar, mallocator<pair<char*, int>>>();

	m[a] = 4;

	m.~map();*/

	delete ReadBuffer;

	_getch();

	return 0;
}