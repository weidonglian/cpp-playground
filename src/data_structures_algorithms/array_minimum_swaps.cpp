#include <vector>
#include <fstream>
#include "cpptest.hpp"

using namespace std;

int array_minimum_swaps(vector<int> arr)
{
    auto is_matched = [&arr](int i) { return arr[i] == i + 1; };
    int cnt = 0;
    int s = 0;
    while (s < arr.size()) {
        if (is_matched(s)) {
            ++s;
        } else {
            std::swap(arr[s], arr[arr[s]-1]);
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

/* TEST(ArraySuite, array_minimum_swaps_large) {
    ifstream ifs("input12.txt");
    int arr_size = 0;
    ifs >> arr_size;
    vector<int> arr(arr_size);
    for (size_t i = 0; i < arr_size; ++i)
    {
        ifs >> arr[i];
    }
    EXPECT_EQ(99987, array_minimum_swaps(arr));
} */

