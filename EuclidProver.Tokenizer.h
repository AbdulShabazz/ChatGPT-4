#include <iostream>
#include <vector>
#include <unordered_map>

// Function to generate the next prime number after a given number
uint64_t NextPrimeUInt64(uint64_t n);

int main() {
    // Define the axioms for the term-rewriting system
    std::vector<std::string> axioms = {
        "{1}+{1}={2}",
        "{2}+{2}={4}",
        "{4}+{4}={8}"
    };

    // Tokenize each symbol and compute its prime factorization
    std::vector<std::vector<std::pair<uint64_t, uint64_t>>> axiom_factors;
    for (const auto& axiom : axioms) {
        std::vector<std::pair<uint64_t, uint64_t>> factors;
        for (const auto& c : axiom) {
            if (c == '{' || c == '}' || c == '+' || c == '=')
                continue;  // skip these symbols
            uint64_t prime = NextPrimeUInt64(static_cast<uint64_t>(c));
            uint64_t power = static_cast<uint64_t>(&c - axiom.data());  // compute place-value
            factors.emplace_back(prime, power);
        }
        axiom_factors.push_back(factors);
    }

    // Create a hash table to store the axioms
    std::unordered_map<std::size_t, std::string> axiom_map;

    // Insert each axiom into the hash table
    for (std::size_t i = 0; i < axiom_factors.size(); i++) {
        std::size_t hash_code = 1;
        for (const auto& factor : axiom_factors[i]) {
            hash_code *= static_cast<std::size_t>(std::pow(factor.first, factor.second));
        }
        axiom_map.emplace(hash_code, axioms[i]);
    }

    // Test the hash table by looking up an axiom
    std::string test_axiom = "{1}+{1}={2}";
    std::vector<std::pair<uint64_t, uint64_t>> test_factors;
    for (const auto& c : test_axiom) {
        if (c == '{' || c == '}' || c == '+' || c == '=')
            continue;  // skip these symbols
        uint64_t prime = NextPrimeUInt64(static_cast<uint64_t>(c));
        uint64_t power = static_cast<uint64_t>(&c - test_axiom.data());
        test_factors.emplace_back(prime, power);
    }
    std::size_t test_hash = 1;
    for (const auto& factor : test_factors) {
        test_hash *= static_cast<std::size_t>(std::pow(factor.first, factor.second));
    }
    auto it = axiom_map.find(test_hash);
    if (it != axiom_map.end()) {
        std::cout << "Found axiom: " << it->second << std::endl;
    } else {
        std::cout << "Axiom not found" << std::endl;
    }

    return 0;
}


#include <iostream>
#include <vector>
#include <unordered_map>

int main() {
    // Define the axioms for the term-rewriting system
    std::vector<std::string> axioms = {
        "{1}+{1}={2}",
        "{2}+{2}={4}",
        "{4}+{4}={8}"
    };

    // Tokenize each symbol and store the tuples
    std::vector<std::vector<std::string>> axiom_tuples;
    for (const auto& axiom : axioms) {
        std::vector<std::string> tuple;
        for (std::size_t i = 0; i < axiom.size(); i++) {
            if (axiom[i] == '{') {
                // Find the end of the substring
                std::size_t j = axiom.find('}', i+1);
                // Extract the substring
                std::string token = axiom.substr(i, j-i+1);
                tuple.push_back(token);
                // Skip the substring in the next iteration
                i = j;
            } else if (axiom[i] == '+' || axiom[i] == '=' || axiom[i] == ' ') {
                continue;  // skip these symbols
            } else {
                // Add the symbol to the tuple
                tuple.push_back(std::string(1, axiom[i]));
            }
        }
        axiom_tuples.push_back(tuple);
    }

    // Create a hash table to store the axioms
    std::unordered_map<std::string, std::string> axiom_map;

    // Insert each axiom into the hash table
    for (std::size_t i = 0; i < axiom_tuples.size(); i++) {
        // Concatenate the tuple into a single string
        std::string tuple_str;
        for (const auto& token : axiom_tuples[i]) {
            tuple_str += token;
        }
        // Insert the axiom into the hash table
        axiom_map.emplace(tuple_str, axioms[i]);
    }

    // Test the hash table by looking up an axiom
    std::vector<std::string> test_tuple = {"{1}", "+", "{1}", "=", "{2}"};
    std::string test_tuple_str;
    for (const auto& token : test_tuple) {
        test_tuple_str += token;
    }
    auto it = axiom_map.find(test_tuple_str);
    if (it != axiom_map.end()) {
        std::cout << "Found axiom: " << it->second << std::endl;
    } else {
        std::cout << "Axiom not found" << std::endl;
    }

    return 0;
}

#include <vector>
#include <algorithm>

void splitAtEquals(const std::vector<char>& axiom_0, std::vector<char>& LHS, std::vector<char>& RHS)
{
    auto eqIt = std::find(axiom_0.begin(), axiom_0.end(), '=');

    LHS.clear();
    LHS.reserve(std::distance(axiom_0.begin(), eqIt));
    LHS.insert(LHS.end(), axiom_0.begin(), eqIt);

    RHS.clear();
    RHS.reserve(std::distance(eqIt + 1, axiom_0.end()));
    RHS.insert(RHS.end(), eqIt + 1, axiom_0.end());
}

#include <vector>
#include <algorithm>

std::vector<std::vector<char>> splitAtEquals(const std::vector<char>& axiom_0)
{
    std::vector<std::vector<char>> result;
    auto start = axiom_0.begin();
    auto end = axiom_0.end();

    while (true) {
        auto eqIt = std::find(start, end, '=');

        if (eqIt == end) {
            result.emplace_back(start, end);
            break;
        }

        result.emplace_back(start, eqIt);
        start = eqIt + 1;
    }

    return result;
}

