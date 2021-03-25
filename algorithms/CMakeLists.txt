add_executable(test-algorithms
    array/find_common_elements.cpp
    array/mine_sweeper.cpp
    array/sum_pair.cpp
    array/sum_three_some.cpp
    array/find_sum_pair.cpp
    array/minimum_swaps.cpp
    array/find_max_diff.cpp
    array/manipulation.cpp
    array/rotate.cpp
    array/hour_glass_sum.cpp
    array/minimum_bribes.cpp
    array/find_missing_numbers.cpp
    array/binary_search_rotated_array.cpp
    array/pair_sum_in_parallel.cpp
    array/merge_pairs.cpp
    link_list/add_two_integers.cpp
    link_list/merge_two_sorted_link_list.cpp
    link_list/find_circular_loop.cpp
    string/reverse_letters.cpp
    string/char_frequency.cpp
    string/char_non_repeating.cpp
    string/char_is_one_away.cpp
    string/find_repeat_times.cpp
    sort/quick_sort.cpp
    sort/sort_two_direction.cpp
    tree/find_nearest_neighbour.cpp
    tree/ordered_map.cpp
    tree/visit_tree.cpp
    tree/tree_manipulate.cpp
    tree/directed_graph.cpp
    tree/flatten_bst_into_linked_list.cpp
    hash_table/separate_chainning.cpp
    set/set_key.cpp
    math/x_power_y.cpp
    base.cpp
    base.hpp
    random.hpp
)

if(OpenMP_CXX_FOUND)
    set(LINK_LIB_OPENMP OpenMP::OpenMP_CXX)
endif()

target_link_libraries(test-algorithms Threads::Threads catch2 simple_svg ${LINK_LIB_OPENMP})

target_include_directories(test-algorithms PRIVATE "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>")
add_test(NAME test-algorithms COMMAND test-algorithms)
