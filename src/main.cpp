/**
 * \file
 * \author  Pascal-Emmanuel Lachance
 * \p       https://www.github.com/Raesangur
 * ------------------------------------------------------------------------------------------------
 * MIT License
 * Copyright (c) 2020 Pascal-Emmanuel Lachance | Ràësangür
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 * and associated documentation files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or
 * substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 * BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
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

        pel::vector<int> vec1 = pel::vector<int>(ilist);
        std::cout << vec1.to_string() << "\n";

        incrementVector(vec1);
        std::cout << vec1.to_string() << "\n";

        vec1.push_back(ilist);
        std::cout << vec1.to_string() << "\n";

        vec1.emplace_back(magicNumber_42);
        std::cout << vec1.to_string() << "\n";

        sortVector(vec1);
        std::cout << vec1.to_string() << "\n";

        return 0;
    }
    catch(...)
    {
        std::cout << "Uh oh\n";
        return 1;
    }
}
