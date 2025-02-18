add_executable(compressor
    src/compressor.cpp
)

target_include_directories(compressor
    PRIVATE
        ${CMAKE_SOURCE_DIR}/libcompressor/include
        ${fmt_INCLUDE_DIRS}
)

target_link_libraries(compressor
    PRIVATE
        libcompressor
        fmt::fmt
)

target_compile_options(compressor PRIVATE 
    -Wall -Wextra -Wpedantic -Werror
)

if(UNIX)
    target_link_libraries(compressor PRIVATE m)
endif()