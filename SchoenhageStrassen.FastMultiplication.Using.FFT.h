#include <complex>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iostream>

void fft(std::vector<std::complex<double>>& a, bool invert) {
    // Implement FFT and IFFT
}

std::vector<int> multiplyPolynomials(const std::vector<int>& a, const std::vector<int>& b) {
    // Implement polynomial multiplication using FFT
}

std::vector<int> integerToPolynomial(const std::vector<int>& number) {
    // Implement integer to polynomial conversion for std::vector<int>
}

std::vector<int> polynomialToInteger(const std::vector<int>& poly) {
    // Implement polynomial to integer conversion for std::vector<int>
}

std::vector<int> schoenhageStrassenMultiplication(const std::vector<int>& a, const std::vector<int>& b) {
    // Convert integer inputs to polynomial representations
    std::vector<int> a_poly = integerToPolynomial(a);
    std::vector<int> b_poly = integerToPolynomial(b);

    // Multiply the polynomials using FFT
    std::vector<int> result_poly = multiplyPolynomials(a_poly, b_poly);

    // Convert the resulting polynomial back to an integer
    std::vector<int> result = polynomialToInteger(result_poly);

    return result;
}

int main() {
    std::vector<int> a = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    std::vector<int> b = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    std::vector<int> result = schoenhageStrassenMultiplication(a, b);
    
    std::cout << "Result: ";
    for (const auto& digit : result) {
        std::cout << digit;
    }
    std::cout << std::endl;
    return 0;
}

0099 000999
0099 000999
9801 998001