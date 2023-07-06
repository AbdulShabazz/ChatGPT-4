
**Title:** Proposal for Validated Types as a Language-Level Extension in C++

**Document number:** N/A

**Date:** 2023-07-05

**Project:** Programming Language C++

**Reply to:** [Your Name and Contact Information]

**Introduction**

HTML elements such as inputs and textareas have a `pattern` attribute that allows developers to specify a regular expression that the value of the element must match. 

```HTML
<textarea id="MyStringVar" oninput='validate_email_address_format(this.value, "/^.+@\\w\\.\\w+$/")'></textarea>
```

This is a simple and effective way to ensure that user input is valid before instantiation at a memory address. 
This validation is essential in order to ensure data integrity, validation must be performed on the getter side as well. 
This can be done by writing validation logic manually for each variable, but this can lead to code duplication and an increased risk of bugs.

This proposal suggests the addition of "validated types" to the C++ language. This feature would allow developers to define a data type along with a validation function or Validator that validates the value upon initialization, thereby ensuring data integrity and reducing the risk of bugs.

**Motivation and Scope**

Take the following C++ example:

```cpp
std::vector<std::string> MyStringVar{...};
```

Here, `std::vector` is the base type which defines the memory layout it expects, and `std::string` is the validation function for the accepted lexical stream of symbols. But: In many programming scenarios, developers need to ensure that certain conditions are met when a variable is initialized. Current methods for ensuring such conditions often involve writing validation logic manually for each variable, which can lead to code duplication and an increased risk of bugs. 

The "validated types" feature proposed herein provides a clear, concise way to tie validation logic to the type itself, thereby ensuring the integrity of the data without the need for repetition of code.

This feature is expected to be widely applicable and beneficial in various domains where data validation is critical, such as web development, database programming, and user input handling.

The idea of extending C++ to validate types upon initialization is interesting and what I consider potentially powerful. However, such a feature is not part of the C++23 standard, as of my knowledge.

Still, it is possible to achieve something similar in C++ by creating classes or structs that perform validation in their constructors. One could use a regex library to validate string formats, for instance, or create a more complex validation logic.

Here's an example:

```cpp
#include <regex>
#include <stdexcept>
#include <string>

struct EmailAddress {
    std::string value;

    EmailAddress(const std::string& s) : value(s) {
        std::regex re(".+@.+\\..+");
        if (!std::regex_match(value, re)) {
            throw std::invalid_argument("Invalid email address format");
        }
    }
};

int main() {    
    EmailAddress email1("example@example.com"); // This will work
    EmailAddress email2("invalid_email"); // This will throw an exception
}
```

In this example, when an `EmailAddress` object is instantiated, it checks whether the input string matches the email address format. If it doesn't, it throws an exception, preventing the object from being created with an invalid value.

Again, this isn't exactly what I'm asking for - a language-level extension to validate types upon initialization - but it is a way to enforce validation when objects of a certain type are created. This approach is flexible and can be extended to validate any kind of input. You can create different classes/structs for different types of data, each with its own validation logic.

However, with this new implementation you would need to be mindful of exceptions in your code. In the example above, if an exception is thrown and not caught, your program will terminate. Depending on your use case, the developer might need to routinely add appropriate exception handling logic.

**Impact on the Standard**

This is a pure extension to the C++ standard and does not modify or conflict with any existing features.

As for the idea of extending the C++ standard itself, such changes would need to be proposed, reviewed, and approved by the ISO C++ standards committee. 

**Design and Specification**

The proposed syntax for a validated type could be:

```cpp
template < typename BaseType, typename BoolValidationFunction >
std::validated_type < BaseType, BoolValidationFunction > TypeName;
```

Here, `TypeName` is the name of the new type; `BaseType` is an existing C++ type; and `BoolValidationFunction` is a function (which could be a lambda, free function, or member function) that accepts a value of `BaseType` and returns a `bool`.

Upon initialization of a variable of `TypeName`, `BoolValidationFunction` is automatically called with the initial value. If `BoolValidationFunction` returns `false`, a standard library exception is thrown or perhaps a std::expected!

An example usage would be:

```cpp
auto validate_email = template < typename U > [](const U& email) -> bool {
    std::regex re(".+@.+\\..+");
    return std::regex_match(email, re);
};

using EmailAddress = std::validated_type < std::string, validate_email > ;

int main() {
    EmailAddress email1 = "example@example.com";  // This will work for our custom datatype
    EmailAddress email2 = "invalid_email";  // This will throw a standard library exception
}
```

**Implementation and Test Plan**

A reference implementation will be provided upon consideration and or acceptance of this proposal, along with a comprehensive suite of tests to ensure the feature behaves as expected and interacts correctly with existing features.

**Acknowledgments**

N/A

**References**

N/A

**Revision History**

N/A
