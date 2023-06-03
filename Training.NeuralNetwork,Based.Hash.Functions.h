#include <functional>
#include <unordered_map>
#include <string>

struct CustomHash {
	std::size_t operator()(const std::string& key) const {
		std::size_t hash = 0;
		std::vector<std::size_t> prime {2,3,5,31,101};  // prime numbers...
		std::size_t i{};
		for(char c : key) {
			hash = hash * prime[i] + int{c};
			++i;
		}
		
		return hash;
	}
};

int main() {
	std::unordered_map<std::string, int, CustomHash> map;
	map["test"] = 1;

	return 0;
}

//

#include <functional>
#include <unordered_map>
#include <string>
#include <vector>

std::size_t> prime (const std::size_t& next) // prime numbers...
{
	// generate next prime number //
}

struct CustomHash {
	std::size_t operator()(const std::string& key) const {
		std::size_t hash = 0;
		for(std::size_t i = 0; i < key.size(); ++i) {
			char c = key[i];
			hash = hash * int{c} * prime(i);
		}		
		return hash;
	}
};

int main() {
	std::unordered_map<std::string, int, CustomHash> map;
	map["test"] = 1;

	return 0;
}

// Q:Yes, my goal is to map similar input data to the same hash codes in a high-dimensional feature space. 

/* A:Mapping similar input data to the same hash codes in a high-dimensional feature space is a topic in machine learning known as Learning to Hash (L2H). The aim of L2H methods is to transform high-dimensional data into a compact binary code, ideally preserving the similarity structures of the original data. This approach has gained popularity in handling large-scale datasets, particularly in areas such as image and text retrieval.

One common approach to Learning to Hash is to train a neural network to map input data to binary codes such that the Hamming distance between codes reflects the similarity of the corresponding inputs.

Here's a very simplified example of how this could look like using a hypothetical neural network library:*/

#include <unordered_map>
#include <string>
#include "hypothetical_neural_network_library.h"

class NeuralHash {
public:
	NeuralHash() {
		// Load pre-trained weights from file
		net.load_weights("weights.dat");
	}

	std::size_t operator()(const std::string& key) const {
		// Convert key to input tensor
		Tensor input = string_to_tensor(key);
		
		// Forward pass through the network
		Tensor output = net.forward(input);
		
		// Convert the output tensor to a binary hash code
		std::size_t hash = tensor_to_hash(output);

		return hash;
	}

private:
	// Pre-trained neural network
	NeuralNetwork net;
};

int main() {
	std::unordered_map<std::string, int, NeuralHash> map;
	map["test"] = 1;

	return 0;
}

/*A: In this hypothetical example, we first convert the input key into a suitable format for the network (e.g., a tensor). We then pass this through the pre-trained network to obtain an output tensor. Finally, we convert this output tensor to a binary hash code.

Note that the NeuralHash class and the NeuralNetwork, Tensor, and string_to_tensor and tensor_to_hash functions are not provided by C++ or the Standard Library; they would need to be implemented using a suitable machine learning library or framework.

Remember, training a neural network to generate hash codes that preserve input similarity is a non-trivial task that requires a significant amount of data and computational resources. While the benefits could be substantial for certain applications, for many use-cases, a standard hash function would likely be more efficient and easier to implement.

*/
