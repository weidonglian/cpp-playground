#include <algorithm>
#include <iostream>
#include <tuple>
#include <vector>

#include "base.hpp"

bool has_pair_sum(const std::vector<int>& arr, size_t l, int target_sum) {
  // arr has been sorted already
  size_t r = arr.size() - 1;
  while (l < r) {
    const int sum = arr[l] + arr[r];
    if (sum == target_sum) {
      return true;
    } else if (sum < target_sum) {
      ++l;
    } else {
      --r;
    }
  }
  return false;
}

bool has_three_some_sum(std::vector<int> arr, int target_sum) {
  std::sort(arr.begin(), arr.end());
  for (size_t i = 0; i < arr.size() - 2; ++i) {
    if (has_pair_sum(arr, i + 1, target_sum - arr[i])) {
      return true;
    }
  }
  return false;
}

/**
 * @brief Check if the array has a sum of three values matching the given value.
 *
 * Solution: It should be normally scaned with O(N^2).
 * First sort the array and scan from left to right.
 * For i, it turns out to be a sub problem of `pair sum matching problem` with
 * a sub array:(i+1..N) and the given matching `sum-arr[i]`.
 */
TEST_CASE("match_sum_three_some", "[array]") {
  REQUIRE(has_three_some_sum({1, 8, 9, 20, -1, 3, 7, 5, 3, 7, 1}, 7) == true);
  REQUIRE(has_three_some_sum({1, 8, 9, 20, -1, 3, 7, 5, 3, 7, 1}, 100) == false);
}