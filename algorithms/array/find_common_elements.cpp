#include <vector>

#include "algorithms.hpp"

using namespace std;

vector<int> find_common_elements(const vector<int>& arr1, const vector<int>& arr2) {
  vector<int> results;
  int i = 0;
  int j = 0;
  while (i < arr1.size() && j < arr2.size()) {
    if (arr1[i] == arr2[j]) {
      results.push_back(arr1[i]);
      i++;
      j++;
    } else if (arr1[i] > arr2[j]) {
      j++;
    } else {
      i++;
    }
  }
  return results;
}

/**
 * @brief Find the common elements between two integer sequences.
 *
 * 1. sort the two sequences first.
 * 2. initiate two indices and move the two them accordingly.
 */
TEST_CASE("find_common_elements", "[array]") {
  CHECK(find_common_elements({1, 3, 4, 6, 7, 9}, {1, 2, 4, 5, 9, 10}) == vector<int>({1, 4, 9}));
  CHECK(find_common_elements({1, 2, 9, 10, 11, 12}, {0, 1, 2, 3, 4, 5, 8, 9, 10, 12, 14, 15}) ==
        vector<int>({1, 2, 9, 10, 12}));
  CHECK(find_common_elements({0, 1, 2, 3, 4, 5}, {6, 7, 8, 9, 10, 11}).empty());
}