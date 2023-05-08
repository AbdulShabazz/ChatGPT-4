#include <iostream>
#include <thread>
#include <future>
#include <cstdlib>
#include <chrono>

int main()
{
    // Create a function object that prints "Hello, world!"
    auto print_hello = []() { std::cout << "Hello, world!" << std::endl; };
    
    const auto start_time_chrono = std::chrono::high_resolution_clock::now();
    
    // Create a new thread to execute the function object
    //std::future<void> future = std::async(print_hello);
    std::thread th(print_hello);
    
    // Do some other work in the main thread
    std::cout << "Doing some other work in the main thread..." << std::endl;
    
    // Wait for the asynchronous operation to complete
    //future.wait();
    th.join();
    
    // Print the result of the asynchronous operation
    std::cout << "The asynchronous operation completed successfully." << std::endl;

    const auto end_time_chrono = std::chrono::high_resolution_clock::now();
    const auto duration_chrono = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time_chrono - start_time_chrono).count();
    std::cout << "Total Duration (nanoseconds): " << duration_chrono << std::endl;
    
    return EXIT_SUCCESS;
}
