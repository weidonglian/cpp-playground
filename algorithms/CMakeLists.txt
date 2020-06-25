# Use gtest, gtest style play
include(${CMAKE_SOURCE_DIR}/third_party/gtest/gtest.cmake)
set(SRC_GTEST_CASES_LIST ${GTEST_SRC} ${GTEST_HDR}
    array_find_common_elements.cpp
    array_mine_sweeper.cpp
    array_sum_pair.cpp
    array_find_sum_pair.cpp
    array_minimum_swaps.cpp
    array_find_max_diff.cpp
    array_manipulation.cpp
    array_rotate.cpp
    array_hour_glass_sum.cpp
    array_minimum_bribes.cpp
    array_find_missing_numbers.cpp
    string_reverse_letters.cpp
    string_char_frequency.cpp
    string_char_non_repeating.cpp
    string_char_is_one_away.cpp
    string_find_repeat_times.cpp
    tree_find_nearest_neighbour.cpp
    tree_ordered_map.cpp
    hash_table_separate_chainning.cpp
    container_set_key.cpp
)

# Finalize to create a cpp-gtest
add_executable(cpptest ${SRC_GTEST_CASES_LIST})
target_link_libraries(cpptest Threads::Threads)
target_include_directories(cpptest PRIVATE ${GTEST_INC} ${CMAKE_SOURCE_DIR}/include)
add_test(NAME test-cpptest COMMAND cpptest)
