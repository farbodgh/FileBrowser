#include <iostream>
#include <fstream>
#include <filesystem>
#include <thread>
#include <string>
#include <vector>

#include "SearchEngine.h"



class foo
{
public:
	static void bar(int a)
	{
		std::cout << "bar: " << a << std::endl;
	}
};

int main()
{
	SearchEngine searchEngine("findssit.txt");
	searchEngine.Search();
}