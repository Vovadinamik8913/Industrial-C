file(GLOB LIBTRANSFORMER_SOURCES src/*.cpp)
file(GLOB LIBTRANSFORMER_HEADERS include/libtransformer/*.hpp)

add_library(libtransformer STATIC ${LIBTRANSFORMER_SOURCES})

target_include_directories(libtransformer PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

install(TARGETS libtransformer
    EXPORT LibtransformerTargets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)