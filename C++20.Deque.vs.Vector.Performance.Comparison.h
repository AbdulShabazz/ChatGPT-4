/*
Q:Provide a c++20 usage example for std::deque.

A:In this C++20 example, we will demonstrate the usage of std::deque by implementing a simple program that adds and removes elements from both ends of the deque container. We will use various std::deque functions such as push_front, push_back, pop_front, pop_back, and size to manipulate the deque.

cpp
*/
#include <iostream>
#include <deque>

int main() {
    std::deque<int> my_deque;

    // Adding elements to the front and back of the deque
    my_deque.push_front(1);
    my_deque.push_back(2);
    my_deque.push_front(0);
    my_deque.push_back(3);

    // Displaying the deque elements
    std::cout << "Deque elements:" << std::endl;
    for (const auto& element : my_deque) {
        std::cout << element << ' ';
    }
    std::cout << std::endl;

    // Removing elements from the front and back of the deque
    my_deque.pop_front();
    my_deque.pop_back();

    // Displaying the deque elements after removing elements
    std::cout << "Deque elements after removing:" << std::endl;
    for (const auto& element : my_deque) {
        std::cout << element << ' ';
    }
    std::cout << std::endl;

    // Displaying the deque size
    std::cout << "Deque size: " << my_deque.size() << std::endl;

    return 0;
}

/*
When you compile and run this program, you should see the following output:

Deque elements:
0 1 2 3
Deque elements after removing:
1 2
Deque size: 2

Q:Compare c++20 std::deque to std::vector. Include insert, remove, erase, and search performance. 

A:std::deque and std::vector are both sequence containers in C++ that store elements in a linear fashion. However, their underlying data structures and performance characteristics differ. Let's compare them based on their insertion, removal, erasing, and searching performance.

    Insertion:
        std::deque: Insertion at both ends (front and back) is very efficient, typically having an O(1) complexity. However, insertion in the middle takes O(n) time complexity as elements need to be shifted.
        std::vector: Insertion at the end is very efficient, having an amortized O(1) complexity. However, insertion at the front or in the middle has a higher complexity of O(n) as elements need to be shifted.

    Removal:
        std::deque: Removal at both ends (front and back) is very efficient, typically having an O(1) complexity. However, removal in the middle takes O(n) time complexity as elements need to be shifted.
        std::vector: Removal at the end is very efficient, having an O(1) complexity. However, removal at the front or in the middle has a higher complexity of O(n) as elements need to be shifted.

    Erasing:
        std::deque: Erasing a range of elements takes O(n) time complexity, where n is the number of elements to be erased plus the minimum distance to the beginning or end of the deque.
        std::vector: Erasing a range of elements takes O(n) time complexity, where n is the number of elements to be erased plus the distance from the last element to be erased to the end of the vector.

    Searching:
        std::deque: Searching has O(n) time complexity, as the deque elements are stored in multiple, non-contiguous memory blocks.
        std::vector: Searching has O(n) time complexity. Although elements are stored in a contiguous memory block, which might offer better cache locality, searching still has a linear complexity.

In conclusion, std::deque is more efficient for insertion and removal at both ends, 
while std::vector is better for scenarios that mostly involve insertions and removals at the end. 
For searching and erasing, both containers have similar performance characteristics. However, 
std::vector has better memory locality due to its contiguous memory allocation, 
which can result in better performance in some situations.
*/
