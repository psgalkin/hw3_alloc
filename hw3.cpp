#include "Container.h"
#include "pretty.h"
#include "Map_allocator.h"

#include <iostream>
#include <vector>
#include <map>

int fact(int n)
{
	int f = 1;
	for (int i = 1; i <= n; ++i) {
		f *= i;
	}
	return f;
}

int main() 
try
{
	std::map<int, int> defMap;
	for (int i = 0; i < 10; ++i) {
		defMap[i] = fact(i);
	}

	std::map<int, int, std::less<int>, Map_allocator<std::pair<const int, int>, 10>> allocMap;
	for (int i = 0; i < 10; ++i) {
		allocMap[i] = fact(i);
	}
	for (auto p : allocMap) {
		std::cout << p.first << ": " << p.second << '\n';
	}


 	My_Cont<Map_allocator<int, 10>> cont;
	for (int i = 1; i < 10; ++i) {
		cont.push_back(i);
	}
	cont.show();

	return 0;
}
catch (std::exception& e)
{
	std::cerr << e.what() << '\n';
	return 1;
}

