#include "cpptest.hpp"
#include <fstream>
#include <vector>

using namespace std;

int array_minimum_swaps(vector<int> arr) {
    auto is_matched = [&arr](int i) { return arr[i] == i + 1; };
    int cnt = 0;
    int s = 0;
    while (s < arr.size()) {
        if (is_matched(s)) {
            ++s;
        } else {
            std::swap(arr[s], arr[arr[s] - 1]);
            ++cnt;
        }
    }
    return cnt;
}

TEST_CASE("array_minimum_swaps", "[array]") {
    CHECK(3 == array_minimum_swaps({1, 3, 5, 2, 4, 6, 7}));
    CHECK(3 == array_minimum_swaps({2, 3, 4, 1, 5}));
    CHECK(3 == array_minimum_swaps({4, 3, 1, 2}));
    CHECK(0 == array_minimum_swaps({1, 2, 3, 4}));
}

/* TEST_CASE("[array]', array_minimum_swaps_large) {
    ifstream ifs("input12.txt");
    int arr_size = 0;
    ifs >> arr_size;
    vector<int> arr(arr_size);
    for (size_t i = 0; i < arr_size; ++i)
    {
        ifs >> arr[i];
    }
    CHECK(99987, array_minimum_swaps(arr));
} */
