#include <iostream>

#include "./tests.inl"
#include "./vector.hpp"

constexpr std::initializer_list<int> ilist = {100, 400, 69, 420, 00, 0x72, 643, 65535, 1, 2, 3};

int
main()
{
    try
    {
        pel::vector<int> vec1 = pel::vector<int>(ilist);
        std::cout << vec1.to_string() << "\n";

        incrementVector(vec1);
        std::cout << vec1.to_string() << "\n";

        sortVector(vec1);
        std::cout << vec1.to_string() << "\n";

        vec1.push_back(ilist);
        std::cout << vec1.to_string() << "\n";

        return 0;
    }
    catch (...)
    {
        return 1;
    }
}
