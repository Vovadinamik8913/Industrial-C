cmake_minimum_required (VERSION 3.12)
project(basic_program)

find_package(ZLIB REQUIRED)
find_package(BZip2 REQUIRED)
find_package(fmt REQUIRED)

set(CMAKE_C_COMPILER "/usr/bin/clang")
set(CMAKE_CXX_COMPILER "/usr/bin/clang++")
set(BUILD_TESTS ON)

find_package(Doxygen REQUIRED)
if(Doxygen_FOUND)
    set(DOXYGEN_PROJECT_NAME "Compressor")
    set(DOXYGEN_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/docs")
    set(DOXYGEN_RECURSIVE YES)
    set(DOXYGEN_EXTRACT_ALL YES)
    
    doxygen_add_docs(docs
        ${CMAKE_SOURCE_DIR}/libcompressor/include
        ${CMAKE_SOURCE_DIR}/libcompressor/src
        ${CMAKE_SOURCE_DIR}/compressor/src
        COMMENT "Generating API documentation"
    )
endif()

add_compile_options(-Wall -Wextra -Wpedantic -Werror)

set_property(GLOBAL PROPERTY CXX_STANDARD 20)
set_property(GLOBAL PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(GLOBAL PROPERTY CXX_EXTENSIONS OFF)
set_property(GLOBAL PROPERTY POSITION_INDEPENDENT_CODE ON)

add_subdirectory(libcompressor)
add_subdirectory(compressor)

find_program(CLANG_FORMAT "clang-format")

if (CLANG_FORMAT)
    file(GLOB_RECURSE ALL_SOURCE_FILES
        "*.cpp" "*.hpp" "*.c" "*.h"
    )

    add_custom_target(
        format
        COMMAND ${CLANG_FORMAT}
        -i
        -style=file
        ${ALL_SOURCE_FILES}
        COMMENT "Formatting all source files with clang-format..."
    )
else()
    message(WARNING "clang-format not found. The 'format' target will not be available.")
endif()

find_program(CLANG_TIDY "clang-tidy")

if (CLANG_TIDY)
    set(CMAKE_CXX_CLANG_TIDY
        ${CLANG_TIDY}
        -config-file=${CMAKE_SOURCE_DIR}/.clang-tidy
        -extra-arg=-Wno-unknown-warning-option
    )
else()
    message(WARNING "clang-tidy not found. Static analysis will not be performed.")
endif()


if(${BUILD_TESTS})
    enable_testing()
endif()