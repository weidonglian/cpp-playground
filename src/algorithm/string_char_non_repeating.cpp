#include <string>
#include <algorithm>
#include <unordered_map>
#include "cpptest.hpp"

using namespace std;

struct count_info {
    int cnt;
    int pos;
};

char find_non_repeating(const std::string& str) {
    unordered_map<char, count_info> counts;
    for (int i = 0; i < str.size(); i++) {
        auto c = str[i];
        auto it = counts.find(c);
        if (it == counts.end()) {
            counts.emplace(c, count_info{1, i});
        } else {
            it->second.cnt++;
        }
    }

    char ret = '\0';
    int pos = (int)str.size() + 1;
    for (const auto& item : counts) {
        const auto& info = item.second;
        if (info.cnt == 1 && info.pos < pos) {
            ret = item.first;
            pos = info.pos;
        }
    }
    return ret;
}

TEST(StringSuite, char_non_repeating) {
EXPECT_EQ(find_non_repeating("abcab"), 'c');
EXPECT_EQ(find_non_repeating("abab"), '\0');
EXPECT_EQ(find_non_repeating("aabbbc"), 'c');
EXPECT_EQ(find_non_repeating("aabbdbc"), 'd');
}