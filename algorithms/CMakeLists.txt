add_executable(test-algorithms
    array/find_common_elements.cpp
    array/mine_sweeper.cpp
    array/sum_pair.cpp
    array/find_sum_pair.cpp
    array/minimum_swaps.cpp
    array/find_max_diff.cpp
    array/manipulation.cpp
    array/rotate.cpp
    array/hour_glass_sum.cpp
    array/minimum_bribes.cpp
    array/find_missing_numbers.cpp
    string/reverse_letters.cpp
    string/char_frequency.cpp
    string/char_non_repeating.cpp
    string/char_is_one_away.cpp
    string/find_repeat_times.cpp
    tree/find_nearest_neighbour.cpp
    tree/ordered_map.cpp
    tree/visit_tree.cpp
    hash_table/separate_chainning.cpp
    set/set_key.cpp
    base.cpp
    base.hpp
    random.hpp
)

target_link_libraries(test-algorithms Threads::Threads catch2 simple_svg)
target_include_directories(test-algorithms PRIVATE "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>")
add_test(NAME test-algorithms COMMAND test-algorithms)
