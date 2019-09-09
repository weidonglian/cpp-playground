#include <vector>
#include <string>
#include <iostream>
#include <unordered_map>
#include "cpptest.hpp"

using namespace std;

int find_repeat_times(string sa, string sb) {
    unordered_map<char, int> cnts_sb;
    for (auto c : sb) {
        cnts_sb[c]++;
    }
    unordered_map<char, int> cnts_sa;
    for (auto c : sa) {
        cnts_sa[c]++;
    }
    int min_repeat_times = 1;
    for (const auto& e : cnts_sb) {
        auto it = cnts_sa.find(e.first);
        if (it == cnts_sa.end()) {
            return -1;
        }
        int times_required = e.second / it->second;
        if (times_required * it->second < e.second) {
            times_required += 1;
        }
        if (times_required > min_repeat_times) {
            min_repeat_times = times_required;
        }
    }
    if (sa.size() * min_repeat_times <= sb.size()) {
        min_repeat_times += 1;
    }
    return min_repeat_times;
}

TEST(StringSuite, find_repeat_times) {
    EXPECT_EQ(find_repeat_times("abcd", "cdabcdab"), 3);
    EXPECT_EQ(find_repeat_times("aafbbbcd", "cdeabcdab"), -1);
    EXPECT_EQ(find_repeat_times("aabbbcdddeeef", "abcdeff"), 2);
    EXPECT_EQ(find_repeat_times("abf", "abf"), 2);
    EXPECT_EQ(find_repeat_times("abff", "abf"), 1);
    EXPECT_EQ(find_repeat_times("abfff", "abff"), 1);
    EXPECT_EQ(find_repeat_times("abf", "abff"), 2);
    EXPECT_EQ(find_repeat_times("abff", "abfff"), 2);
    EXPECT_EQ(find_repeat_times("aabbbcdddeeeff", "abcdefff"), 2);
}