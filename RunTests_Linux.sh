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

