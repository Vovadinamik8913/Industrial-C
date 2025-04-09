add_executable(transformer
    src/transformer.cpp
)

target_include_directories(transformer
    PRIVATE
        ${CMAKE_SOURCE_DIR}/libtransformer/include
)

target_link_libraries(transformer
    PRIVATE
        libtransformer
)

install(TARGETS transformer
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

install(DIRECTORY ${CMAKE_SOURCE_DIR}/libtransformer/include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    FILES_MATCHING PATTERN "*.h*"
)