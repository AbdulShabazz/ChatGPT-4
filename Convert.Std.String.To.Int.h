#include <iostream>
#include <cstdint>
#include <functional>
#include <chrono>
#include <string>
#include <vector>

void profiler (std::function<void()> f)
{
    auto start_time_chrono = std::chrono::high_resolution_clock::now ();
    
    f();
    
    std::cout << std::endl;
    auto end_time_chrono = std::chrono::high_resolution_clock::now();
    auto duration_chrono = std::chrono::duration_cast<std::chrono::nanoseconds>( end_time_chrono - start_time_chrono ).count();
    std::cout << "Total Duration (nanoseconds): " << duration_chrono << "\n\n";
}

int main ()
{
    std::vector<
    std::vector<
    std::string>> keys
    {
        {"cat"}, // 99 97 116 
        {"bat"}, // 98 97 116 
        {"mat"}, // 109 97 116 
        {"mop"}, // 109 111 112 
        {"five"} // 102 105 118 101
    };
    
    profiler([&]()
    {
        
        for(const std::vector<std::string>& InnerVec : keys)
        {
            for(const std::string& str : InnerVec)
            {
                std::vector<char> vec(str.begin(), str.end());
                for(const char& s : vec)
                {
                    std::cout << int{s} << " ";
                }
            }
        }
        std::cout << "\nHello World!";
    });
    
    return EXIT_SUCCESS;
}
