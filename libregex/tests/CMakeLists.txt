find_package(GTest REQUIRED)
file(GLOB TEST_SOURCES *.cpp)

add_executable(libregex_tests ${TEST_SOURCES})

target_link_libraries(libregex_tests
    PRIVATE
        libregex
        GTest::GTest
        GTest::Main
)

target_include_directories(libregex_tests PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
)

set(TEST_REPORT_DIR "${CMAKE_BINARY_DIR}/test_results")
file(MAKE_DIRECTORY ${TEST_REPORT_DIR})

add_test(
    NAME libregex_tests
    COMMAND libregex_tests
    --gtest_output=xml:${TEST_REPORT_DIR}/test_results.xml
)