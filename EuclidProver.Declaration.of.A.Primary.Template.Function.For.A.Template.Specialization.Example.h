#include <iostream>
#include <thread>
#include <atomic>
#include <cstdint>
#include <functional>

/*
A:The issue with your code is that the template specialization for fn 
is missing the declaration of the primary template function, which is required 
when providing a specialization. The compiler doesn't know what fn is because 
you haven't defined it yet. To fix the issue, you need to add the primary template 
function and also specify that fn is a function template. Here's the corrected version of your code:
*/

template <bool B>
void fn(); // Declaration of the primary template function

template<>
void fn<true>()
{
    std::cout << "fn<true>(...)" << std::endl;
}

int main()
{
    fn<1==1>();
    
    return 0;
}
