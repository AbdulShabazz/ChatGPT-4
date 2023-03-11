/**
A:A coroutine is a lightweight thread of execution that allows you to pause and resume execution at certain points, without blocking the entire thread or process. In C++20, coroutines are implemented using the co_await and co_yield keywords. Here's an example of a coroutine function that generates a sequence of numbers:

c++
*/
#include <iostream>
#include <coroutine>

struct SequenceGenerator {
    struct promise_type {
        int current_value;
        
        auto get_return_object() {
            return SequenceGenerator{std::coroutine_handle<promise_type>::from_promise(*this)};
        }
        
        auto initial_suspend() {
            return std::suspend_always{};
        }
        
        auto final_suspend() {
            return std::suspend_always{};
        }
        
        void return_void() {}
        
        auto yield_value(int value) {
            current_value = value;
            return std::suspend_always{};
        }
    };
    
    std::coroutine_handle<promise_type> coro_handle;
    
    SequenceGenerator(std::coroutine_handle<promise_type> handle) : coro_handle{handle} {}
    
    ~SequenceGenerator() {
        if (coro_handle)
            coro_handle.destroy();
    }
    
    int current_value() const {
        return coro_handle.promise().current_value;
    }
    
    void resume() {
        coro_handle.resume();
    }
};

SequenceGenerator generate_sequence() {
    for (int i = 0; i < 10; ++i) {
        co_yield i;
    }
}

int main() {
    SequenceGenerator seq_gen = generate_sequence();
    while (seq_gen.current_value() < 10) {
        std::cout << seq_gen.current_value() << std::endl;
        seq_gen.resume();
    }
    return 0;
}

/**
This example creates a vector of threads, each of which executes the print_hello() function with a different ID. The join() function is used to wait for all threads to complete before exiting the program.
*/

#include <iostream>
#include <thread>
#include <vector>

void print_hello(int id) {
    std::cout << "Hello from thread " << id << std::endl;
}

int main() {
    std::vector<std::thread> threads;
    for (int i = 0; i < 5; ++i) {
        threads.emplace_back(print_hello, i);
    }
    for (auto& thread : threads) {
        thread.join();
    }
    return 0;
}

/**
A:This example uses the std::system() function to execute the ls -l command in a new process. The output of this command is printed to the console.

Now, let's compare and contrast these three approaches:

    Coroutines are lightweight and provide a way to pause and resume execution at certain points, without blocking the entire thread or process. They are ideal for performing non-blocking I/O operations and other tasks that require frequent context switching.

    Threads allow you to perform concurrent operations within the same process, but they share memory and resources, which can lead to synchronization issues. They are ideal for parallelizing CPU-bound tasks and performing background tasks that do not require a lot of memory or resource sharing.

    Processes provide a way to execute an independent program or script, and they isolate memory and resources between processes. They are ideal for running multiple instances of the same program concurrently, or for distributing work across multiple machines in a distributed computing environment.

When deciding which approach to use, consider the specific requirements of your application. If you need to perform lightweight and fast context switching, coroutines may be the best choice. If you need to perform concurrent operations within the same process and share memory and resources, threads may be a good choice. If you need to execute an independent program or isolate memory and resources between processes, processes may be the best choice.

It's worth noting that C++20 introduces the concept of executors, which provide a unified interface for executing tasks across different concurrency models, including coroutines, threads, and processes. This can simplify the code for performing concurrent operations and make it easier to switch between different concurrency models as needed.

*/

#include <iostream>
#include <cstdlib>

int main() {
    std::system("ls -l");
    return 0;
}

/**Q:Provide an example executors, and their benefits and drawbacks.

A:In C++20, executors provide a unified interface for executing tasks across different concurrency models, including coroutines, threads, and processes. Here's an example of using executors to execute a task asynchronously:

c++ */

#include <iostream>
#include <chrono>
#include <thread>
#include <execution>
#include <future>

int main() {
    auto policy = std::execution::par;
    std::future<int> result = std::async(policy, [] {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        return 42;
    });
    std::cout << "Waiting for result..." << std::endl;
    std::cout << "Result: " << result.get() << std::endl;
    return 0;
}

/** A:In this example, the std::execution::par policy is used to execute a lambda function asynchronously, 
 which sleeps for one second and returns the value 42. The std::async() function is used to create 
 a future object that represents the result of the lambda function, and the get() function is used to wait for the result and retrieve it.

Here are some benefits and drawbacks of using executors:

Benefits:

    Provides a unified interface for executing tasks across different concurrency models.
    Simplifies the code for performing concurrent operations.
    Allows you to switch between different concurrency models as needed.
    Can improve performance by automatically selecting the best concurrency model for the current hardware and workload.

Drawbacks:

    Requires familiarity with the executor interface and its implementation details.
    May not be necessary for simple use cases or small applications.
    Can add complexity to the code if used improperly or unnecessarily.

Overall, executors can be a powerful tool for performing concurrent operations in C++20, 
but they should be used judiciously and with careful consideration of the specific requirements of the application. 
They can simplify the code and improve performance, but they require some knowledge of the underlying concurrency models 
and their implementation details.
 */
