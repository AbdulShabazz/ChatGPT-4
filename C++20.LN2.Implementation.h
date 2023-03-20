/*
Q:Show an example c++20 implementation for `log2()` which does not rely on third party libraries or built-in types.

A:Here is a C++20 implementation of the log2() function without using third-party libraries or built-in functions. 
This implementation uses a basic iterative method to compute the base-2 logarithm:
*/

#include <iostream>
#include <limits>

constexpr double epsilon = std::numeric_limits<double>::epsilon();

double log2(double x)
{
    if (x <= 0.0)
	{
        throw std::domain_error("log2(): argument must be a positive value");
    }
    int exponent = 0;
    while (x < 1.0)
	{
        x *= 2;
        exponent--;
    }
    while (x >= 2.0)
	{
        x /= 2;
        exponent++;
    }
    double result = exponent;
    double term = x - 1.0;
    double factor = term;
    for (int i = 1; i <= 30; ++i)
	{
        result += factor / static_cast<double>(i);
        term *= -1.0 * (x - 1.0);
        factor *= term;
    }
    return result;
}

int main()
{
    double value = 8.0;
    double log2_value = log2(value);
    std::cout << "log2(" << value << ") = " << log2_value << std::endl;
    return 0;
}
