/*Q:What is an efficient C++20 algorithm to compute every permutation order for the uint64_t elements in Number?*/
// std::vector<uint64_t> Numbers;
// Numbers.resize(1000000); // 0 to 1e6"

/*
If you're looking to compute every permutation of the elements in the Numbers vector, you can use the std::next_permutation function available in the C++ Standard Library. This function takes two iterators as input and rearranges the elements in the specified range to the next lexicographically greater permutation.

Here is an efficient C++20 algorithm to generate all permutation orders for the uint64_t elements in the Numbers vector:

cpp
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdint>

int main() {
    std::vector<uint64_t> Numbers;
    Numbers.resize(4); // 0 to 4

    // Fill the vector with sequential numbers
    for (size_t i = 0; i < Numbers.size(); ++i) {
        Numbers[i] = i;
    }

    // Sort the vector in ascending order
    std::sort(Numbers.begin(), Numbers.end());

    // Function to process each permutation (e.g., print or store)
    auto process_permutation = [](const std::vector<uint64_t>& perm) {
        for (const auto& num : perm) {
            std::cout << num << ' ';
        }
        std::cout << '\n';
    };

    // Compute and process each permutation
    do {
        process_permutation(Numbers);
    } while (std::next_permutation(Numbers.begin(), Numbers.end()));

	/*
	output:
	0 1 2 3
	0 1 3 2
	0 2 1 3
	0 2 3 1
	0 3 1 2
	0 3 2 1
	1 0 2 3
	1 0 3 2
	1 2 0 3
	1 2 3 0
	1 3 0 2
	1 3 2 0
	2 0 1 3
	2 0 3 1
	2 1 0 3
	2 1 3 0
	2 3 0 1
	2 3 1 0
	3 0 1 2
	3 0 2 1
	3 1 0 2
	3 1 2 0
	3 2 0 1
	3 2 1 0
	*/

    return 0;
}
/*
Please note that generating all possible permutations of a sequence with 1,000,000 elements is a computationally intensive task, which will take a very long time and may be impractical in most use cases. You may want to consider using a smaller input size or parallelizing the algorithm if you really need to generate all permutations of such a large sequence.
*/
