#include <iostream>
#include <cstdlib>
#include <utility>
#include <chrono>
#include <vector>
#include <thread>
#include <unordered_map>
#include <functional>
#include <algorithm>

const int LHS = 0;
const int RHS = 1;

std::vector<
std::vector<
std::string>>
InTheorem_StdStrVec = 
{
	{"1", "+", "1", "+", "1", "+", "1"}, // (lhs) Prime Composite: 1585615607 //
	{"4"} // (rhs) Prime Composite: 29 //   
};

const
std::vector<
std::vector<
std::vector<
std::string>>>
InAxioms_StdStrVec = 
{
	{
		{"1", "+", "1"}, // (lhs) Prime Composite: 8303 //
		{"2"} // (rhs) Prime Composite: 31
	},

	{
		{"2", "+", "2"}, // (lhs) Prime Composite: 22103 //
		{"4"} // (rhs) Prime Composite: 29 //
	}   
};

void RemoveEmptyStrings(auto& vec)
{
    // Remove empty strings from-, and resize-, the vec.
    vec.erase(
        std::remove_if(
            vec.begin(), 
            vec.end(), 
            [](const std::string& s)
            {
                return s.empty();
            }), vec.end());
}

bool Rewrite
(
    auto& th, 
    
    const auto& from, 
    
    const auto& to
)
{
    bool bSuccessFlag {};
    
    if (th.size() < from.size())
        return false;
        
    std::unordered_map<std::string, std::string>
    
    end_scope {{"(", ")"}, {"{", "}"}, {"[", "]"}};
    
    std::vector<
    std::string> result {};
        
    uint64_t i {};
    
    const uint64_t I {from.size()};
    
    for (const auto& val : th )
    {
        std::cout << "Next val: " << val << std::endl;
        
        if (val == from[i])
        {
            ++i;
            
            std::cout << "Match found: " << val;
            
            if (i == I)
            {
                for (const auto& u2 : to)
                {
                    std::cout << u2 << " ";
                    result.emplace_back (u2);
                }
                
                bSuccessFlag = true;
                
                std::cout << "\nSubstitution found" << std::endl;
                
                i = 0;
            } 
        } else {
            i = 0; // reset //
            
            std::cout << "No Match found: " << val << std::endl;
            
            result.emplace_back (val);
        }
        std::cout << std::endl;
    }
    
    th = result;
    
    return bSuccessFlag;
}

int main()
{
	auto& TempTheorem_StdStrVecRef {InTheorem_StdStrVec};
	
	auto start_time_chrono = std::chrono::high_resolution_clock::now();
	
	Rewrite (TempTheorem_StdStrVecRef[RHS], InAxioms_StdStrVec[1][RHS], InAxioms_StdStrVec[1][LHS]); // lhs_reduce //
	
	auto end_time_chrono = std::chrono::high_resolution_clock::now();
	auto duration_chrono = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time_chrono - start_time_chrono).count();
	std::cout << "Total Duration (nanoseconds): " << duration_chrono << std::endl;
	
    std::cout << "TempTheorem_StdStrVecRef[RHS] = " ;
    
	for (const auto& val : TempTheorem_StdStrVecRef[RHS])
	{
	    std::cout << val << " " ;
	}
	
	std::cout << std::endl << "Q.E.D." << std::endl;
	
    return EXIT_SUCCESS;
}
