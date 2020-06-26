#include "algorithms.hpp"
#include <algorithm>
#include <initializer_list>
#include <iostream>
#include <string>
#include <vector>

//#define CHECK(e) if (!(e)) std::cout << "Failure: '" << #e << "'  ==
// false" << std::endl
void print_numbers(const std::vector<int> &numbers) {
    for (int i = 0; i < numbers.size(); ++i) {
        if (i == 0)
            std::cout << "Result:[";
        else
            std::cout << ", ";
        std::cout << numbers[i];
        if (i == numbers.size() - 1)
            std::cout << "]" << std::endl;
    }
}

// search the first element
// include left and right
// case 1: arr = [1, 2, 3, 8, 9], l = r = 2, l = 0, r = 3, l = 0 r = 4
// case 2: arr = [1, 3, 8, 9], l = r = 2, l = 1, r = 4
int binary_search(const std::vector<int> &arr, int l, int r, int val) {
    if (l <= r) {
        int mid = l + (r - l) / 2;
        if (arr[mid] == val) {
            // mid is what we want, but we should move back to skip duplication
            while (mid - 1 >= l && arr[mid - 1] == val)
                --mid;
            return mid;
        } else if (arr[mid] > val) {
            return binary_search(arr, l, mid - 1, val);
        } else {
            return binary_search(arr, mid + 1, r, val);
        }
    }
    return -1;
}

// search the first element
int binary_search_iterative(const std::vector<int> &arr, int l, int r,
                            int val) {
    while (l <= r) {
        int mid = l + (r - l) / 2;
        if (arr[mid] == val) {
            while (mid - 1 >= l && arr[mid - 1] == val)
                mid--;
            return mid;
        } else if (arr[mid] > val) {
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    return -1;
}

std::vector<int> find_missing_numbers(const std::vector<int> &arr, int x,
                                      int y) {
    if (x >= y)
        return {};

    const int total = static_cast<int>(arr.size());
    int b = binary_search(arr, 0, total, x);
    if (b == -1)
        return {};
    int e = binary_search(arr, b, total, y);
    if (e == -1)
        return {};

    auto move_next = [&](int idx) {
        while (++idx < total && arr[idx] == arr[idx - 1])
            ;
        return idx;
    };

    std::vector<int> results;
    b = move_next(b);
    for (int v = x + 1; v < y && b < total; ++v) {
        if (v == arr[b]) {
            b = move_next(b);
        } else {
            results.push_back(v);
        }
    }
    return results;
}

std::vector<int> find_missing_numbers_2(const std::vector<int> &sorted_numbers,
                                        int x, int y) {
    if (x == y) {
        return {};
    }
    auto it_x =
        std::find(std::begin(sorted_numbers), std::end(sorted_numbers), x);
    if (it_x == std::end(sorted_numbers)) {
        return {};
    }

    auto it_y =
        std::find(std::begin(sorted_numbers), std::end(sorted_numbers), y);
    if (it_y == std::end(sorted_numbers)) {
        return {};
    }

    while (std::next(it_x) != std::end(sorted_numbers) && *std::next(it_x) == x)
        ++it_x;

    std::vector<int> numbers;
    auto it = std::next(it_x);
    for (int i = x + 1; i < y; ++i) {
        if (i == *it) {
            ++it;
            while (i == *it)
                ++it;

        } else {
            numbers.push_back(i);
        }
    }

    print_numbers(sorted_numbers);
    return numbers;
}

TEST_CASE("find_missing_numbers", "[array]") {
    CHECK(binary_search_iterative({1, 3, 7, 9, 17, 23}, 1, 4, 9) == 3);
    CHECK(binary_search_iterative({1, 3, 3, 7, 9, 9, 17, 23}, 0, 6, 3) == 1);
    CHECK(binary_search_iterative({1, 3, 3, 7, 7, 9, 9, 17, 20}, 1, 7, 9) == 5);

    CHECK(binary_search({1, 3, 7, 9, 17, 23}, 1, 4, 9) == 3);
    CHECK(binary_search({1, 3, 3, 7, 9, 9, 17, 23}, 0, 6, 3) == 1);
    CHECK(binary_search({1, 3, 3, 7, 7, 9, 9, 17, 20}, 1, 7, 9) == 5);

    CHECK(find_missing_numbers({1, 3, 7, 9, 17, 23}, 3, 9) ==
          std::vector<int>({4, 5, 6, 8}));
    CHECK(find_missing_numbers({1, 3, 3, 7, 9, 9, 17, 23}, 3, 9) ==
          std::vector<int>({4, 5, 6, 8}));
    CHECK(
        find_missing_numbers({1, 3, 3, 7, 7, 9, 9, 17, 20}, 1, 20) ==
        std::vector<int>({2, 4, 5, 6, 8, 10, 11, 12, 13, 14, 15, 16, 18, 19}));
}