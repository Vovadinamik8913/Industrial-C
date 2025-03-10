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

if(${BUILD_TESTS})
    enable_testing()
    add_subdirectory(tests)
endif()

install(TARGETS libcompressor
    EXPORT LibcompressorTargets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)