/*Q:Provide an example of a unordered_map that supports true parallel access, without the use of a third party library.*/
#include <vector>
#include <unordered_map>
#include <mutex>
#include <thread>
#include <iostream>

template <typename KEY, typename VALUE>
class ConcurrentUnorderedMap {
private:
    struct Bucket {
        std::unordered_map<KEY, VALUE> map;
        std::mutex mtx;
    };

    std::vector<Bucket> buckets;
    size_t num_buckets;

    Bucket& get_bucket(KEY key) {
        // Use the key to determine the bucket
        KEY bucket_index = std::hash<KEY>{}(key) % num_buckets;
        return buckets[bucket_index];
    }

public:
    ConcurrentUnorderedMap(const KEY num_buckets = 0) : num_buckets(num_buckets), buckets(num_buckets) {}

    void insert(KEY key, Value value) {
        Bucket& bucket = get_bucket(key);
        std::lock_guard<std::mutex> lock(bucket.mtx);
        bucket.map[key] = value;
    }
	
	VALUE& operator [] (const KEY& key) {
		Bucket& bucket = get_bucket(key);
		std::lock_guard<std::mutex> lock(bucket.mtx);
		return bucket.map[key];
	}

    VALUE get(const KEY& key) {
        Bucket& bucket = get_bucket(key);
        std::lock_guard<std::mutex> lock(bucket.mtx);
        return bucket.map[key];
    }
};

int main() {
    ConcurrentUnorderedMap<int,int> map(10);

    std::vector<std::thread> threads;
    for (int i = 0; i < 100; ++i) {
        threads.push_back(std::thread([i, &map]() {
            map.insert(i, i * 2);
            std::cout << "Inserted: " << i << ", " << i * 2 << std::endl;
            std::cout << "Retrieved: " << i << ", " << map.get(i) << std::endl;
        }));
    }

    for (auto& thread : threads) {
        thread.join();
    }

    return 0;
}

// Usage example
//#include <tbb/concurrent_unordered_map.h>
//#include <tbb/parallel_for_each.h>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <execution>

int main() {
    ConcurrentUnorderedMap<int, std::vector<int>> map{};

    // Insert elements in parallel
    std::vector<int> keys = {1, 2, 3, 4, 5};
    std::for_each(std::execution::par_unseq, keys.begin(), keys.end(), [&map](int key) {
        map[key] = {key*1, key*2, key*3};
    });

    // Access elements in parallel
    std::for_each(std::execution::par_unseq, keys.begin(), keys.end(), [](const auto& pair) {
        int key = pair.first;
        for (int value : pair.second) {
            // do something with key and value
        }
    });

    return 0;
}

