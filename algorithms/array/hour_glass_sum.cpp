#include <iostream>
#include <string>
#include <vector>

#include "base.hpp"

using namespace std;

// Find the maximum element
template <class IT>
IT find_max_element(IT first, IT second) {
  if (first == second)
    return second;
  IT largest = first;
  while (++first != second) {
    if (*first > *largest) {
      largest = first;
    }
  }
  return largest;
}

// Complete the hourglassSum function below.
int hour_glass_sum(vector<vector<int>> arr) {
  vector<int> sums;
  // scan all sums
  for (int i = 0; i < arr.size() - 2; ++i)
    for (int j = 0; j < arr.size() - 2; ++j) {
      int sum = 0;
      for (int a = 0; a < 3; ++a)
        for (int b = 0; b < 3; ++b) {
          if (!(a == 1 && (b == 0 || b == 2)))
            sum += arr[i + a][j + b];
        }
      sums.push_back(sum);
    }

  // extract max element
  auto it = find_max_element(begin(sums), end(sums));
  if (it != end(sums))
    return *it;
  return 0;
}

TEST_CASE("array_hour_glass_sum", "[array]") {
  CHECK(19 == hour_glass_sum({{1, 1, 1, 0, 0, 0},
                              {0, 1, 0, 0, 0, 0},
                              {1, 1, 1, 0, 0, 0},
                              {0, 0, 2, 4, 4, 0},
                              {0, 0, 0, 2, 0, 0},
                              {0, 0, 1, 2, 4, 0}}));
  CHECK(13 == hour_glass_sum({{{1, 1, 1, 0, 0, 0},
                               {0, 1, 0, 0, 0, 0},
                               {1, 1, 1, 0, 0, 0},
                               {0, 9, 2, -4, -4, 0},
                               {0, 0, 0, -2, 0, 0},
                               {0, 0, -1, -2, -4, 0}}}));
}