#!/bin/bash

# ------------------------------
# Get variables

# https://unix.stackexchange.com/questions/129391/passing-named-arguments-to-shell-scripts
for ARGUMENT in "$@"
do
    KEY=$(echo $ARGUMENT | cut -f1 -d=)
    VALUE=$(echo $ARGUMENT | cut -f2 -d=)

    case "$KEY" in
        gccPath)          clangPath=${VALUE} ;;
        clangPath)        clangPath=${VALUE} ;;
        *)
    esac
done

# Check if variables exist and assign values to them if they dont
if [ -z "$gccPath" ]
then
    gccPath=/usr/bin/g++-10
else
    echo "G++: " $gccPath
fi

if [ -z "$clangPath" ]
then
    clangPath=/usr/bin/clang++-10
else
    echo "Clang++: " $clangPath
fi

# Temporary Exit - TO REMOVE
exit

# ------------------------------
# Make sure the repository is up-to-date
git pull > /dev/null 2>&1

# Make sure clang-tidy can be run
chmod +x ./tools/run-clang-tidy.py > /dev/null 2>&1

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
../../tools/run-clang-tidy.py -quiet
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
#cmake --build .
cd ..
echo "Leak Sanitizer:"
cd leak-sanitizer
cmake ../../../. -D CMAKE_CXX_COMPILER=$clangPath -DPEL_CLANG_USE_LEAK_SANITIZER=True > /dev/null 2>&1
cmake --build .
cd ..
echo "Undefined Behavior Sanitizer:"
cd undefined-behavior-sanitizer
cmake ../../../. -D CMAKE_CXX_COMPILER=$clangPath -DPEL_CLANG_USE_UNDEFINED_BEHAVIOR_SANITIZER=True > /dev/null 2>&1
#cmake --build .
cd ../../..

# Generate Doxygen documentation
echo "-----------------------------"
echo "Generating documentation"
doxygen ./tools/Doxyfile
