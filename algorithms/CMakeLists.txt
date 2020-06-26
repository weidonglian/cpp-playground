add_executable(algorithms
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
    catch2_main.cpp
    cpptest.hpp
)

target_link_libraries(algorithms Threads::Threads catch2 simple_svg)
add_test(NAME test-algorithms COMMAND algorithms)
