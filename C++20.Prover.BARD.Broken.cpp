#include <iostream>
#include <cstdint>
#include <unordered_map>
#include <unordered_set>
#include <vector>

const int LHS = 0;

// Use a divide-and-conquer approach to generate new theorems.
std::vector<uint64_t> GenerateTheorem(std::vector<uint64_t>& theorem, const std::vector<uint64_t>& axioms) {
	if (theorem == axioms) {
		return theorem;
	}

	// Find the first axiom that divides the left-hand side of the theorem.
	auto it = std::find_if(axioms.begin(), axioms.end(), [&theorem](uint64_t axiom) {
		return theorem[LHS] % axiom == 0;
	});

	if (it == axioms.end()) {
		// The theorem cannot be proven.
		return {};
	}

	// Divide the left-hand side of the theorem by the axiom.
	theorem[LHS] /= *it;

	// Generate the theorem for the right-hand side of the theorem.
	auto right_hand_side_theorem = GenerateTheorem(theorem, axioms);

	// If the right-hand side of the theorem is empty, then the theorem is proven.
	if (right_hand_side_theorem.empty()) {
		return theorem;
	}

	// Push the axiom onto the proof stack.
	theorem.emplace_back(*it);

	// Return the theorem for the right-hand side of the theorem.
	return right_hand_side_theorem;
}

// Main function.
int main() {

		// Use a hash table to store the proven theorems.
		std::unordered_set<std::vector<uint64_t>> ProvenTheorems;
		
		// Check if a theorem has been proven already.
		bool IsProven(const std::vector<uint64_t>& theorem) {
			return ProvenTheorems.find(theorem) != ProvenTheorems.end();
		}
		// Use a hash table for the call history.
		std::unordered_map<std::vector<uint64_t>, bool> CallHistory;

	// Initialize the call history.
	CallHistory.clear();

	// Initialize the proven theorems.
	ProvenTheorems.clear();

	// Get the axioms.
	std::vector<uint64_t> axioms = {1, 2, 3, 5, 7, 11, 13, 17, 19, 23};

	// Generate all possible theorems.
	for (std::vector<uint64_t> theorem = {1}; theorem.size() <= 10; ++theorem) {
		// If the theorem is proven, print it.
		if (IsProven(theorem)) {
			std::cout << theorem << std::endl;
		}
	}

	return 0;
}

