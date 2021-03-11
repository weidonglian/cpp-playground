#include <algorithm>
#include <iostream>
#include <optional>
#include <vector>

#include "base.hpp"

using namespace std;

optional<int> array_minimum_bribes(vector<int> q) {
  const auto v_max = (int)q.size();
  int cnt = 0;
  for (int v = v_max; v > 0; --v) {
    for (int i = 0; i < 3; ++i) {
      // v should be in the position v-1
      const int should_pos = v - 1;
      if (q[should_pos - i] == v) {
        // move to right i th.
        for (int j = 0; j < i; ++j) {
          std::swap(q[should_pos - i + j], q[should_pos - i + j + 1]);
        }
        break;
      } else if (i == 2) {
        return nullopt;
      } else {
        ++cnt;
      }
    }
  }
  return cnt;
}

TEST_CASE("array_minimum_bribes", "[array]") {
  auto r1 = array_minimum_bribes({2, 1, 5, 3, 4});
  CHECK(r1.has_value());
  CHECK(3 == r1.value());

  auto r2 = array_minimum_bribes({2, 5, 1, 3, 4});
  CHECK_FALSE(r2.has_value());
}