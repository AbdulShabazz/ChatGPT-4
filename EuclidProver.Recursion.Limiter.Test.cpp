#include <iostream>
#include <thread>
#include <atomic>
#include <cstdint>
#include <functional>

const std::size_t num_threads = std::thread::hardware_concurrency() - 1; // Reserve, minus the main thread

class RecursionLimiter
{
public:
    static void set_recursion_limit(uint64_t limit)
    {
        recursion_limit = limit;
    }

    class Invoke
    {
    public:
        Invoke(uint64_t initial_depth)
            : depth(initial_depth),
              recursion_count(thread_local_recursion_count())
        {
            if (depth)
            {
                *recursion_count += depth;
            }
        }

        ~Invoke()
        {
            if (recursion_count)
            {
                *recursion_count -= depth;
            }
        }

        bool acquired()
        {
            if (!recursion_count)
            {
                recursion_count = thread_local_recursion_count();
                return true;
            }

            if (*recursion_count + depth < recursion_limit)
            {
                *recursion_count += depth;
                 return true;
            }

            return false;
        }

        bool release()
        {
            bool retval{};
            
            if (recursion_count)
            {
                *recursion_count -= depth;
                 retval = true;
            }
            
            return retval;
        }

    private:
        uint64_t depth;
        std::atomic<uint64_t>* thread_local_recursion_count()
        {
            thread_local std::atomic<uint64_t> rc{0};
            return &rc;
        }

        std::atomic<uint64_t>* recursion_count;
    };

private:
    static inline std::atomic<uint64_t> recursion_limit;
};

int main()
{
    RecursionLimiter::set_recursion_limit(32535);

    uint64_t calllim{};
    
    std::function<void(void)> fn = [&calllim,&fn]()
    {
        RecursionLimiter::Invoke limiter(1);
        if (limiter.acquired())
        {
            std::cout << "1 stack call made. Call limit: " << calllim++ << std::endl;
        }
        
        fn();
    };
    
    //fn();
    
    while(1)
    {
        RecursionLimiter::Invoke limiter(1);
        if (limiter.acquired())
        {
            std::cout << "1 stack call made. Call limit: " << calllim++ << std::endl;
            limiter.release();
        }
        
        else
        {
            std::cout << "reservation failed. " << std::endl;   
        }
    }
    
    return 0;
}
