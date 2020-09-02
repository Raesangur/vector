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

#include <array>
#include <iostream>
#include <memory_resource>

#include "./tests.inl"
#include "./vector.hpp"


int
main()
{
    try
    {
        std::cout << "Starting vector project\n";

        int toto = 0;

        std::array<std::uint8_t, 2000>      bigArray{0};
        std::pmr::monotonic_buffer_resource memResource{bigArray.data(), bigArray.size()};
        pel::vector<int, std::pmr::polymorphic_allocator<int>> myVec(
          10,
          [&]() {
              return toto++;
          },
          std::pmr::polymorphic_allocator<int>{&memResource});

        myVec.push_back(toto);
        myVec.push_back(++toto);
        myVec.push_back(++toto);
        myVec.push_back(++toto);

        std::cout << "vector's size: " << sizeof(myVec) << '\n';
        std::cout << "vector's iterator's size" << sizeof(myVec.begin()) << '\n';
        std::cout << "vector's allocator's size" << sizeof(myVec.get_allocator()) << '\n';
        std::cout << myVec.to_string() << '\n';
        return static_cast<int>(myVec.length());
    }
    catch(...)
    {
        // std::cout << "Uh oh\n";
        return 1;
    }
}
