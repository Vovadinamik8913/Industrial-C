add_executable(regex
    src/regex.cpp
)

target_include_directories(regex
    PRIVATE
        ${CMAKE_SOURCE_DIR}/libregex/include
)

target_link_libraries(regex
    PRIVATE
        libregex
)

install(TARGETS regex
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

install(DIRECTORY ${CMAKE_SOURCE_DIR}/libregex/include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    FILES_MATCHING PATTERN "*.h*"
)