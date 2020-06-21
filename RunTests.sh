#!/bin/bash

# ------------------------------
# Get variables

# https://unix.stackexchange.com/questions/129391/passing-named-arguments-to-shell-scripts
for ARGUMENT in "$@"
do
    KEY=$(echo $ARGUMENT | cut -f1 -d=)
    VALUE=$(echo $ARGUMENT | cut -f2 -d=)

    case "$KEY" in
        gccPath)          clangPath=${VALUE} ;;                 # String : Path to the g++ executable of choice
        clangPath)        clangPath=${VALUE} ;;                 # String : Path to the clang++ executable of choice
        runGcc)           runGcc=${VALUE} ;;                    # Bool : Run G++ on project
        runClang)         runClang=${VALUE} ;;                  # Bool : Run clang++ on project. Also disables clang-tidy and sanitizers.
        runClangTidy)     runClangTidy=${VALUE} ;;              # Bool : Run clang-tidy on project. Is also disabled by disabling clang.
        runSanitizers)    runSanitizers=${VALUE} ;;             # Bool : Run clang sanitizers on project. Can be fine-tuned with the following 4 parameters:
        runASan)          runASan=${VALUE} ;;                   # Bool : Run clang Address Sanitizer on project.
        runTSan)          runTSan=${VALUE} ;;                   # Bool : Run clang Thread Sanitizer on project.
        runLSan)          runLSan=${VALUE} ;;                   # Bool : Run clang Leak Sanitizer on project.
        runUBSan)         runUBSan${VALUE} ;;                   # Bool : Run clang Undefined Behavior Sanitizer on project.
        runDoxygen)       runDoxygen=${VALUE} ;;                # Bool : Run doxygen and generate documentation for project
        *)                echo "Invalid argument " ${ARGUMENT}
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

# Check if parts of the program should be skipped
if [ -z "$runGcc" ]
then
   runGcc="true"
fi

if [ -z "$runClang" ]
then
   runClang="true"
fi

if [ -z "$runClangTidy" ]
then
   runClangTidy="true"
fi


if [ -z "$runSanitizers" ]
then
    runSanitizers="true"
fi

if [ -z "$runASan" ]
then
   runASan="true"
fi

if [ -z "$runTSan" ]
then
   runTSan="true"
fi

if [ -z "$runLSan" ]
then
   runLSan="true"
fi

if [ -z "$runUBSan" ]
then
   runUBSan="true"
fi

if [ -z "$runDoxygen" ]
then
   runDoxygen="true"
fi


# ------------------------------
# Make sure the repository is up-to-date
git pull > /dev/null 2>&1

# Make sure clang-tidy can be run
chmod +x ./tools/run-clang-tidy.py > /dev/null 2>&1

# Clean and prepare build directories
cd build
rm -rf clang++ g++

# Build Clang++ project and compile
if [ "$runClang" == "true" ]
then
    echo "------------------------------"
    echo "Building with clang++"
    mkdir clang++
    cd clang++
    cmake ./../.. -D CMAKE_CXX_COMPILER=$clangPath > /dev/null 2>&1
    cmake --build .
    cd ..
else
    echo "Skipping clang"
fi

# Build G++ project and compile
if [ "$runGcc" == "true" ]
then
    echo "------------------------------"
    echo "Building with g++"
    mkdir g++
    cd g++
    cmake ./../.. -D CMAKE_CXX_COMPILER=$gccPath > /dev/null 2>&1
    cmake --build .
    cd ..
else
    echo "Skipping G++"
fi

# Run Clang-Tidy on project
if [ "$runClangTidy" == "true" ] && [ "$runClang" == "true" ]
then
    echo "------------------------------"
    echo "Running clang-tidy"
    cd clang++
    ../../tools/run-clang-tidy.py -quiet > /dev/null 2>&1
    cd ..
else
    echo "Skipping clang-tidy"
fi


# Run Clang Sanitizers on project
if [ "$runSanitizers" == "true" ] && [ "$runClang" == "true" ]
then
    echo "-----------------------------"
    echo "Running Clang Sanitizers"
    cd clang++
    if [ "$runASan" == "true" ]
    then
        echo "Address Sanitizer:"
        mkdir address-sanitizer
        cd address-sanitizer
        cmake ../../../. -D CMAKE_CXX_COMPILER=$clangPath -DPEL_CLANG_USE_ADDRESS_SANITIZER=True > /dev/null 2>&1
        cmake --build .
        cd ..
    fi
    if [ "$runTSan" == "true" ]
    then
        echo "Thread Sanitizer:"
        mkdir thread-sanitizer
        cd thread-sanitizer
        cmake ../../../. -D CMAKE_CXX_COMPILER=$clangPath -DPEL_CLANG_USE_THREAD_SANITIZER=True > /dev/null 2>&1
        cmake --build .
        cd ..
    fi
    if [ "$runLSan" == "true" ]
    then
        echo "Leak Sanitizer:"
        mkdir leak-sanitizer
        cd leak-sanitizer
        cmake ../../../. -D CMAKE_CXX_COMPILER=$clangPath -DPEL_CLANG_USE_LEAK_SANITIZER=True > /dev/null 2>&1
        cmake --build .
        cd ..
    fi
    if [ "$runUBSan" == "true" ]
    then
        echo "Undefined Behavior Sanitizer:"
        mkdir undefined-behavior-sanitizer
        cd undefined-behavior-sanitizer
        cmake ../../../. -D CMAKE_CXX_COMPILER=$clangPath -DPEL_CLANG_USE_UNDEFINED_BEHAVIOR_SANITIZER=True > /dev/null 2>&1
        cmake --build .
        cd ..
    fi
    cd ..
fi

# Generate Doxygen documentation
cd ..                               # Return to project root directory
if [ "$runDoxygen" == "true" ]
then
    echo "-----------------------------"
    echo "Generating documentation"
    doxygen ./tools/Doxyfile
fi


