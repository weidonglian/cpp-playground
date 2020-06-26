#include "cpptest.hpp"
#include <algorithm>
#include <unordered_set>
#include <vector>

using namespace std;

// arr has been sorted
bool has_sum_pair_sorted(const vector<int> &arr, int sum) {
    // scan from two pointers
    int l = 0;
    int r = static_cast<int>(arr.size() - 1);
    while (l < r) {
        const int s = arr[l] + arr[r];
        if (s == sum) {
            return true;
        } else if (s < sum) {
            ++l;
        } else { // s > sum
            --r;
        }
    }
    return false;
}

bool has_sum_pair(const vector<int> &arr, int sum) {
    unordered_set<int> complements;
    for (auto v : arr) {
        if (complements.count(v)) {
            return true;
        }
        complements.insert(sum - v);
    }
    return false;
}

TEST_CASE('array_sum_pair', '[array]') {
    CHECK(has_sum_pair_sorted({1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 19}, 12),
          true);
    CHECK(has_sum_pair_sorted({1, 2, 3, 9}, 8), false);
    CHECK(has_sum_pair_sorted({1, 2, 4, 4}, 8), true);

    CHECK(has_sum_pair({1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 19}, 12), true);
    CHECK(has_sum_pair({1, 2, 3, 9}, 8), false);
    CHECK(has_sum_pair({1, 2, 4, 4}, 8), true);

    CHECK(has_sum_pair({1, 4, 2, 11, 8, 8, 7, 2, 19, 6, 6, 12, 19}, 12), true);
    CHECK(has_sum_pair({9, 3, 2, 1}, 8), false);
    CHECK(has_sum_pair({1, 4, 4, 2}, 8), true);
}