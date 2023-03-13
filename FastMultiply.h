#include <cmath>
#include <type_traits>

template <typename NumberBase = uint64_t>
NumberBase PowerUInt64(const NumberBase& ConstNumberRef,
                       const NumberBase& ConstExponentRef) {
    static_assert(std::is_arithmetic_v<NumberBase>, "NumericDataType must be an arithmetic type");

    if (ConstExponentRef == 0) {
        return NumberBase{1};
    }

    double log_base = std::log(static_cast<double>(ConstNumberRef));
    double log_result = std::log(static_cast<double>(ConstExponentRef));
    double log_final = log_result / log_base;
    NumberBase int_part = static_cast<NumberBase>(std::floor(log_final));
    double frac_part = log_final - int_part;
    NumberBase result = static_cast<NumberBase>(std::pow(ConstNumberRef, frac_part) * std::pow(2, int_part));
    result *= ConstExponentRef;

    return result;
}
