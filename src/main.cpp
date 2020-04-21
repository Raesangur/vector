#include <iostream>

#include "./vector.hpp"
#include "./tests.inl"

constexpr std::initializer_list<int> ilist = {100, 400, 69, 420, 00, 0x72, 643, 65535, 1, 2, 3};

int
main()
{
    pel::vector<int> vec1 = pel::vector<int>(ilist);
    std::cout << vec1.to_string() << "\n";

    incrementVector(vec1);
    std::cout << vec1.to_string() << "\n";

    sortVector(vec1);
    std::cout << vec1.to_string() << "\n";

    return 0;
}
