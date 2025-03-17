cmake_minimum_required (VERSION 3.12)
project(regexp LANGUAGES CXX)

find_package(Doxygen REQUIRED)

set(CMAKE_C_COMPILER "/usr/bin/clang")
set(CMAKE_CXX_COMPILER "/usr/bin/clang++")
set(BUILD_TESTS ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS YES)

include(GNUInstallDirs)
doxygen_add_docs(docs
    ${CMAKE_SOURCE_DIR}/libregex/include
    ${CMAKE_SOURCE_DIR}/libregex/src
    ${CMAKE_SOURCE_DIR}/regex/src
    COMMENT "Generating API documentation"
)

add_compile_options(-Wall -Wextra -Wpedantic -Werror)
set_property(GLOBAL PROPERTY CXX_STANDARD 20)
set_property(GLOBAL PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(GLOBAL PROPERTY CXX_EXTENSIONS OFF)
set_property(GLOBAL PROPERTY POSITION_INDEPENDENT_CODE ON)

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
endif()

find_program(CLANG_TIDY "clang-tidy")
if (CLANG_TIDY)
    set(CMAKE_CXX_CLANG_TIDY
        ${CLANG_TIDY}
        -config-file=${CMAKE_SOURCE_DIR}/.clang-tidy
        -extra-arg=-Wno-unknown-warning-option
    )
endif()

if(${BUILD_TESTS})
    enable_testing()
endif()

add_subdirectory(libregex)
add_subdirectory(regex)