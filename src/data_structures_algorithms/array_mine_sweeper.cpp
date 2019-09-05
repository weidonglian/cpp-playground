#include <vector>
#include <algorithm>
#include "cpptest.hpp"

using namespace std;

TEST(ArraySuite, mine_sweeper_assign_numbers) {
// NOTE: The following input values will be used for testing your solution.
// mine_sweeper([[0, 2], [2, 0]], 3, 3) should return:
// [[0, 1, -1],
//  [1, 2, 1],
//  [-1, 1, 0]]

// mine_sweeper([[0, 0], [0, 1], [1, 2]], 3, 4) should return:
// [[-1, -1, 2, 1],
//  [2, 3, -1, 1],
//  [0, 1, 1, 1]]

// mine_sweeper([[1, 1], [1, 2], [2, 2], [4, 3]], 5, 5) should return:
// [[1, 2, 2, 1, 0],
//  [1, -1, -1, 2, 0],
//  [1, 3, -1, 2, 0],
//  [0, 1, 2, 2, 1],
//  [0, 0, 1, -1, 1]]
}

TEST(ArraySuite, mine_sweeper_where_to_expand) {
// NOTE: The following input values will be used for testing your solution.
// mine_sweeper([[0, 2], [2, 0]], 3, 3) should return:
// [[0, 1, -1],
//  [1, 2, 1],
//  [-1, 1, 0]]

// mine_sweeper([[0, 0], [0, 1], [1, 2]], 3, 4) should return:
// [[-1, -1, 2, 1],
//  [2, 3, -1, 1],
//  [0, 1, 1, 1]]

// mine_sweeper([[1, 1], [1, 2], [2, 2], [4, 3]], 5, 5) should return:
// [[1, 2, 2, 1, 0],
//  [1, -1, -1, 2, 0],
//  [1, 3, -1, 2, 0],
//  [0, 1, 2, 2, 1],
//  [0, 0, 1, -1, 1]]
}