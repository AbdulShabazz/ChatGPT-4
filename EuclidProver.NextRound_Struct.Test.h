
#include <iostream>
#include <thread>
#include <atomic>
#include <cstdint>
#include <cstdlib>
#include <array>
#include <chrono>
#include <vector>
#include <string>
#include <unordered_map>

struct NextRound_Struct
{
    bool Round_Flag {};
    bool init_flag {};
    
    uint8_t iCurrentRound_UInt8 = 0;
    uint8_t iNextRound_UInt8 = 1;

    uint8_t NextRound_UInt8(const bool UpdateRound_Flag = true)
    {
        if(UpdateRound_Flag && init_flag)
            std::swap(iCurrentRound_UInt8,iNextRound_UInt8);
            
        init_flag = true;

        return iNextRound_UInt8;
    };

    uint8_t CurrentRound_UInt8()
    {
        return iCurrentRound_UInt8;
    };
};

int main()
{
    const auto start_time_chrono = std::chrono::high_resolution_clock::now();
    
    NextRound_Struct Round;
    
    uint8_t Read = Round.NextRound_UInt8();
    uint8_t Write = Round.CurrentRound_UInt8();
    
    std::cout << "Read Index: " << static_cast<unsigned>( Round.NextRound_UInt8(false) ) << std::endl;
    std::cout << "Write Index: " << static_cast<unsigned>(Write) << std::endl;
    std::cout << "Updating Read Index..." << std::endl;
    
    Read = Round.NextRound_UInt8();
    Write = Round.CurrentRound_UInt8();
    
    std::cout << "Read Index: " << static_cast<unsigned>(Read) << std::endl;
    std::cout << "Write Index: " << static_cast<unsigned>(Write) << std::endl;

    const auto end_time_chrono = std::chrono::high_resolution_clock::now();
    const auto duration_chrono = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time_chrono - start_time_chrono).count();
    std::cout << "Total Duration (nanoseconds): " << duration_chrono << std::endl;

    return EXIT_SUCCESS;
}
