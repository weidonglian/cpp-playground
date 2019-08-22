#include <vector>
#include <fstream>
#include "cpptest.hpp"

using namespace std;

int array_minimum_swaps(vector<int> arr) // Not optimal performant
{
    auto is_matched = [&arr](int i) { return arr[i] == i + 1; };
    auto is_one_matched_after_swap = [&arr](int i, int j) { return arr[i] == j + 1 || arr[j] == i + 1; };
    auto is_both_matched_after_swap = [&arr](int i, int j) { return arr[i] == j + 1 && arr[j] == i + 1; };
    int cnt = 0;
    int b = 0, e = (int)arr.size() - 1; // b and e are indices of searching range.
    int loop = 0;
    while (b < e)
    {
        loop++;
        cout << "while loop i=" << loop << " with [" << b << ", " << e << "]" << endl;
        while (is_matched(b) && ++b <= e) {}
        while (is_matched(e) && --e >= b) {}
        if (b >= e)
        {
            break;
        }

        // start moving both b and e, since they are not matched yet
        int candiate = -1;
        for (int i = b + 1; i <= e; ++i)
        {
            if (is_matched(i)) continue;
            if (is_both_matched_after_swap(b, i)) // perfect matched
            { // perfect swap
                std::swap(arr[b], arr[i]);
                ++cnt;
                candiate = -1;
                break;
            }
            if (candiate == -1 && is_one_matched_after_swap(b, i)) {
                candiate = i;
            }
        }
        if (candiate != -1) {
            std::swap(arr[b], arr[candiate]);
            ++cnt;
        }
    }
    return cnt;
}

TEST(ArraySuite, array_minimum_swaps) {
    EXPECT_EQ(3, array_minimum_swaps({1, 3, 5, 2, 4, 6, 7}));
    EXPECT_EQ(3, array_minimum_swaps({2, 3, 4, 1, 5}));
    EXPECT_EQ(3, array_minimum_swaps({4, 3, 1, 2}));
    EXPECT_EQ(0, array_minimum_swaps({1, 2, 3, 4}));
}

TEST(ArraySuite, array_minimum_swaps_large) {
    ifstream ifs("input12.txt");
    int arr_size = 0;
    ifs >> arr_size;
    vector<int> arr(arr_size);
    for (size_t i = 0; i < arr_size; ++i)
    {
        ifs >> arr[i];
    }
    EXPECT_EQ(99987, array_minimum_swaps(arr));
}

