
__x86i64Int operator*(const __x86i64Int& other) const
{
    __x86i64Int result;
    result.digits_.resize(digits_.size() + other.digits_.size());

    // Chunk size for the outer loop
    const uint64_t chunk_size = 1000;

    // Spawn threads to calculate the inner loop for each chunk
    std::vector<std::thread> threads;
    for (uint64_t i = 0; i < digits_.size(); i += chunk_size)
    {
        threads.emplace_back([this, &other, &result, i, chunk_size]() {
            for (uint64_t j = i; j < i + chunk_size && j < digits_.size(); j++)
            {
                uint64_t carry = 0;
                for (uint64_t k = 0; k < other.digits_.size() || carry > 0; k++)
                {
                    uint64_t prod = result.digits_[j + k] + carry +
                                     digits_[j] *
                                         (k < other.digits_.size() ? other.digits_[k] : 0);
                    result.digits_[j + k] = prod % BASE;
                    carry = prod / BASE;
                }
            }
        });
    }

    // Wait for all threads to finish
    for (auto& thread : threads)
    {
        thread.join();
    }

    result.trim();
    result.sign_ = sign_ * other.sign_;
    return result;
}
