#include <algorithm>
#include <functional>
#include <vector>

#include "algorithms.hpp"

using namespace std;

/// This will loop every possible combinations. Complexity: N*N
int find_max_diff_brutal_force(const vector<int>& arr) {
  int max_diff = 0;
  for (int i = 0; i < arr.size(); i++) {
    for (int j = i + 1; j < arr.size(); j++) {
      auto diff = arr[j] - arr[i];
      if (diff > max_diff) {
        max_diff = diff;
      }
    }
  }
  return max_diff;
}

/// Keep track of the min value from left and max_diff. Complexity: N.
int find_max_diff_optimal(const vector<int>& arr) {
  if (arr.empty())
    return 0;
  const int n = (int)arr.size();
  int max_diff = 0;
  int min_val = arr[0];
  for (int i = 1; i < n; i++) {
    int diff = arr[i] - min_val;
    if (diff > max_diff) {
      max_diff = diff;
    }
    if (arr[i] < min_val) {
      min_val = arr[i];
    }
  }
  return max_diff;
}

/// keep track of the adjacent dist and then find max sum of positive contributions.
int find_max_diff_relative_dist(const vector<int>& arr) {
  const int n = (int)arr.size();
  vector<int> diffs(n - 1);
  for (int i = 0; i < diffs.size(); i++) {
    diffs[i] = arr[i + 1] - arr[i];
  }
  int max_diff = 0;
  for (int i = 1; i < diffs.size(); i++) {
    if (diffs[i - 1] > 0) {
      diffs[i] += diffs[i - 1];
    }
    if (diffs[i] > max_diff) {
      max_diff = diffs[i];
    }
  }
  return max_diff;
}

/// keep track of the adjacent dist and then find max sum of dist. space
/// optimal.
int find_max_diff_relative_dist_optimal(const vector<int>& arr) {
  if (arr.size() < 2)
    return 0;
  int diff = 0;
  int cur_sum = 0;
  int max_sum = 0;
  for (int i = 1; i < arr.size(); i++) {
    diff = arr[i] - arr[i - 1];
    if (cur_sum > 0) {
      cur_sum += diff;
    } else {
      cur_sum = diff;
    }
    if (cur_sum > max_sum) {
      max_sum = cur_sum;
    }
  }
  return max_sum;
}

/**
 * @brief Find the max difference between two elements such that the larger element appears after the smaller one.
 *
 * Note: we can not sort the array and find the difference between min and max. The order matters.
 */
TEST_CASE("find_max_diff", "[array]") {
  int idx = 0;
  for (const auto& fn : {find_max_diff_brutal_force, find_max_diff_optimal, find_max_diff_relative_dist,
                         find_max_diff_relative_dist_optimal}) {
    INFO("with idx" << idx);
    CHECK(fn({1, 3, 4, 8, 2, 4, 7}) == 7);
    CHECK(fn({1, 2, 3, 4, 5, 6, 8}) == 7);
    CHECK(fn({3, 2, 1}) == 0);
    CHECK(fn({4, 2, 8, 2, 7, 1, 7}) == 6);
    CHECK(fn({80, 2, 6, 3, 100}) == 98);
    idx++;
  }
}