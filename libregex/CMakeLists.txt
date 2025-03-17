file(GLOB LIBREGEX_SOURCES src/*.cpp)
file(GLOB LIBREGEX_HEADERS include/libregex/*.hpp)

add_library(libregex STATIC ${LIBREGEX_SOURCES})

target_include_directories(libregex PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

if(${BUILD_TESTS})
    enable_testing()
    add_subdirectory(tests)
endif()

install(TARGETS libregex
    EXPORT LibergexTargets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)