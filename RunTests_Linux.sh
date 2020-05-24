# Get variables
if [$1 -eq 0]
  then
    clangPath = /usr/bin/clang++-10
else
    clangPath = $1

if [$2 -eq 0]
  then
    gccPath = /usr/bin/g++-10
else
    gccPath = $2

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

