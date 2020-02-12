#include <vector>
#include <array>
#include <string>
#include <utility>
#include "vector.hpp"
#include <type_traits>

#include <iostream>

struct mystruct
{
    mystruct()
    {
        a = 0;
        b = 1;
        c = 2;
        d = 3;
        e = 4;
        f = 5;
        f1 = 0.0;
        f2 = 1.0;
        f3 = 3.141592653589793236448464323;
        array = { true, false, true, false, false, true, false, true, false, false };
    }

    int a;
    int b;
    int c;
    int d;
    int e;
    int f;
    double f1;
    double f2;
    double f3;
    std::array<bool, 10> array;
};

template<typename ItemType>
void printVec(std::vector<ItemType>& vector)
{
    std::for_each(vector.cbegin(), vector.cend(), [](const ItemType& val)
                  {
                      std::cout << val << '\n';
                  });
    std::cout << "----------------\n";
}

template<typename ItemType>
void printVec(pel::vector<ItemType>& vector)
{
    if constexpr (std::is_same<ItemType, mystruct>())
    {
        printStructVec(vector);
    }
    else
    {
        std::for_each(vector.cbegin(), vector.cend(), [](ItemType& val)
                      {
                          std::cout << val << '\n';
                      });
        std::cout << "----------------\n";
    }
}

inline void printStructVec(pel::vector<mystruct>& vector)
{
    std::for_each(vector.cbegin(), vector.cend(), [](mystruct& val)
                  {
                      std::cout << "A: " << val.a << '\n';
                      std::cout << "B: " << val.b << '\n';
                      std::cout << "C: " << val.c << '\n' << "-----" << '\n';
                  });
    std::cout << "----------------\n";
}


int main()
{
    std::vector<int> testvec = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    printVec(testvec);
    std::shift_right(testvec.begin() + 2, testvec.end(), 1);
    printVec(testvec);


    try
    {
        pel::vector<int> vec(5);
        vec[0] = 10;
        vec[1] = 67;
        vec[2] = 0;
        vec[3] = 61;
        vec[4] = 12409;

        pel::vector<int> vec2(vec.begin(), vec.end());

        std::sort(vec2.begin(), vec2.end());

        vec.front() = 128;
        vec.back() = 256;

        
        printVec(vec);
        printVec(vec2);


        vec.reserve(vec.length() * 2);
        printVec(vec);

        vec.resize(vec.capacity());
        int i = 0;
        std::generate(vec.begin(), vec.end(), [&]()
                      {
                          return ++i;
                      });
        printVec(vec);

        vec.resize(vec.capacity() / 2);
        std::generate(vec.begin(), vec.end(), [&]()
                      {
                          return --i * 2;
                      });
        printVec(vec);

        vec2.clear();
        printVec(vec2);
        std::cout << vec2.capacity();
        std::cout << '\n' << vec2.length() << '\n';

        std::cout << "----------------\n";
        pel::vector<mystruct> vec3(0);


        printVec(vec3);
        mystruct a;
        mystruct b;
        b.b = 0;
        mystruct c;
        c.c = 0;
        vec3.push_back(a);
        vec3.push_back(b);
        vec3.push_back(c);
        vec3.push_back(b);
        vec3.push_back(a);
        printVec(vec3);
        vec3.pop_back();
        printVec(vec3);

        while (vec3.isEmpty() == false)
        {
            vec3.pop_back();
        }
        printVec(vec3);
        std::cout << "size : " << vec3.length() << "\ncapacity : " << vec3.capacity() << '\n';
        vec3.shrink_to_fit();
        std::cout << "size : " << vec3.length() << "\ncapacity : " << vec3.capacity() << '\n';
        std::cout << "--------------\n--------------\n--------------\n\n";

        printVec(vec);
        vec.insert(1024, vec.length());
        vec.emplace_back(2048);
        printVec(vec);

        return 0;
    }
    catch(...)
    {
        std::cout << "\n ----------exception-----------\n";
        return -1;
    }
}