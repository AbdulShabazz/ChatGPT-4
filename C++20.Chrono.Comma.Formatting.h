#include <chrono>
#include <sstream>
#include <locale>
#include <iomanip>

std::string format_with_commas(std::chrono::milliseconds ms)
{
    std::stringstream ss;
    ss.imbue(std::locale(""));
    ss << std::fixed << ms.count();
    return ss.str();
}

int main()
{
    auto ms = std::chrono::milliseconds(123456789);
    std::cout << "Formatted time: " << format_with_commas(ms) << "ms\n";
    return 0;
}
