rm -r build
mkdir build && cd build
conan install ../conanfile.txt --build=missing  --output-folder="../build"
cmake ../ -DCMAKE_BUILD_TYPE=Release
cmake --build .
cmake --build . --target docs
ctest -v -j4