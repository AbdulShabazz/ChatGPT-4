/*
Q:Is it more performant to represent large integers of arbitrary length as strings, as opposed to a vector of int's?

A:The performance of representing large integers of arbitrary length as strings versus a vector of ints depends on the specific use case and the operations you'll be performing on the large integers. Let's compare the two representations in terms of memory usage, ease of implementation, and performance for various arithmetic operations:

    Memory usage:
        String representation: Each digit consumes one character (usually 1 byte) in the string, so the memory usage is proportional to the number of digits.
        Vector of ints representation: Each int in the vector represents a single digit or a group of digits (e.g., base 10^9 for 32-bit ints), so the memory usage is proportional to the number of digits or groups of digits.

    Ease of implementation:
        String representation: It is generally easier to implement arithmetic operations using strings because you can directly manipulate individual digits without worrying about the underlying numeric representation.
        Vector of ints representation: Implementing arithmetic operations might be more complex due to the need to handle carries, borrows, and base conversions.

    Performance of arithmetic operations:
        String representation: Arithmetic operations on strings usually involve iterating through the digits one by one, which can be slow for large integers.
        Vector of ints representation: When using a vector of ints, each int can represent a larger value (e.g., up to 2^32 - 1 for 32-bit ints), so the number of iterations required for arithmetic operations is generally smaller, which can lead to better performance.

Overall, representing large integers as a vector of ints can be more performant for arithmetic operations, especially when using a larger base, such as 10^9 or 2^32. However, implementing arithmetic operations with a vector of ints might be more complex due to the need to handle carries, borrows, and base conversions. The string representation can be more straightforward to implement but may have slower performance for large integers. Depending on your specific use case and performance requirements, you can choose the representation that best suits your needs.
*/