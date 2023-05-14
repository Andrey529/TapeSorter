project(Google_tests)
add_subdirectory(googletest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# 'Google_Tests_run' is the target name
# 'Tests.cpp' are source files with tests
add_executable(Google_Tests_run UnitTests.cpp)
target_link_libraries(Google_Tests_run gtest gtest_main)