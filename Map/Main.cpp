#include <iostream>
#include <map>
#include <functional>
#include <string>
#include <conio.h>
#include <memory>
#include <stdio.h>

using namespace std;

#include "Mallocator.h"


struct cmpByInt
{
	bool operator()(const int& a, const int&b) const
	{
		return a < b;
	}
};

int main()
{
	//cout << "Hell";

	auto m = map<int, int, cmpByInt, mallocator<pair<int, int>>>();

	m[5] = 4;
	m[2] = 1;

	m.~map();

	_getch();

	return 0;
}