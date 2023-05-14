#include <cstdlib>
#include <iostream>
#include <chrono>
#include <atomic>
#include <thread>
#include <condition_variable>
#include <mutex>

int main() {
    bool bStatusReadyFlag {};
    
    std::mutex mtx;
    std::condition_variable cv;
    
    auto ReWrite = [](bool& InStatusReadyFlag, std::mutex& _mtx, std::condition_variable& _cv)
    {
        std::cout << "Q.E.D." << std::endl;
        InStatusReadyFlag = true;
        
        std::lock_guard<std::mutex> lck(_mtx);
        _cv.notify_one();
    };
	
	auto start_time_chrono = std::chrono::high_resolution_clock::now();
	
    std::thread th(ReWrite, std::ref(bStatusReadyFlag), std::ref(mtx), std::ref(cv));
    th.detach();
	
    std::unique_lock<std::mutex> lck(mtx);
    cv.wait(lck, [&]{return bStatusReadyFlag;});
	
	auto end_time_chrono = std::chrono::high_resolution_clock::now();
	auto duration_chrono = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time_chrono - start_time_chrono).count();
	std::cout << "Total Duration (nanoseconds): " << duration_chrono << std::endl;
	
  return EXIT_SUCCESS;
}

/*
Q.E.D.
Total Duration (nanoseconds): 166909
*/

#include <cstdlib>
#include <iostream>
#include <chrono>
#include <atomic>
#include <thread>

int main() {
    bool bStatusReadyFlag {};
    
    auto ReWrite = [](bool& InStatusReadyFlag)
    {
        std::cout << "Q.E.D." << std::endl;
        InStatusReadyFlag = true;
    };
	
	auto start_time_chrono = std::chrono::high_resolution_clock::now();
	
    std::thread th(ReWrite, std::ref(bStatusReadyFlag));
    th.detach();
	
	while(!bStatusReadyFlag)
	{
	    std::this_thread::sleep_for(std::chrono::nanoseconds(25));
	}
	
	auto end_time_chrono = std::chrono::high_resolution_clock::now();
	auto duration_chrono = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time_chrono - start_time_chrono).count();
	std::cout << "Total Duration (nanoseconds): " << duration_chrono << std::endl;
	
  return EXIT_SUCCESS;
}

/*
Q.E.D.
Total Duration (nanoseconds): 102481
*/

#include <cstdlib>
#include <iostream>
#include <chrono>
#include <atomic>
#include <thread>
#include <condition_variable>
#include <mutex>

int main()
{
    bool bStatusReadyFlag {};
    const std::string QED {"Q.E.D."};
    
    auto cb = [](const bool& _bStatusReadyFlag, const std::string& _qed) -> void 
    {
        if (_bStatusReadyFlag)
            std::cout << _qed << std::endl;
    };
    
    auto ReWrite = [](bool& _bStatusReadyFlag, const std::string& _qed, auto&& _cb) -> void
    {
        std::cout << "ReWrite..." << std::endl;
        _bStatusReadyFlag = true;
        _cb (_bStatusReadyFlag, _qed);
    };
	
	auto start_time_chrono = std::chrono::high_resolution_clock::now();
	
    std::thread th(ReWrite, std::ref(bStatusReadyFlag), std::cref(QED), std::move(cb));
	
	auto end_time_chrono = std::chrono::high_resolution_clock::now();
	auto duration_chrono = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time_chrono - start_time_chrono).count();
	std::cout << "Total Duration (nanoseconds): " << duration_chrono << std::endl;
	
    th.join();
	
	return EXIT_SUCCESS;
}

/*
Total Duration (nanoseconds): 59071
ReWrite...
Q.E.D.
*/
