rd /S /Q build
mkdir build
cd build

mkdir VS2019
cd VS2019
cmake -G "Visual Studio 16 2019" ./../..

cd..
pause