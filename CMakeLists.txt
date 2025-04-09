cmake_minimum_required (VERSION 3.12)
project(regexp LANGUAGES CXX)

find_package(Doxygen REQUIRED)

set(CMAKE_C_COMPILER "/usr/bin/clang")
set(CMAKE_CXX_COMPILER "/usr/bin/clang++")
set(BUILD_TESTS ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS YES)

include(GNUInstallDirs)
doxygen_add_docs(docs
    ${CMAKE_SOURCE_DIR}/libtransformer/include
    ${CMAKE_SOURCE_DIR}/libtransformer/src
    ${CMAKE_SOURCE_DIR}/transformer/src
    COMMENT "Generating API documentation"
)

add_compile_options(-Wall -Wextra -Wpedantic -Werror)
set_property(GLOBAL PROPERTY CXX_STANDARD 20)
set_property(GLOBAL PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(GLOBAL PROPERTY CXX_EXTENSIONS OFF)
set_property(GLOBAL PROPERTY POSITION_INDEPENDENT_CODE ON)


if(${BUILD_TESTS})
    enable_testing()
endif()

add_subdirectory(libtransformer)
add_subdirectory(transformer)