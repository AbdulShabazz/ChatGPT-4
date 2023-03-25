#include <type_traits>
#include <limits>

template<typename ui64>
concept UnsignedInteger = std::is_unsigned_v<ui64>;

template<typename ui64 = uint64_t>
requires UnsignedInteger<ui64>
class BigInt
{
    public:
        static constexpr ui64 BASE = std::numeric_limits<ui64>::max() / 2;
};