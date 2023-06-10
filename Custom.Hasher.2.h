#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>

std::vector<
std::unordered_set<
std::string,std::size_t>> hash_lookup{ {{"t",0}}, {{"e",0}}, {{"s",0}},{{"t",0}} };

struct CustomHash {
	std::size_t operator()(const std::string& key) const {
		std::size_t hash = 0;
		std::vector<std::size_t> hash_candidates{}; // stores the hash values of the key[0] for comparison in all sets
		std::vector<bool> hash_candidate_exists{}; // stores whether the hash value of the key[0] exists in all sets
		for (std::unordered_set<std::string,std::size_t> set_ : hash_lookup[0]) {
			if (set_.find(std::to_string(key[0])) != set_.end()) { // verify key[0] is a member of the set
				hash_candidates.push_back(set_.find(std::to_string(key[0]))->second);
				hash_candidate_exists.push_back(true);
			}
		}
		if (hash_candidates.size() == 0)
			return 0; // no keys found
		bool KeyFound{true};
		for (bool& b_hash_candidate_exists : hash_candidate_exists){
			KeyFound = false;
			std::size_t lookup_index{1};
			for (char c : key) { // verify any key[0] exists in the remaining sets
				if (b_hash_candidate_exists){
					KeyFound = true;
					b_hash_candidate_exists = 
						hash_lookup[lookup_index].find(std::to_string(c)) != hash_lookup[lookup_index].end();
						hash = hash_lookup[lookup_index].find(std::to_string(c))->second;
				} else {
					break;
				}
			}
			if (!KeyFound)
				hash = 0;
				continue; // key not found in all sets; try next.
			else
				++lookup_index;
		}
		if (!KeyFound)
			hash = 0;
		
		return hash;
	}
};

//

unsigned long xor_djb2_hash(const std::string& str) {
    unsigned long hash = 5381;
    
    for (char c : str) {
        hash = (hash << 5 + 1) + static_cast<unsigned char>(c);
    }
    
    return hash;
}

//

unsigned long xor_djb2_hash(const std::string& str) {
    unsigned long hash = 5381;
    
    for (char c : str) {
        hash = (hash << 5 + 1) ^ static_cast<unsigned char>(c);
    }
    
    return hash;
}

