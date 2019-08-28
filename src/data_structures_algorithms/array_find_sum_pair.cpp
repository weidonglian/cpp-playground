#include <vector>
#include <algorithm>
#include "cpptest.hpp"

using namespace std;

pair<int, int> find_sum_pair(vector<int> arr1, vector<int> arr2, int sum) {
    if (arr1.empty() || arr2.empty()) return { -1, -1 };
    // they both are not empty
    sort(arr1.begin(), arr1.end());
    sort(arr2.begin(), arr2.end());
    // search from the right, top corner of the block seemingly more efficient
    const int len1 = arr1.size();
    const int len2 = arr2.size();
    int i = len1 - 1;
    int j = 0;
    while (i >= 0 && j < len2) {
        int s = arr1[i] + arr2[j];
        if (s == sum) {
            return { i, j };
        } else if (s < sum) {
            j++;
        } else { // s > sum
            i--;
        }
    }
    return { -1, -1 };
}

pair<int, int> find_sum_pair_brut(const vector<int>& arr1, const vector<int>& arr2, int sum) {
    for (int i = 0; i < arr1.size(); ++i)
        for (int j = 0; j < arr2.size(); ++j) {
            if (arr1[i] + arr2[j] == sum) {
                return {i, j};
            }
        }
    return {-1, -1};
}

TEST(ArraySuite, find_sum_pair) {
    const vector<int> arr1 = {1, 8, 9, 20, -1, 3, 7, 5, 3, 7, 1};
    const vector<int> arr2 = {5, 4, -1, 2, -1, 2, -5, 7, 0, 8, 9, 3, 4, 2};
    auto pr = find_sum_pair_brut(arr1, arr2, 7);
    ASSERT_TRUE(pr.first != -1 && pr.second != -1);
    EXPECT_EQ(arr1[pr.first] + arr2[pr.second], 7);
    pr = find_sum_pair(arr1, arr2, 7);
    ASSERT_TRUE(pr.first != -1 && pr.second != -1);
    EXPECT_EQ(arr1[pr.first] + arr2[pr.second], 7);
}





