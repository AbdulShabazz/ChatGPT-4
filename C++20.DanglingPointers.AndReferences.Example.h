
/** Q:Provide a c++20 example of a dangling reference, and an example of a dangling pointer.

A:Sure, here are some examples of dangling references and pointers in C++20:

Dangling Reference Example:

c */

#include <iostream>
#include <string>
 
std::string& get_string_ref()
{
    std::string s = "Hello World";
    return s; // returning a reference to a local variable
}
 
int main()
{
    std::string& s_ref = get_string_ref();
    std::cout << s_ref << std::endl; // accessing a dangling reference
    return 0;
}

/** A:In this example, the function get_string_ref returns a reference to a local variable s, 
which is destroyed when the function returns. As a result, s_ref becomes a dangling reference, 
and accessing it leads to undefined behavior.

Dangling Pointer Example:

c */

#include <iostream>
#include <string>
 
int* get_int_pointer()
{
    int num = 42;
    int* ptr = &num;
    return ptr; // returning a pointer to a local variable
}
 
int main()
{
    int* num_ptr = get_int_pointer();
    std::cout << *num_ptr << std::endl; // accessing a dangling pointer
    return 0;
}

/** A:In this example, the function get_int_pointer returns a pointer to a local variable num, 
 which is destroyed when the function returns. As a result, num_ptr becomes a dangling pointer, 
 and accessing it leads to undefined behavior. */

/** Q:If I pass a parameter using a move reference to an unused parameter, does that create a dangling reference to that parameter?

A:No, passing a parameter using a move reference to an unused parameter 
does not create a dangling reference to that parameter.

When you pass an argument to a function using a move reference (&&), 
you are effectively transferring ownership of the object to the function. 
If the function doesn't make use of the parameter, the parameter is simply ignored, 
and there is no reference left to the object.

For example:

c */

#include <iostream>
#include <string>

void do_something(std::string&& str) {
    // do nothing with str
}

int main() {
    std::string s = "Hello World";
    do_something(std::move(s));
    std::cout << s << std::endl; // s is still valid here
    return 0;
}

/* In this example, we pass the string "s" to the function do_something using a move reference. 
The function doesn't make use of the parameter, so it is simply ignored. After the function call, 
"s" is still a valid object, and there is no dangling reference to it. 

RULE OF THUMB

A dangling reference happens when a reference is used to access a variable or object that has already been deallocated or has gone out of scope. T
his can lead to undefined behavior in a program. Here are some rules of thumb to avoid dangling references:

1. **Avoid returning local variables**: Never return a reference or a pointer to a local variable from a function. 
Once the function returns, the local variable goes out of scope and is destroyed, and the reference or pointer becomes dangling.

2. **Be careful with lifetimes**: Understand the lifetimes of your objects. If an object is destroyed, all references and pointers to it become dangling. For example, 
if an object is created within a block or a function, it will be destroyed at the end of the block or function. Any references or pointers to it that are still around are now dangling.

3. **Reassignment**: Be careful when reassigning references. Once a reference is set to refer to an object, it cannot be made to refer to a different object later. 
If the object it refers to is destroyed, the reference becomes dangling.

4. **Beware of iterator invalidation**: In certain cases, such as modifying a vector while iterating over it, you can end up with dangling references. 
Understand when and how iterators can be invalidated by modifications.

5. **Smart Pointers**: Wherever possible, use smart pointers (`std::unique_ptr`, `std::shared_ptr`) instead of raw pointers. 
They automatically manage the lifetime of objects and can help prevent dangling references.

6. **Avoid storing pointers or references** to objects that can be reallocated or resized, like elements in a vector. 
After a reallocation, these pointers or references will be dangling.

7. **Watch out for dangling references in closures**: In C++, if you capture a local variable by reference in a lambda function, and then return the lambda or store it for later use, 
you will end up with a dangling reference as soon as the function ends and the local variable goes out of scope.

*/
