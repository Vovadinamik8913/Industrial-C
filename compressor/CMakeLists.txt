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

install(TARGETS compressor
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

install(DIRECTORY ${CMAKE_SOURCE_DIR}/libcompressor/include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    FILES_MATCHING PATTERN "*.h*"
)