
#include <iostream>

template<int N>
void fn();

template<>
void fn<1>()
{
	std::cout << "Hello World!\n";
}

template<>
void fn<0>()
{
	std::cout << "Foo Bar Baz Qux: N must be 1.\n";
}

int main()
{
	fn<1 == 1>(); // prints "Hello World!"
	// fn<1 == 1>(); // prints "Foo Bar Baz Qux: N must be 1.\n"
	return 0;
}

//

#include <iostream>

template<bool N>
void fn();

template<>
void fn<true>()
{
    std::cout << "Hello World!\n";   
}

template<>
void fn<false>()
{
    std::cout << "Foo Bar Baz Qux: N must be 1.\n";
}

int main()
{
    fn<1 == 1>(); // prints "Hello World!"
    // fn<1 == 1>(); // prints "Foo Bar Baz Qux: N must be 1.\n"
    return 0;
}
