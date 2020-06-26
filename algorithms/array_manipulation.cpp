#include <array>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "cpptest.hpp"

using namespace std;

long array_manipulation(int n, const vector<array<int, 3>> &queries) {
    vector<int> deltas(n);
    for (const auto &query : queries) {
        const auto left = query[0] - 1;
        const auto right = query[1] - 1;
        const auto val = query[2];
        deltas[left] += val;
        if (right + 1 < n)
            deltas[right + 1] -= val;
    }

    long max = 0;
    long current = 0;
    for (auto d : deltas) {
        current += d;
        if (current > max) {
            max = current;
        }
    }
    return max;
}

std::string test_array_manipulation(const std::string &input) {
    istringstream iss(input);
    int n = 0, m = 0;
    iss >> n >> m;
    vector<array<int, 3>> queries(m);
    for (auto &query : queries) {
        iss >> query[0] >> query[1] >> query[2];
    }
    const auto result = array_manipulation(n, queries);
    return to_string(result);
}

TEST_CASE('array_manipulation', '[array]') {
    const array<test_input_output, 3> cases = {
        test_input_output{
            R"(5 3
1 2 100
2 5 100
3 4 100)",
            R"(200)"},

        test_input_output{
            R"(10 3
1 5 3
4 8 7
6 9 1)",
            R"(10)"},

        test_input_output{
            R"(10 4
2 6 8
3 5 7
1 8 1
5 9 15)",
            R"(31)"},
    };

    for (const auto &e : cases) {
        CHECK(test_array_manipulation(e.input) == e.output);
    }
}
