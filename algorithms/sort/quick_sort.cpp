#include <algorithm>
#include <array>
#include <cstdlib>
#include <vector>

#include "base.hpp"

namespace {

int pivot(std::vector<int>& a, int lo, int hi) {
  int m = lo + (hi - lo) / 2;
  if (a[m] >= a[lo] && a[m] <= a[hi]) {
    return m;
  } else if (a[lo] >= a[m] && a[lo] <= a[hi]) {
    return lo;
  } else {
    return hi;
  }
}

void quick_sort(std::vector<int>& a, int lo, int hi) {
  if (lo >= hi) {
    return;
  }
  // choose a pivot
  std::swap(a[pivot(a, lo, hi)], a[lo]);
  // lo now keeps the pivot and start partioning
  int l = lo;
  int r = l + 1;
  while (l < r && r <= hi) {
    if (a[r] < a[l]) {
      std::swap(a[l], a[r]);
      l = l + 1;
      if (l != r) {
        std::swap(a[l], a[r]);
      }
    }
    ++r;
  }

  // i_pivot now is on the boundary of the partioning
  quick_sort(a, lo, l - 1);
  quick_sort(a, l + 1, hi);
}

std::vector<int> gen_random_sequence(size_t sz) {
  std::vector<int> data;
  data.resize(sz);
  for (auto& v : data) {
    v = std::rand();
  }
  return data;
}

} // namespace

TEST_CASE("quick_sort", "[sort]") {
  int k_test_count = 1000;
  while (k_test_count-- > 0) {
    auto data = gen_random_sequence(std::rand() % 1000);
    auto expected = data;
    std::sort(std::begin(expected), std::end(expected));
    quick_sort(data, 0, static_cast<int>(data.size()) - 1);
    REQUIRE(data == expected);
  }
}

TEST_CASE("quick_sort_prop_testing", "[sort]") {
  rc::prop([](const std::vector<int>& l0) {
    auto l1 = l0;
    quick_sort(l1, 0, static_cast<int>(l1.size()) - 1);
    auto l2 = l0;
    RC_ASSERT(l1 == l2);
  });
}