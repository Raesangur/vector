/**
 * \file
 */

#include "./vector.hpp"

#include <algorithm>


/**
 * \brief   This is a test function that increments all the values contained in a vector
 */
template<typename T>
void incrementVector(pel::vector<T>& vec) noexcept
{
    for(T& i: vec)
    {
        i++;
    }
}


template<typename T>
void sortVector(pel::vector<T>& vec) noexcept
{
    std::sort(vec.begin(), vec.end());
}