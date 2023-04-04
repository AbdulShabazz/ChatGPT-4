
#include <iostream>
#include <vector>
#include <queue>
#include <chrono>
#include <random>
#include <coroutine>
#include <mutex>
#include <condition_variable>
#include <thread>

class Axiom {
public:
    uint64_t GuidUInt64;

    Axiom(uint64_t guid) : GuidUInt64(guid) {}
};

class GlobalAxiomQueue {
private:
    std::queue<Axiom> queue;
    std::mutex mutex;
    std::condition_variable cv;

public:
    void push(const Axiom& axiom) {
        std::unique_lock<std::mutex> lock(mutex);
        queue.push(axiom);
        lock.unlock();
        cv.notify_one();
    }

    Axiom pop() {
        std::unique_lock<std::mutex> lock(mutex);
        cv.wait(lock, [&] { return !queue.empty(); });
        Axiom axiom = queue.front();
        queue.pop();
        return axiom;
    }
};

struct AwaitablePrime {
    uint64_t current;

    AwaitablePrime(uint64_t start) : current(start) {}

    bool await_ready() const noexcept { return false; }

    uint64_t await_resume() { return current; }

    void await_suspend(std::coroutine_handle<> handle) {
        std::thread([this, handle]() {
            while (true) {
                current++;
                if (is_prime(current)) {
                    handle.resume();
                    break;
                }
            }
        }).detach();
    }

    bool is_prime(uint64_t num) {
        if (num < 2) return false;
        if (num == 2) return true;
        if (num % 2 == 0) return false;
        for (uint64_t i = 3; i * i <= num; i += 2) {
            if (num % i == 0) return false;
        }
        return true;
    }
};

struct NextPrimeUInt64 {
    uint64_t start;

    NextPrimeUInt64(uint64_t start) : start(start) {}

    AwaitablePrime operator co_await() { return {start}; }
};

GlobalAxiomQueue GlobalAxioms;

void generate_axioms() {
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<uint64_t> dis;

    for (int i = 0; i < 10; ++i) {
        GlobalAxioms.push(Axiom(dis(gen)));
    }
}

std::queue<Axiom> processed_axioms;

class DispatchWork {
public:
    struct promise_type {
        DispatchWork get_return_object() { return {}; }
        std::suspend_always initial_suspend() { return

//

/* 
Q:Provide a C++20 co_routines example involving at least two co_routines.

In this example, we'll implement a simple generator-like structure using C++20 coroutines. We'll have two coroutines: one for generating a sequence of numbers and the other for consuming the generated numbers by squaring them.

First, let's start by including the necessary headers and defining a generator class that will help us use coroutines easily:

cpp
*/

#include <iostream>
#include <coroutine>
#include <optional>

template<typename T>
class generator {
public:
    struct promise_type;
    using handle_type = std::coroutine_handle<promise_type>;

    generator(handle_type handle) : handle_(handle) {}
    ~generator() { if (handle_) handle_.destroy(); }

    generator(const generator&) = delete;
    generator& operator=(const generator&) = delete;

    generator(generator&& other) noexcept : handle_(other.handle_) {
        other.handle_ = nullptr;
    }
    generator& operator=(generator&& other) noexcept {
        if (this != &other) {
            if (handle_) handle_.destroy();
            handle_ = other.handle_;
            other.handle_ = nullptr;
        }
        return *this;
    }

    bool next() { return handle_ && !handle_.done() && (handle_.resume(), !handle_.done()); }
    T value() const { return handle_.promise().value_; }

private:
    handle_type handle_;

    struct promise_type {
        T value_;
        std::optional<std::exception_ptr> exception_;

        auto get_return_object() { return generator{handle_type::from_promise(*this)}; }
        auto initial_suspend() { return std::suspend_always{}; }
        auto final_suspend() noexcept { return std::suspend_always{}; }
        void unhandled_exception() { exception_ = std::current_exception(); }
        auto yield_value(const T value) {
            value_ = value;
            return std::suspend_always{};
        }
        void return_void() {}
    };
};
/* 
Now, let's create two coroutines, number_generator and square_consumer. number_generator generates numbers from start to end, and square_consumer consumes the generated numbers and squares them.

cpp
*/
generator<int> number_generator(int start, int end) {
    for (int i = start; i <= end; ++i) {
        co_yield i;
    }
}

generator<int> square_consumer(generator<int>& number_gen) {
    while (number_gen.next()) {
        int value = number_gen.value();
        co_yield value * value;
    }
}
/* 
Finally, we can use these two coroutines together in the main function to generate and square numbers:

cpp
*/
int main() {
    auto numbers = number_generator(1, 5);
    auto squares = square_consumer(numbers);

    while (squares.next()) {
        std::cout << "Square: " << squares.value() << std::endl;
    }

    return 0;
}
/* 
When you run this program, you should see the following output:

makefile

Square: 1
Square: 4
Square: 9
Square: 16
Square: 25
*/
