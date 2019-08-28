project(data-structures-algorithms)

# Use gtest, gtest style play
include(${CMAKE_SOURCE_DIR}/third_party/gtest/gtest.cmake)
set(SRC_GTEST_CASES_LIST ${GTEST_SRC} ${GTEST_HDR}
    array_minimum_swaps.cpp
    array_manipulation.cpp
    array_rotate.cpp
    array_hour_glass_sum.cpp
    array_minimum_bribes.cpp
    reverse_words_sentence.cpp
    container_set_key.cpp
    find_missing_numbers.cpp)

# Finalize to create a cpp-gtest
add_executable(cpptest ${SRC_GTEST_CASES_LIST})
target_link_libraries(cpptest Threads::Threads)
target_include_directories(cpptest PRIVATE ${GTEST_INC} ${CMAKE_SOURCE_DIR}/include)
add_test(NAME test-cpptest COMMAND cpptest)
