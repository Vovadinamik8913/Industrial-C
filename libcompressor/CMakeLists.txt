add_library(libcompressor STATIC
    src/libcompressor.cpp
    include/libcompressor/libcompressor.hpp
)

target_include_directories(libcompressor
    PUBLIC 
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${BZip2_INCLUDE_DIRS}
        ${ZLIB_INCLUDE_DIRS}
)

target_link_libraries(libcompressor
    PRIVATE
        ZLIB::ZLIB
        BZip2::BZip2
)

target_compile_options(libcompressor PRIVATE 
    -Wall -Wextra -Wpedantic -Werror
)

set_target_properties(libcompressor PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
    POSITION_INDEPENDENT_CODE ON
)