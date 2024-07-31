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
  int r = static_cast<int>(arr.size()) - 1;
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

// this implementation is optimal with complexity only O(LogN)
// Note: when binary searching, we should shrink the range and exclude the middle element
// to avoid the infinite/dead loop. Always m + 1 or m -1. Each loop should move the l, r
// otherwise, it might get stuck.
// Note this won't, since it is three-some.
bool has_three_some_sum_binary_search(std::vector<int> arr, int target_sum) {
  std::sort(std::begin(arr), std::end(arr));
  int l = 1;
  int r = static_cast<int>(arr.size()) - 2;
  while (l <= r) {
    // search right side first
    const int m = l + (r - l) / 2;
    const int sum = arr[m - 1] + arr[m] + arr[m + 1];
    if (sum == target_sum) {
      return true;
    } else if (sum < target_sum) {
      l = m + 1;
    } else {
      r = m - 1;
    }
  }
  return false;
}

// this implementation is space optimal, but a brutal force with N^3 complexity.
bool has_three_some_sum_brutal(const std::vector<int>& arr, int target_sum) {
  for (size_t i = 0; i < arr.size(); ++i) {
    for (size_t j = i + 1; j < arr.size(); ++j) {
      for (size_t k = j + 1; k < arr.size(); ++k) {
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

/**  @brief Check if there exists sum pair in a sorted array. */
TEST_CASE("match_sum_pair", "[array]") {
  REQUIRE(has_pair_sum({1, 8, 9, 20, -1, 3, 7, 5, 3, 7, 1}, 0, 0) == true);
  REQUIRE(has_pair_sum({1, 8, 9, 20, -1, 3, 7, 5, 3, 7, 1}, 0, 10) == true);
  REQUIRE(has_pair_sum({1, 8, 9, 20, -1, 3, 7, 5, 3, 7, 1}, 0, 100) == false);
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
  // REQUIRE(has_three_some_sum_binary_search({1, 8, 9, 20, -1, 3, 7, 5, 3, 7, 1}, 7) == true);
  // REQUIRE(has_three_some_sum_binary_search({1, 8, 9, 20, -1, 3, 7, 5, 3, 7, 1}, 100) == false);
  // REQUIRE(has_three_some_sum_binary_search({1, 8, 9, 20, -1, 6, 3, 7, 5, 3, 7, 1}, 7) == true);
  // REQUIRE(has_three_some_sum_binary_search({1, 8, 9, 20, -1, 6, 3, 7, 5, 3, 7, 1}, 100) == false);
}

TEST_CASE("match_sum_three_some_one_case", "[array]") {
  std::vector<int> tarr{
    14343, 30523, 1587,  29314, 9503,  7448,  25200, 13458, 6618,  20580, 19796, 14798, 15281, 19589, 20798, 28009,
    27157, 20472, 23622, 18538, 12292, 6038,  24179, 18190, 29657, 7958,  6191,  19815, 22888, 19156, 11511, 16202,
    2634,  24272, 20055, 20328, 22646, 26362, 4886,  18875, 28433, 29869, 20142, 23844, 1416,  21881, 31998, 10322,
    18651, 10021, 5699,  3557,  28476, 27892, 24389, 5075,  10712, 2600,  2510,  21003, 26869, 17861, 14688, 13401,
    9789,  15255, 16423, 5002,  10585, 24182, 10285, 27088, 31426, 28617, 23757, 9832,  30932, 4169,  2154,  25721,
    17189, 19976, 31329, 2368,  28692, 21425, 10555, 3434,  16549, 7441,  9512,  30145, 18060};
  const int t_target_sum = 21718;
  REQUIRE(has_three_some_sum_brutal(tarr, t_target_sum));
  REQUIRE(has_three_some_sum(tarr, t_target_sum));
}

TEST_CASE("match_sum_three_some_random", "[array]") {
  int cnt = 100;
  while (cnt-- > 0) {
    auto arr = generate_random_sequence(std::rand() % 100);
    const int target_sum = rand();
    std::string info = "array:";
    for (auto v : arr) {
      info += std::to_string(v) + ", ";
    }
    INFO("target:" + std::to_string(target_sum));
    INFO(info);
    // auto ret = has_three_some_sum_brutal(arr, target_sum);
    // REQUIRE(ret == has_three_some_sum(arr, target_sum));
    // REQUIRE(ret == has_three_some_sum_hashset(arr, target_sum));
    // REQUIRE(ret == has_three_some_sum_binary_search(arr, target_sum));
  }
}