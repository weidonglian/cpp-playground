#include <vector>
#include <functional>
#include <algorithm>
#include "cpptest.hpp"

using namespace std;

/// This will loop every possible combinations. Complexity: N*N
int find_max_diff_brutal_force(const vector<int>& arr) {
    int max_diff = 0;
    for (int i = 0; i < arr.size(); i++) {
        for (int j = i+1; j < arr.size(); j++) {
            auto diff = arr[j] - arr[i];
            if (diff > max_diff) {
                max_diff = diff;
            }
        }
    }
    return max_diff;
}

/// Keep track of the min value from left and max_diff. Complexity: N.
int find_max_diff_optimal(const vector<int>& arr) {
    if (arr.empty()) return 0;
    const int n = (int)arr.size();
    int max_diff = 0;
    int min_val = arr[0];
    for (int i = 1; i < n; i++) {
        int diff = arr[i] - min_val;
        if (diff > max_diff) {
            max_diff = diff;
        }
        if (arr[i] < min_val) {
            min_val = arr[i];
        }
    }
    return max_diff;
}

/// keep track of the adjacent dist and then find max sum of dist.
int find_max_diff_relative_dist(const vector<int>& arr) {
    const int n = (int)arr.size();
    vector<int> diffs(n-1);
    for (int i = 0; i < diffs.size(); i++) {
        diffs[i] = arr[i+1] - arr[i];
    }
    int max_diff = 0;
    for(auto diff : diffs) {
        // todo
    }
}

TEST(ArraySuite, find_max_diff) {
    using calculator = function<int(const vector<int>&)>;
    int idx = 0;
    for (const auto& fn : { find_max_diff_brutal_force, find_max_diff_optimal }) {
        EXPECT_EQ(fn({1, 3, 4, 8, 2, 4, 7}), 7) << "with idx " << idx;
        EXPECT_EQ(fn({1, 2, 3, 4, 5, 6, 8}), 7) << "with idx " << idx;
        EXPECT_EQ(fn({3, 2, 1}), 0) << "with idx " << idx;
        EXPECT_EQ(fn({4, 2, 8, 2, 7, 1, 7}), 6) << "with idx " << idx;
        idx++;
    }
}