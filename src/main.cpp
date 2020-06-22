/**
 * @file   vector/src/main.cpp 
 */

#include <iostream>

#include "./tests.inl"
#include "./vector.hpp"

constexpr std::initializer_list<int> ilist = {100, 400, 69, 420, 00, 0x72, 643, 65535, 1, 2, 3};

int
main()
{
    std::cout << "Starting vector project\n";
    try
    {
        constexpr int magicNumber_42 = 42;

        std::cout << "Constructing vector\n";
        pel::vector<int> vec1 = pel::vector<int>(ilist);
        std::cout << vec1.to_string() << "\n";

        std::cout << "Incrementing all values in vector\n";
        incrementVector(vec1);
        std::cout << vec1.to_string() << "\n";

        vec1.push_back(ilist);
        std::cout << vec1.to_string() << "\n";

        vec1.emplace_back(magicNumber_42);
        std::cout << vec1.to_string() << "\n";

        sortVector(vec1);
        std::cout << vec1.to_string() << "\n";


        std::cout << "Vector stuff\n"; 
        return 0;
    }
    catch (...)
    {
        std::cout << "Uh oh\n";
        return 1;
    }
}
