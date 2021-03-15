#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <vector>

#include "base.hpp"

// arr is sorted and rotated. The catch is that we should make use of the
// property that in the sorted but rotated array, if a[i] <= a[m], then
// [i, m] is sorted and not rotated. We should check cases that the target
// value lies in the range like [i, m] and we should search from [i, j]; otherwise,
// we should search from the other half.
bool find_number(const std::vector<int>& a, int target_value) {
  int l = 0;
  int r = static_cast<int>(a.size()) - 1;
  while (l <= r) {
    const int m = l + (r - l) / 2;
    if (a[m] == target_value) {
      return true;
    } else {
      if (a[l] <= a[m] && target_value >= a[l] && target_value <= a[m]) {
        r = m - 1;
      } else if (a[m] <= a[r] && target_value >= a[m] && target_value <= a[r]) {
        l = m + 1;
      } else if (a[l] > a[m]) {
        r = m - 1;
      } else {
        l = m + 1;
      }
    }
  }
  return false;
}

std::vector<int> gen_random_sequence(size_t sz) {
  std::vector<int> data;
  data.resize(sz);
  for (auto& v : data) {
    v = std::rand();
  }
  return data;
}

/**
 * @brief A given array is sorted and then rotated. We need to search through this rotated array
 * to find out if it contains a given target number.
 *
 */
TEST_CASE("bindary_search_rotated_array", "[array]") {
  REQUIRE(find_number({778, 1842, 3035, 8723, 9741, 12316, 12859, 20037, 22190, 25547, 27529, 27644, 32662, 32757, 288},
                      27529) == true);
  int k_test_count = 1000;
  while (k_test_count-- > 0) {
    auto arr = gen_random_sequence(std::abs(std::rand()) % 100 + 2);
    std::sort(arr.begin(), arr.end());
    const int val_outside = arr.back() + 100;
    size_t shift = std::abs(std::rand()) % arr.size();
    std::rotate(arr.begin(), arr.begin() + shift, arr.end());
    int target = arr[std::abs(std::rand()) % arr.size()];
    std::string info = "arr:";
    INFO("target:" + std::to_string(target));
    for (const auto v : arr) {
      info += std::to_string(v) + ", ";
    }
    INFO(info);
    REQUIRE(find_number(arr, target) == true);
    REQUIRE(find_number(arr, val_outside) == false);
  }
}