#include <iostream>
#include <vector>
#include <limits>
#include <unordered_map>
#include "cpptest.hpp"

using namespace std;

vector<int> rot_left(const vector<int>& a, int d) {
    vector<int> results;
    results.reserve(a.size());
    for (int i = d; i < a.size(); ++i) {
        results.push_back(a[i]);
    }

    for (int j = 0; j < d; ++j) {
        results.push_back(a[j]);
    }
    return results;
}

void rot_left_inplace(vector<int>& arr, int d) {
    if (arr.empty()) return;
    int cnt = 0;
    while (cnt++ < d) {
        int temp = arr.front();
        for (int i = 1; i < arr.size(); ++i) {
            arr[i-1] = arr[i];
        }
        arr.back() = temp;
    }
}

TEST(ArraySuite, rotate_left) {
    EXPECT_EQ(rot_left({41, 73, 89, 7, 10, 1, 59, 58, 84, 77, 77, 97, 58, 1, 86, 58, 26, 10, 86, 51}, 10),
              vector<int>({77, 97, 58, 1, 86, 58, 26, 10, 86, 51, 41, 73, 89, 7, 10, 1, 59, 58, 84, 77}));
    vector<int> arr;
    rot_left_inplace((arr = {41, 73, 89, 7, 10, 1, 59, 58, 84, 77, 77, 97, 58, 1, 86, 58, 26, 10, 86, 51}), 10);
    EXPECT_EQ(arr, vector<int>({77, 97, 58, 1, 86, 58, 26, 10, 86, 51, 41, 73, 89, 7, 10, 1, 59, 58, 84, 77}));
}

bool is_match_rotated(const vector<int>& arr1, const vector<int>& arr2) {
    if (arr1.size() != arr2.size())
        return false;
    if (arr1.empty())
        return true;
    auto is_match = [&arr1, &arr2](int i_start, int j_start) {
        for (int i = 0; i < arr1.size(); i++) {
            // move j to next
            if (arr1[(i+i_start)%arr1.size()] != arr2[(i+j_start)%arr2.size()])
                return false;
        }
        return true;
    };
    // TODO: if there is duplication, it is better to find the less frequent one
    const int i_start = 0;
    int j_start = 0;
    while (j_start < arr2.size()) {
        auto it = find(next(arr2.begin(), j_start), arr2.end(), arr1[i_start]);
        if (it == arr2.end())
            return false;
        j_start = distance(arr2.begin(), it);
        if (is_match(i_start, j_start))
            return true;
        j_start++;
    }
    return true;
}

TEST(ArraySuite, is_rotated) {
    EXPECT_FALSE(is_match_rotated({1, 2, 3, 4, 5, 6, 7}, {4, 5, 6, 7, 8, 1, 2, 3}));
    EXPECT_TRUE(is_match_rotated({1, 2, 3, 4, 5, 6, 7}, {4, 5, 6, 7, 1, 2, 3}));
    EXPECT_FALSE(is_match_rotated({1, 2, 3, 4, 5, 6, 7}, {4, 5, 6, 9, 1, 2, 3}));
    // with duplication
    EXPECT_TRUE(is_match_rotated({2, 2, 3, 2, 5, 6, 7, 1}, {2, 5, 6, 7, 1, 2, 2, 3}));
}

vector<vector<int>> rotate(const vector<vector<int>>& arr) {
    if (arr.empty()) return {};
    const int n = arr.size();
    if (arr[0].size() != n)
        return {};
    vector<vector<int>> mat(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            mat[j][n - i - 1] = arr[i][j];
        }
    }
    return mat;
}

void rotate_inplace(vector<vector<int>>& arr) {
    if (arr.empty() || arr[0].size() != arr.size())
        return;
    const int n = (int)arr.size();
    // sub-block 1/4 part of the matrix.
    for (int i = 0; i < n/2; i++) {
        for (int j = 0; j < (n+1)/2; j++) {

        }
    }

}

TEST(ArraySuite, 2d_array_rotate) {
    // NOTE: The following input values will be used for testing your solution.
    vector<vector<int>> a1 = {{1, 2, 3},
                              {4, 5, 6},
                              {7, 8, 9}};
    EXPECT_EQ(rotate(a1), vector<vector<int>>({{7, 4, 1}, {8, 5, 2}, {9, 6, 3}}));
    rotate_inplace(a1);
    EXPECT_EQ(a1, vector<vector<int>>({{7, 4, 1}, {8, 5, 2}, {9, 6, 3}}));

    vector<vector<int>> a2 = {{1, 2, 3, 4},
                              {5, 6, 7, 8},
                              {9, 10, 11, 12},
                              {13, 14, 15, 16}};
    EXPECT_EQ(rotate(a2), vector<vector<int>>({{13, 9, 5, 1}, {14, 10, 6, 2}, {15, 11, 7, 3}, {16, 12, 8, 4}}));
    rotate_inplace(a2);
    EXPECT_EQ(a2, vector<vector<int>>({{13, 9, 5, 1}, {14, 10, 6, 2}, {15, 11, 7, 3}, {16, 12, 8, 4}}));
}