#include "test.hpp"
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

bool is_match_rotated(const vector<int> &arr1, const vector<int> &arr2) {
    if (arr1.size() != arr2.size())
        return false;
    if (arr1.empty())
        return true;
    for (int i = 0, j = 0; i < arr1.size(); i++, j = (j + 1) % arr2.size()) {
        if (i == 0) {
            auto it = find(arr2.begin(), arr2.end(), arr1[0]);
            if (it == arr2.end())
                return false;
            j = distance(arr2.begin(), it);
        } else {
            // move j to next
            if (arr1[i] != arr2[j])
                return false;
        }
    }
    return true;
}

TEST_CASE("is_rotated", "[array]") {
    CHECK_FALSE(
        is_match_rotated({1, 2, 3, 4, 5, 6, 7}, {4, 5, 6, 7, 8, 1, 2, 3}));
    CHECK(is_match_rotated({1, 2, 3, 4, 5, 6, 7}, {4, 5, 6, 7, 1, 2, 3}));
    CHECK_FALSE(is_match_rotated({1, 2, 3, 4, 5, 6, 7}, {4, 5, 6, 9, 1, 2, 3}));
    // with duplication
    CHECK(is_match_rotated({2, 2, 3, 2, 5, 6, 7, 1}, {2, 5, 6, 7, 1, 2, 2, 3}));
}