#include <vector>
#include "vector.hpp"

#include <iostream>


template<typename ItemType>
void printVec(pel::vector<ItemType>& vector)
{
    std::for_each(vector.cbegin(), vector.cend(), [](ItemType& val)
        {
            std::cout << val << '\n';
        });
    std::cout << "----------------\n";
}

int main()
{
    std::vector<int> testvec = { 12, 0 };
    testvec.clear();
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


        vec.reserve(vec.size() * 2);
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
        std::cout << '\n' << vec2.size() << '\n';

        std::cout << "----------------\n";
        //pel::vector<std::shared_ptr<int>> vec3(0);

        std::shared_ptr<int> int1 = std::make_shared<int>(1);
        std::shared_ptr<int> int2 = std::make_shared<int>(2);
        std::shared_ptr<int> int3 = std::make_shared<int>(3);
        std::shared_ptr<int> int4 = std::make_shared<int>(4);
       /* printVec(vec3);
        vec3.push_back(int1);
        vec3.push_back(int2);
        vec3.push_back(int3);
        vec3.push_back(int4);
        printVec(vec3);*/


        return 0;
    }
    catch(std::exception e)
    {
        std::cout << e.what();
        return -1;
    }
}