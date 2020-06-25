#include <vector>
#include <queue>
#include <algorithm>
#include "cpptest.hpp"

using namespace std;

struct position {
    int x;
    int y;
};

vector<vector<int>> generate_mine_sweeper_board(const vector<position>& bombs, int n, int m) {
    vector<vector<int>> board(n, vector<int>(m, 0));
    auto is_valid = [](int id, int n) {
        return id >= 0 && id < n;
    };

    for (const auto& bomb : bombs) {
        // loop all neighbours
        for (int i = -1; i <= 1; i++)
            for (int j = -1; j <= 1; j++) {
                if (i == 0 && j == 0) {
                    board[bomb.x][bomb.y] = -1;
                    continue;
                } else {
                    int idx = bomb.x + i, idy = bomb.y + j;
                    if (is_valid(idx, n) && is_valid(idy, m) && board[idx][idy] != -1)
                        board[idx][idy] += 1;
                }
            }
    }
    return board;
}

TEST(ArraySuite, mine_sweeper_assign_numbers) {
// NOTE: The following input values will be used for testing your solution.
// mine_sweeper([[0, 2], [2, 0]], 3, 3) should return:
// [[0, 1, -1],
//  [1, 2, 1],
//  [-1, 1, 0]]
EXPECT_EQ(generate_mine_sweeper_board({position{0, 2}, position{2, 0}}, 3, 3),
          vector<vector<int>>({{0, 1, -1}, {1, 2, 1}, {-1, 1, 0}}));

// mine_sweeper([[0, 0], [0, 1], [1, 2]], 3, 4) should return:
// [[-1, -1, 2, 1],
//  [2, 3, -1, 1],
//  [0, 1, 1, 1]]
EXPECT_EQ(generate_mine_sweeper_board({position{0, 0},
                                       position{0, 1},
                                       position{1, 2}},
                                      3, 4),
          vector<vector<int>>({{-1, -1, 2, 1}, {2, 3, -1, 1}, {0, 1, 1,1}}));

// mine_sweeper([[1, 1], [1, 2], [2, 2], [4, 3]], 5, 5) should return:
// [[1, 2, 2, 1, 0],
//  [1, -1, -1, 2, 0],
//  [1, 3, -1, 2, 0],
//  [0, 1, 2, 2, 1],
//  [0, 0, 1, -1, 1]]
EXPECT_EQ(generate_mine_sweeper_board({position{1, 1},
                                       position{1, 2},
                                       position{4, 3},
                                       position{2, 2}},
                                      5, 5),
          vector<vector<int>>({{1, 2, 2, 1, 0}, {1, -1, -1, 2, 0}, {1, 3, -1, 2, 0}, {0, 1, 2, 2, 1}, {0, 0, 1, -1, 1}}));
}

void mine_sweeper_click_to_expand(vector<vector<int>>& field, int click_x, int click_y) {
    if (field.empty()) return;
    auto is_valid = [](int idx, int size) {
        return idx >= 0 && idx < size;
    };

    auto mark_expanded = [&](int x, int y) {
        field[x][y] = -2;
    };

    const int n = (int)field.size();
    const int m = (int)field[0].size();
    if (!is_valid(click_x, n) || !is_valid(click_y, m) || field[click_x][click_y])
        return;
    vector<vector<int>> result(n, vector<int>(m, 0));
    queue<position> candidates;
    candidates.push({click_x, click_y});
    if (!field[click_x][click_y])
        field[click_x][click_y] = -2;
    while (!candidates.empty()) {
        position pos = candidates.front();
        candidates.pop();
        // check if pos valid
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                if (i == 0 && j == 0) continue;
                int idx = pos.x + i, idy = pos.y + j;
                if (is_valid(idx, n) && is_valid(idy, m) && !field[idx][idy]) {
                    candidates.push({idx, idy});
                    field[idx][idy] = -2;
                }
            }
        }
    }
}
TEST(ArraySuite, mine_sweeper_where_to_expand) {
    // NOTE: The following input values will be used for testing your solution.
    const vector<vector<int>> field1 = {{0, 0, 0, 0, 0},
                                        {0, 1, 1, 1, 0},
                                        {0, 1, -1, 1, 0}};
    auto field1_result1 = field1;
    mine_sweeper_click_to_expand(field1_result1, 2, 2);
    EXPECT_EQ(field1, field1_result1);

    auto field1_result2 = field1;
    mine_sweeper_click_to_expand(field1_result2, 1, 4);
    EXPECT_EQ(field1_result2, vector<vector<int>>({{-2, -2, -2, -2, -2},
      {-2, 1, 1, 1, -2},
      {-2, 1, -1, 1, -2}}));

    const vector<vector<int>> field2 = {{-1, 1, 0, 0}, {1, 1, 0, 0}, {0, 0, 1, 1}, {0, 0, 1, -1}};
    auto field2_result1 = field2;
    mine_sweeper_click_to_expand(field2_result1, 0, 1);
    EXPECT_EQ(field2_result1, vector<vector<int>>({
    {-1, 1, 0, 0},
    {1, 1, 0, 0},
    {0, 0, 1, 1},
    {0, 0, 1, -1}}));

    auto field2_result2 = field2;
    mine_sweeper_click_to_expand(field2_result2, 1, 3);
    EXPECT_EQ(field2_result2, vector<vector<int>>({
    {-1, 1, -2, -2},
    {1, 1, -2, -2},
    {-2, -2, 1, 1},
    {-2, -2, 1, -1}}));
}