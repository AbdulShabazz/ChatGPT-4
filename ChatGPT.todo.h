/*
Update README examples
Update Euclid.h
Update main.h example
*/
#include <iostream>
#include <string>
#include <vector>
#include <initializer_list>
#include<cstdlib>
void Theorem(std::initializer_list<std::string> args)
{
	std::vector<std::string> buff;
	std::string s {};
	for (const auto& arg : args)
	{
		s += arg;
	}
	std::cout << s << std::endl;
};

int main()
{
	Theorem({"2"});
	Theorem({"4"});
	Theorem({"2","+","2"});
	Theorem({"1","+","1","+","1","+","1"});

	return EXIT_SUCCESS;
}
