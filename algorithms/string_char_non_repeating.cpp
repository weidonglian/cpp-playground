#include "cpptest.hpp"
#include <algorithm>
#include <string>
#include <unordered_map>

using namespace std;

struct count_info {
    int cnt;
    int pos;
};

char find_non_repeating(const std::string &str) {
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
    for (const auto &item : counts) {
        const auto &info = item.second;
        if (info.cnt == 1 && info.pos < pos) {
            ret = item.first;
            pos = info.pos;
        }
    }
    return ret;
}

TEST_CASE("char_non_repeating", "[string]") {
    CHECK(find_non_repeating("abcab") == 'c');
    CHECK(find_non_repeating("abab") == '\0');
    CHECK(find_non_repeating("aabbbc") == 'c');
    CHECK(find_non_repeating("aabbdbc") == 'd');
}