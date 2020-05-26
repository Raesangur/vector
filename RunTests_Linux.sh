#!/bin/bash
# Get variables
if [ "$#" -eq "0" ]
  then
    clangPath=/usr/bin/clang++-10
    gccPath=/usr/bin/g++-10
else
    clangPath=$1
    gccPath=$2
fi

echo "Clang++: " $clangPath
echo "G++: " $gccPath


# Make sure the repository is up-to-date
git pull > /dev/null 2>&1

# Make sure clang-tidy can be run
chmod +x run-clang-tidy.py > /dev/null 2>&1

# Prepare build directories
cd build
rm -rf clang++ g++
mkdir clang++ g++

# Build Clang++ project and compile
echo "------------------------------"
echo "Building with clang++"
cd clang++
cmake ./../.. -D CMAKE_CXX_COMPILER=$clangPath > /dev/null 2>&1
cmake --build .
cd ..

# Build G++ project and compile
echo "------------------------------"
echo "Building with g++"
cd g++
cmake ./../.. -D CMAKE_CXX_COMPILER=$gccPath > /dev/null 2>&1
cmake --build .
cd ..

# Run Clang-Tidy on project
echo "------------------------------"
echo "Running clang-tidy"
cd clang++
../../run-clang-tidy.py -quiet
cd ..

# Run Clang Sanitizers on project
echo "-----------------------------"
echo "Running Clang Sanitizers"
cd clang++
mkdir address-sanitizer thread-sanitizer leak-sanitizer undefined-behavior-sanitizer
echo "Address Sanitizer:"
cd address-sanitizer
cmake ../../../. -D CMAKE_CXX_COMPILER=$clangPath -DPEL_CLANG_USE_ADDRESS_SANITIZER=True > /dev/null 2>&1
cmake --build .
cd ..
echo "Thread Sanitizer:"
cd thread-sanitizer
cmake ../../../. -D CMAKE_CXX_COMPILER=$clangPath -DPEL_CLANG_USE_THREAD_SANITIZER=True > /dev/null 2>&1
cmake --build .
cd ..
echo "Leak Sanitizer:"
cd leak-sanitizer
cmake ../../../. -D CMAKE_CXX_COMPILER=$clangPath -DPEL_CLANG_USE_LEAK_SANITIZER=True > /dev/null 2>&1
cmake --build .
cd ..
echo "Undefined Behavior Sanitizer:"
cd undefined-behavior-sanitizer
cmake ../../../. -D CMAKE_CXX_COMPILER=$clangPath -DPEL_CLANG_USE_UNDEFINED_BEHAVIOR_SANITIZER=True > /dev/null 2>&1
cd ../..
