
/*
Q:Show how to intitialize a c++20 threadpool of 128 threads.

A:Starting from C++20, there is no official thread pool library provided by the standard library. However, you can still create your own thread pool by utilizing the <thread> and <queue> header files. Here is an example of how to initialize a thread pool with 128 threads:
*/

#include <iostream>
#include <thread>
#include <vector>
#include <queue>
#include <mutex>
#include <condition_variable>

class ThreadPool {
public:
    ThreadPool(size_t num_threads) : pool_size(num_threads) {
        for (size_t i = 0; i < pool_size; ++i) {
            threads.emplace_back([this](){
                while (true) {
                    std::function<void()> task;
                    {
                        std::unique_lock<std::mutex> lock(queue_mutex);
                        condition.wait(lock, [this]{ return stop || !task_queue.empty(); });
                        if (stop && task_queue.empty()) return;
                        task = std::move(task_queue.front());
                        task_queue.pop();
                    }
                    task();
                }
            });
        }
    }

    template<typename Func, typename... Args>
    auto enqueue(Func&& func, Args&&... args) -> std::future<typename std::result_of<Func(Args...)>::type> {
        using return_type = typename std::result_of<Func(Args...)>::type;
        auto task = std::make_shared<std::packaged_task<return_type()>>(std::bind(std::forward<Func>(func), std::forward<Args>(args)...));
        std::future<return_type> res = task->get_future();
        {
            std::unique_lock<std::mutex> lock(queue_mutex);
            if (stop) {
                throw std::runtime_error("enqueue on stopped ThreadPool");
            }
            task_queue.emplace([task](){ (*task)(); });
        }
        condition.notify_one();
        return res;
    }

    ~ThreadPool() {
        {
            std::unique_lock<std::mutex> lock(queue_mutex);
            stop = true;
        }
        condition.notify_all();
        for (std::thread& thread : threads) {
            thread.join();
        }
    }

private:
    size_t pool_size;
    std::vector<std::thread> threads;
    std::queue<std::function<void()>> task_queue;
    std::mutex queue_mutex;
    std::condition_variable condition;
    bool stop = false;
};

int main() {
    ThreadPool pool(128);

    std::vector<std::future<int>> results;

    for (int i = 0; i < 10000; ++i) {
        results.emplace_back(pool.enqueue([](int num){ return num*num; }, i));
    }

    for (auto& res : results) {
        std::cout << res.get() << std::endl;
    }

    return 0;
}
