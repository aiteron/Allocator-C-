#include <iostream>
#include <map>
#include <conio.h>
#include <Windows.h>

using namespace std;

#include "Mallocator.h"

struct word
{
	char* ptr;
	size_t len;
};

struct cmpByChar
{
	bool operator()(const string& a, const string& b) const
	{
		return a.compare(b);
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

	char test[] = "I have, some!*interesting story.    f";

	char delim[] = " ,.\t\n;:";
	char *next_token1 = NULL;

	char *ptr = strtok_s(ReadBuffer, delim, &next_token1);

	while (ptr != NULL)
	{
		//printf("'%s'\n", ptr);
		cout << ptr << endl;
		ptr = strtok_s(NULL, delim, &next_token1);
	}

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