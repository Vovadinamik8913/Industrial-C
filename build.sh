rm -r build
rm Doxyfile
mkdir build && cd build
conan install ../conanfile.txt --build=missing  --output-folder="../build"
cmake ../ -DCMAKE_BUILD_TYPE=Release
cmake --build . --target=docs
cmake --build . --target=format
cmake ../
cmake --build .
cmake --install . --prefix ./install
ctest -V -j4
doxygen -s -g ../Doxyfile