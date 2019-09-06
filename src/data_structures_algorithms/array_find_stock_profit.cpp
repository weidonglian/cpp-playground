#include <vector>
#include <functional>
#include <algorithm>
#include "cpptest.hpp"

using namespace std;

int calc_profit_brutal_force(const vector<int>& arr) {
    int profit = 0;
    for (int i = 0; i < arr.size(); i++) {
        for (int j = i+1; j < arr.size(); j++) {
            auto current = arr[j] - arr[i];
            if (current > profit) {
                profit = current;
            }
        }
    }
    return profit;
}

int calc_profit_optimal(const vector<int>& arr) {
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

TEST(ArraySuite, calculate_stock_profit) {
    using calculator = function<int(const vector<int>&)>;
    int idx = 0;
    for (const auto& calc_fn : { calc_profit_brutal_force, calc_profit_optimal }) {
        EXPECT_EQ(calc_fn({1, 3, 4, 8, 2, 4, 7}), 7) << "with idx " << idx;
        EXPECT_EQ(calc_fn({1, 2, 3, 4, 5, 6, 8}), 7) << "with idx " << idx;
        EXPECT_EQ(calc_fn({3, 2, 1}), 0) << "with idx " << idx;
        EXPECT_EQ(calc_fn({4, 2, 8, 2, 7, 1, 7}), 6) << "with idx " << idx;
        idx++;
    }
}