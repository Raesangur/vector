#!/bin/bash
# Get variables
if [ "$#" -eq "0" ]
  then
    clangPath = /usr/bin/clang++-10
    gccPath = /usr/bin/g++-10
else
    clangPath = $1
    gccPath = $2
fi

echo "Clang++: " $clangPath
echo "G++: " $gccPath


# Make sure the repository is up-to-date
git pull

# Prepare build directories
cd build
rm -rf clang++ g++
mkdir clang++ g++

# Build Clang++ project
echo "Building with clang++"

