find_package(GTest REQUIRED)

add_executable(libcompressor_tests
    libcompressortest.cpp
)

target_link_libraries(libcompressor_tests
    PRIVATE
        ${LIBRARYABC}
        GTest::GTest
        GTest::Main
)

set(TEST_REPORT_DIR "${CMAKE_BINARY_DIR}/test_results")
file(MAKE_DIRECTORY ${TEST_REPORT_DIR})

add_test(
    NAME libcompressor_tests
    COMMAND libcompressor_tests
    --gtest_output=xml:${TEST_REPORT_DIR}/test_results.xml
)