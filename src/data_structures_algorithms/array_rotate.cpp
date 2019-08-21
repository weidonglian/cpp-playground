#include <iostream>
#include <vector>
#include "cpptest.hpp"

using namespace std;

vector<int> rot_left(const vector<int>& a, int d) {
    vector<int> results;
    results.reserve(a.size());
    for (int i = d; i < a.size(); ++i) {
        results.push_back(a[i]);
    }

    for (int j = 0; j < d; ++j) {
        results.push_back(a[j]);
    }
    return results;
}

TEST(ArraySuite, array_rotate) {
    EXPECT_EQ(rot_left({41, 73, 89, 7, 10, 1, 59, 58, 84, 77, 77, 97, 58, 1, 86, 58, 26, 10, 86, 51}, 10),
              vector<int>({77, 97, 58, 1, 86, 58, 26, 10, 86, 51, 41, 73, 89, 7, 10, 1, 59, 58, 84, 77}));
}