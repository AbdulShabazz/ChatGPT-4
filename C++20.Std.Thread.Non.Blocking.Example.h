#include <cstdlib>
#include <thread>
#include <chrono>
#include <iostream>

struct DataParams
{
    bool StatusReady {};
    uint64_t DataReady {};
};

void ProcessData(DataParams& OutParams)
{
    std::this_thread::sleep_for(std::chrono::seconds(1));
    OutParams.DataReady = 32;
    OutParams.StatusReady = true;
}

int main()
{
    bool ThreadSpawned {};
    DataParams _params_;
    while (true)
    {
        if (!ThreadSpawned)
        {
            std::thread th(ProcessData, std::ref(_params_));
            th.detach();
            ThreadSpawned = true;
        }
        if (!_params_.StatusReady)
        {
            std::cout << "Performing some work..." << std::endl;
        } else {
            break;
        }
    }
    
    std::cout << "Q.E.D." << std::endl;
    return EXIT_SUCCESS;
}
