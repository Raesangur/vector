#include "./vector.hpp"

#include <algorithm>


template<typename T>
void incrementVector(pel::vector<T>& vec)
{
    for(T& i: vec)
    {
        i++;
    }
}


template<typename T>
void sortVector(pel::vector<T>& vec)
{
    std::sort(vec.begin(), vec.end());
}