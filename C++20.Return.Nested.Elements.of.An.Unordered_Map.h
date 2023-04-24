/*
How do you return all elements of nested C++20 std::unordered_maps?

To return all elements of nested C++20 std::unordered_maps, you can use a recursive function that iterates through each nested map and returns a flattened container of all the elements. Here's an example using a nested std::unordered_map with std::string keys and int values:

cpp
*/
#include <iostream>
#include <unordered_map>
#include <vector>

using NestedMap = std::unordered_map<std::string, std::unordered_map<std::string, int>>;

void getAllElementsHelper(const NestedMap &nested_map,
                          std::vector<std::tuple<std::string, std::string, int>> &elements,
                          const std::string &parent_key = "") {
    for (const auto &[key, value] : nested_map) {
        if constexpr (std::is_same_v<decltype(value), int>) {
            elements.emplace_back(parent_key, key, value);
        } else {
            getAllElementsHelper(value, elements, key);
        }
    }
}

std::vector<std::tuple<std::string, std::string, int>> getAllElements(const NestedMap &nested_map) {
    std::vector<std::tuple<std::string, std::string, int>> elements;
    getAllElementsHelper(nested_map, elements);
    return elements;
}

int main() {
    NestedMap nested_map = {
        {"A", {{"A1", 1}, {"A2", 2}}},
        {"B", {{"B1", 3}, {"B2", 4}}},
        {"C", {{"C1", 5}, {"C2", 6}}},
    };

    auto elements = getAllElements(nested_map);

    for (const auto &[key1, key2, value] : elements) {
        std::cout << "Key1: " << key1 << ", Key2: " << key2 << ", Value: " << value << std::endl;
    }

    return 0;
}
/*
In this example, the getAllElements function returns a vector of tuples containing all elements in the nested nested_map unordered_map. The main function then prints out the keys and values of all elements. The getAllElementsHelper function is a recursive helper function that iterates through the nested maps and stores the elements in the elements vector.

Keep in mind that this example is specifically designed for a two-level nested std::unordered_map. If you have a more complex data structure, you may need to modify the helper function to handle the additional nesting levels.

If the data structure is very deep, you may run into stack overflow issues due to recursion. In such cases, you can use an iterative approach with a stack or queue data structure to traverse the nested maps.
*/
