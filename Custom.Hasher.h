#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>

// minimal perfect hash function

/*
Q:Provide a C++20 algorithm which splits string keys, distilled in a nested std::vector<>, keys, 
into a std::size_t array, hasher, which is later supplied to a std::unordered_multimap as a custom lookup table for a smart hasher 
*/

std::vector<std::vector<std::string>> keys
{
{"cat"}, // 99 97 116 
{"bat"}, // 98 97 116 
{"mat"}, // 109 97 116 
{"mop"}, // 109 111 112 
{"five"} // 102 105 118 101
};

/*
opcodes
255 : data_
254 : data_CHOOSE
253 : data_CHOOSE_jmp_if_true (check std::vector<std::unordered_set>)
252 : data_CHOOSE_seq
251 : data_CHOOSE_end
250 : data_hash_indexes
249 : data_NULL
*/

/*
Q:Complete the hash_string function below, which takes a std::string key and returns a std::size_t hash,
so that the following test passes:
*/

std::vector<std::size_t> hasher{};
std::vector<std::unordered_set<std::size_t,bool>> hash_uset;

/*
// Step 1: hash["cat"]
hasher; // {252,99,97,116,255,252,0}

// Step 2: hash["bat"]
hasher; // {252,253,97,116,255,250,0,1,255}
hash_uset{{99,98}};

// Step 3: hash["mat"]
hasher; // {252,253,97,116,255,250,0,1,2,255}
hash_uset{{99,98,109}};

// Step 4: hash["mop"]
hasher; // {252,253,97,116,255,252,111,112,255,250,0,1,2,3,255}
hash_uset{{99,98,109}};

// Step 5: hash["five"]
hasher; // {252,253,97,116,255,252,111,112,255,252,102,105,118,101,255,250,0,1,2,3,4,255}
hash_uset{{99,98,109}};
*/

constexpr std::size_t hash_string(const std::string& key) {
	bool mode_seq{};
	std::size_t hash = 0;
	std::size_t stride = 0;
	std::size_t i = 0;
	const std::size_t I = key.size();

	for (; i < I; ++i) {
		const char c = key[i];
		while (i < I) {
			const bool next_index_exists_flag = (i + 1) < I;
			switch (hasher[i]) {
				case 255: // data_
					// NOP
					break;

				case 254: // data_CHOOSE
					if (c == hasher[i + 1]) {
						stride++;
						i += 2;
					}
					else {
						i += 3; // jump over the data_CHOOSE
					}
					break;

				case 253: // data_CHOOSE_jmp_if_true
					if (c == hasher[i + 1]) {
						i = hasher[i + 2]; // jump to the index provided by data_CHOOSE_jmp_if_true
					}
					else {
						i += 3; // otherwise just continue
					}
					break;

				case 252: // data_CHOOSE_seq
					while (hasher[i] != 255 && c == hasher[i + 1]) { // while there's a match and not a data_
						stride++;
						i += 2;
					}
					if (hasher[i] == 255) { // end of sequence, continue normally
						i++;
					}
					break;

				case 251: // data_CHOOSE_end
					i++;
					break;

				case 250: // data_hash_indexes
					hash = hasher[i + stride]; // get the hash index corresponding to the stride
					stride = 0; // reset stride
					i += 2; // skip over the data_hash_indexes and the index
					break;

				case 249: // data_NULL
					i++;
					break;

				default:
					i++;
					break;
			}
		}
	}

	return hash;
}

/*
tokens: [1 2 4 +]
primes: [2 3 5 7]

Given:
Axiom_0000_lhs: 1 + 1 // prime 2
Axiom_0000_rhs: 2 // prime 3
Axiom_0001_lhs: 2 + 2 // prime 5
Axiom_0001_rhs: 4 // prime 7

Prove:
Theorem_0000_lhs: 1 + 1 + 1 + 1
Theorem_0000_rhs: 4

Such that:
2 = 5i, where |5i| = (5^4)^(1/4) = 5
4 = 7j, where |7j| = (7^4)^(1/4) = 7
1 + 1 = (2i + 2j) = 2(i + j), where |2i + 2j + 0k + 0l| = (2^4 + 2^4)^(1/4) = 16^(1/4) = 2
2 + 2 = (3i + 3j) = 3(i + j), where |3i + 3j + 0k + 0l| = (3^4 + 3^4)^(1/4) = 18^(1/4)
1 + 1 + 1 + 1 = (2i + 2j + 2k + 2l), where |2i + 2j + 2k + 2l| = (2^4 + 2^4 + 2^4 + 2^4)^(1/4) = 32^(1/4)

*/

#include <iostream>

int main()
{
	std::cout << "Hell111, world!\n";

	std::string s{};
	std::cin >> s;
	return 0;
}

