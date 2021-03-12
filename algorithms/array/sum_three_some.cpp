#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <tuple>
#include <unordered_set>
#include <vector>

#include "base.hpp"

/// arr has to be sorted first as a requirement.
bool has_pair_sum(const std::vector<int>& arr, int l, int target_sum) {
  // arr has been sorted already
  int r = arr.size() - 1;
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

// this implementation need to copy the whole arr and then sort them first.
bool has_three_some_sum(std::vector<int> arr, int target_sum) {
  std::sort(arr.begin(), arr.end());
  int total = static_cast<int>(arr.size());
  for (int i = 0; i < total - 2; ++i) {
    if (has_pair_sum(arr, i + 1, target_sum - arr[i])) {
      return true;
    }
  }
  return false;
}

// this implementation is space optimal, but a brutal force with N^3 complexity.
bool has_three_some_sum_brutal(const std::vector<int>& arr, int target_sum) {
  for (int i = 0; i < arr.size(); ++i) {
    for (int j = i + 1; j < arr.size(); ++j) {
      for (int k = j + 1; k < arr.size(); ++k) {
        if (arr[i] + arr[j] + arr[k] == target_sum) {
          return true;
        }
      }
    }
  }
  return false;
}

// this implementation is fast and no need to sort and copy the original array.
bool has_three_some_sum_hashset(const std::vector<int>& arr, int target_sum) {
  if (arr.size() < 3) {
    return false;
  }

  std::unordered_set<int> complements;
  for (size_t i = 0; i < arr.size() - 2; ++i) {
    complements.clear();
    const int pair_sum_target = target_sum - arr[i];
    for (size_t j = i + 1; j < arr.size(); ++j) {
      if (complements.count(pair_sum_target - arr[j])) {
        return true;
      }
      complements.insert(arr[j]);
    }
  }

  return false;
}

std::vector<int> generate_random_sequence(int sz) {
  std::vector<int> arr;
  arr.resize(sz);
  for (auto& v : arr) {
    v = std::rand();
  }
  return arr;
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
  REQUIRE(has_three_some_sum_brutal({1, 8, 9, 20, -1, 3, 7, 5, 3, 7, 1}, 7) == true);
  REQUIRE(has_three_some_sum_brutal({1, 8, 9, 20, -1, 3, 7, 5, 3, 7, 1}, 100) == false);
  REQUIRE(has_three_some_sum({1, 8, 9, 20, -1, 3, 7, 5, 3, 7, 1}, 7) == true);
  REQUIRE(has_three_some_sum({1, 8, 9, 20, -1, 3, 7, 5, 3, 7, 1}, 100) == false);
  REQUIRE(has_three_some_sum_hashset({1, 8, 9, 20, -1, 3, 7, 5, 3, 7, 1}, 7) == true);
  REQUIRE(has_three_some_sum_hashset({1, 8, 9, 20, -1, 3, 7, 5, 3, 7, 1}, 100) == false);
  int cnt = 100;
  while (cnt-- > 0) {
    auto arr = generate_random_sequence(std::rand() % 100);
    int target_sum = rand();
    auto ret = has_three_some_sum_brutal(arr, target_sum);
    REQUIRE(ret == has_three_some_sum(arr, target_sum));
    REQUIRE(ret == has_three_some_sum_hashset(arr, target_sum));
  }
}