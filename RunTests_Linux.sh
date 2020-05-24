# Make sure the repository is up-to-date
git pull

# Prepare build directories
cd build
rm -rf clang++ g++
mkdir clang++ g++

# Build Clang++ project
echo "Building with clang++ located at " $0
