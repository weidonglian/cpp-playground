#include <array>
#include <iostream>
#include <limits>
#include <unordered_map>
#include <vector>

#include "base.hpp"

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
  if (arr.empty())
    return;
  int cnt = 0;
  while (cnt++ < d) {
    int temp = arr.front();
    for (int i = 1; i < arr.size(); ++i) {
      arr[i - 1] = arr[i];
    }
    arr.back() = temp;
  }
}

TEST_CASE("rotate_left", "[array]") {
  CHECK(rot_left({41, 73, 89, 7, 10, 1, 59, 58, 84, 77, 77, 97, 58, 1, 86, 58, 26, 10, 86, 51}, 10) ==
        vector<int>({77, 97, 58, 1, 86, 58, 26, 10, 86, 51, 41, 73, 89, 7, 10, 1, 59, 58, 84, 77}));
  vector<int> arr;
  rot_left_inplace((arr = {41, 73, 89, 7, 10, 1, 59, 58, 84, 77, 77, 97, 58, 1, 86, 58, 26, 10, 86, 51}), 10);
  CHECK(arr == vector<int>({77, 97, 58, 1, 86, 58, 26, 10, 86, 51, 41, 73, 89, 7, 10, 1, 59, 58, 84, 77}));
}

bool is_match_rotated(const vector<int>& arr1, const vector<int>& arr2) {
  if (arr1.size() != arr2.size())
    return false;
  if (arr1.empty())
    return true;
  auto is_match = [&arr1, &arr2](int i_start, int j_start) {
    for (int i = 0; i < arr1.size(); i++) {
      // move j to next
      if (arr1[(i + i_start) % arr1.size()] != arr2[(i + j_start) % arr2.size()])
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
    j_start = (int)distance(arr2.begin(), it);
    if (is_match(i_start, j_start))
      return true;
    j_start++;
  }
  return true;
}

TEST_CASE("is_rotated", "[array]") {
  CHECK_FALSE(is_match_rotated({1, 2, 3, 4, 5, 6, 7}, {4, 5, 6, 7, 8, 1, 2, 3}));
  CHECK(is_match_rotated({1, 2, 3, 4, 5, 6, 7}, {4, 5, 6, 7, 1, 2, 3}));
  CHECK_FALSE(is_match_rotated({1, 2, 3, 4, 5, 6, 7}, {4, 5, 6, 9, 1, 2, 3}));
  // with duplication
  CHECK(is_match_rotated({2, 2, 3, 2, 5, 6, 7, 1}, {2, 5, 6, 7, 1, 2, 2, 3}));
}

void print(const vector<vector<int>>& arr) {
  for (int i = 0; i < arr.size(); i++) {
    if (i == 0)
      cout << "arr={\n";
    for (int j = 0; j < arr[i].size(); j++) {
      if (j == 0) {
        cout << "[";
      }
      cout << arr[i][j];
      if (j == arr[i].size() - 1)
        cout << "]";
      else
        cout << ",";
    }
    if (i == arr.size() - 1)
      cout << "\n};\n";
    else
      cout << ",\n";
  }
}

vector<vector<int>> rotate(const vector<vector<int>>& arr) {
  if (arr.empty())
    return {};
  const int n = (int)arr.size();
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
  // cout << "before\n";
  // print(arr);
  if (arr.empty() || arr[0].size() != arr.size())
    return;
  const int n = (int)arr.size();
  auto rotate_advance = [n](int i, int j) { return make_pair(j, n - i - 1); };

  // sub-block 1/4 part of the matrix.
  array<int, 4> tmps{};
  for (int i = 0; i < n / 2; i++) {
    for (int j = 0; j < (n + 1) / 2; j++) {
      // i, j, rotate between four positions
      for (int itimes = 0, ia = i, ib = j; itimes < 4; itimes++) {
        tmps[itimes] = arr[ia][ib];
        tie(ia, ib) = rotate_advance(ia, ib);
      }
      for (int itimes = 0, ia = i, ib = j; itimes < 4; itimes++) {
        tie(ia, ib) = rotate_advance(ia, ib);
        arr[ia][ib] = tmps[itimes];
      }
    }
  }
  // cout << "after:\n";
  // print(arr);
}

TEST_CASE("2d_array_rotate", "[array]") {
  // NOTE: The following input values will be used for testing your solution.
  vector<vector<int>> a1 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  CHECK(rotate(a1) == vector<vector<int>>({{7, 4, 1}, {8, 5, 2}, {9, 6, 3}}));
  rotate_inplace(a1);
  CHECK(a1 == vector<vector<int>>({{7, 4, 1}, {8, 5, 2}, {9, 6, 3}}));

  vector<vector<int>> a2 = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
  CHECK(rotate(a2) == vector<vector<int>>({{13, 9, 5, 1}, {14, 10, 6, 2}, {15, 11, 7, 3}, {16, 12, 8, 4}}));
  rotate_inplace(a2);
  CHECK(a2 == vector<vector<int>>({{13, 9, 5, 1}, {14, 10, 6, 2}, {15, 11, 7, 3}, {16, 12, 8, 4}}));
}