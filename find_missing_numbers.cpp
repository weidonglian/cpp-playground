#include <iostream>
#include <string>
#include <vector>
#include <initializer_list>
#include <algorithm>
#include "cpptest.hpp"

ADD_TEST_SUITE(FindMissingNumbers);

//#define EXPECT_TRUE(e) if (!(e)) std::cout << "Failure: '" << #e << "'  == false" << std::endl

std::vector<int> find_missing_numbers(const std::vector<int>& sorted_numbers, int x, int y) {
    if (x == y) {
        return {};
    }
    auto it_x = std::find(std::begin(sorted_numbers), std::end(sorted_numbers), x);
    if (it_x == std::end(sorted_numbers)) {
        return {};
    }

    auto it_y = std::find(std::begin(sorted_numbers), std::end(sorted_numbers), y);
    if (it_y == std::end(sorted_numbers)) {
        return {};        
    }
    
    while (std::next(it_x) != std::end(sorted_numbers) && *std::next(it_x) == x)
        ++it_x;

    std::vector<int> results;
    auto it = std::next(it_x);
    for (int i = x + 1; i < y; ++i) {
        if (i == *it) {
            ++it;
            while (i == *it)
                ++it;

        } else {
            results.push_back(i);
        }
    }
    
    for (int i = 0; i < results.size(); ++i) {
        if (i == 0)
            std::cout << "Result:[";
        else
            std::cout << ", ";
        std::cout << results[i];
        if (i == results.size() -1)
            std::cout << "]" << std::endl;
    }
    return results;
}

TEST(FindMissingNumbers, common) {
    EXPECT_TRUE(find_missing_numbers({1, 3, 7, 9, 17, 23}, 3, 9) == std::vector<int>({4, 5, 6, 8}));
    EXPECT_TRUE(find_missing_numbers({1, 3, 3, 7, 9, 9, 17, 23}, 3, 9) == std::vector<int>({4, 5, 6, 8}));
    EXPECT_TRUE(find_missing_numbers({1, 3, 3, 7, 7, 9, 9, 17, 20}, 1, 20) == std::vector<int>({2, 4, 5, 6, 8, 10, 11, 12, 13, 14, 15, 16, 18, 19}));
}