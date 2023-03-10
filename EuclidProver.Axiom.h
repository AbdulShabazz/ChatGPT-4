#include <vector>
#include <string>
#include <unordered_map>

// Assume GetNextPrimeUInt64 is implemented elsewhere
uint64_t GetNextPrimeUInt64();

class Axiom {
public:
    Axiom(const std::vector<std::string>& axiom_0) {
        splitEquation(axiom_0);

        for (const std::string& str : axiom_0) {
            uint64_t prime = GetNextPrimeUInt64();
            stringToPrimeMap[str] = prime;
        }
    }

    bool isValid() const {
        return lhs.size() > 0 && rhs.size() > 0 && openBraces == closeBraces;
    }

private:
    std::vector<std::string> lhs;
    std::vector<std::string> rhs;
    int openBraces = 0;
    int closeBraces = 0;
    std::unordered_map<std::string, uint64_t> stringToPrimeMap;

    void splitEquation(const std::vector<std::string>& axiom_0) {
        bool foundEqualsSign = false;

        for (const std::string& str : axiom_0) {
            if (str == "=") {
                foundEqualsSign = true;
                continue;
            }

            if (!foundEqualsSign) {
                lhs.push_back(str);
            } else {
                rhs.push_back(str);
            }
        }

        for (const std::string& str : lhs) {
            if (str == "{") {
                openBraces++;
            } else if (str == "}") {
                closeBraces++;
            }
        }

        for (const std::string& str : rhs) {
            if (str == "{") {
                openBraces++;
            } else if (str == "}") {
                closeBraces++;
            }
        }
    }
};
