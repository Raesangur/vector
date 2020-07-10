/**
 * \file
 */

#include "./vector.hpp"

#include <algorithm>
#include <chrono>
#include <vector>

/// https://stackoverflow.com/questions/1861294/how-to-calculate-execution-time-of-a-code-snippet-in-c
class Timer
{
public:
    Timer() noexcept : beg_(clock_::now())
    {
    }

    void
    reset() noexcept
    {
        beg_ = clock_::now();
    }

    [[nodiscard]] double
    elapsed() const noexcept
    {
        return std::chrono::duration_cast<second_>(clock_::now() - beg_).count();
    }

private:
    using clock_  = std::chrono::high_resolution_clock;
    using second_ = std::chrono::duration<double, std::milli>;
    std::chrono::time_point<clock_> beg_;
};


/**
 * \brief   This is a test function that increments all the values contained in a vector
 */
template<typename T>
void
incrementVector(pel::vector<T>& vec) noexcept
{
    for(T& i : vec)
    {
        i++;
    }
}


template<typename T>
void
sortVector(pel::vector<T>& vec) noexcept
{
    std::sort(vec.begin(), vec.end());
}



double
constructVectorNormally(std::uint32_t iterations, std::size_t elements = 1)
{
    const Timer       tmr;
    const std::string copied = "Hello World";
    for(std::uint32_t i = 0; i < iterations; i++)
    {
        pel::vector<std::string> vec(elements, copied);
    }
    const double result = tmr.elapsed();
    std::cout << "Normal test: " << result << '\n';
    return result;
}

double
constructNormalVector(std::uint32_t iterations, std::size_t elements = 1)
{
    const Timer       tmr;
    const std::string copied = "Hello World";
    for(std::uint32_t i = 0; i < iterations; i++)
    {
        std::vector<std::string> vec(elements, copied);
    }
    const double result = tmr.elapsed();
    std::cout << "Base test: " << result << '\n';
    return result;
}

double
constructVectorByMove(std::uint32_t iterations, std::size_t elements = 1)
{
    const Timer tmr;
    for(std::uint32_t i = 0; i < iterations; i++)
    {
        pel::vector<std::string> vec(elements, std::move("Hello World"));
    }
    const double result = tmr.elapsed();
    std::cout << "Move test: " << result << '\n';
    return result;
}
