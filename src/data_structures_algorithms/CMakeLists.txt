project(data-structures-algorithms)

# Use gtest, gtest style play
include(${CMAKE_SOURCE_DIR}/third_party/gtest/gtest.cmake)
set(SRC_GTEST_CASES_LIST
    reverse_letters.cpp
    container_set.cpp
    find_missing_numbers.cpp
    ${GTEST_SRC}
    ${GTEST_HDR})

# Finalize to create a cpp-gtest
add_executable(cpptest ${SRC_GTEST_CASES_LIST})
target_link_libraries(cpptest Threads::Threads)
target_include_directories(cpptest PRIVATE ${GTEST_INC} ${CMAKE_SOURCE_DIR}/include)
add_test(NAME test-cpptest COMMAND cpptest)
