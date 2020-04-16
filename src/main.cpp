#include <array>
#include <iostream>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

#include "./vector.hpp"


int
main()
{
    pel::vector<int> vec1 = pel::vector<int>({100, 400, 69, 420, 00, 0x72, 643, 65535, 1, 2, 3});
    std::cout << vec1.to_string() << "\n";

    for(int& i : vec1)
    {
        i++;
    }
    std::cout << vec1.to_string() << "\n";

    std::sort(vec1.begin(), vec1.end());
    std::cout << vec1.to_string() << "\n";

    return 0;
}
