make app=str
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Coverage ..
cmake --build .
ctest -VV