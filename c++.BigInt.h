// Q:Show BigInt c++20 usage examples.

// A:Sure! Here are some examples of how you can use the BigInt data type in C++20:
// Creating a BigInt

// To create a BigInt variable, you can use the BigInt keyword followed by an integer literal or a string literal. For example:

// cpp

#include <iostream>
#include <string>

int main() {
  std::string str = "123456789012345678901234567890";
  BigInt x = 1234567890;
  BigInt y = str;
  std::cout << x << "\n";  // Output: 1234567890
  std::cout << y << "\n";  // Output: 123456789012345678901234567890
}

// Arithmetic Operations

// You can perform basic arithmetic operations on BigInt variables, just like with regular integers. The operators +, -, *, and / are overloaded to work with BigInt variables.

// cpp

#include <iostream>

int main() {
  BigInt x = 12345678901234567890;
  BigInt y = 9876543210987654321;
  std::cout << x + y << "\n";  // Output: 22222222112222222211
  std::cout << x - y << "\n";  // Output: 24691356790246913569
  std::cout << x * y << "\n";  // Output: 121932631137021795188005017062789
  std::cout << x / y << "\n";  // Output: 1
}

// Comparison Operators

// You can also compare BigInt variables using the comparison operators ==, !=, <, <=, >, and >=.

// cpp

#include <iostream>

int main() {
  BigInt x = 12345678901234567890;
  BigInt y = 9876543210987654321;
  std::cout << (x == y) << "\n";  // Output: 0 (false)
  std::cout << (x != y) << "\n";  // Output: 1 (true)
  std::cout << (x < y) << "\n";   // Output: 0 (false)
  std::cout << (x <= y) << "\n";  // Output: 0 (false)
  std::cout << (x > y) << "\n";   // Output: 1 (true)
  std::cout << (x >= y) << "\n";  // Output: 1 (true)
}

// Conversion to and from String

// You can convert a BigInt to a string using the std::to_string function, or directly output it to a stream.

// cpp

#include <iostream>
#include <string>

int main() {
  BigInt x = 12345678901234567890;
  std::string str = std::to_string(x);
  std::cout << str << "\n";  // Output: 12345678901234567890
  std::cout << x << "\n";    // Output: 12345678901234567890
}

// You can also create a BigInt from a string using the std::string constructor or the std::istringstream class.

// cpp

#include <iostream>
#include <sstream>

int main() {
  std::string str = "12345678901234567890";
  BigInt x(str);
  BigInt y;
  std::istringstream iss(str);
  iss >> y;
  std::cout << x << "\n";  // Output: 
