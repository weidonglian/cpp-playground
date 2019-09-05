#include <string>
#include <functional>
#include "cpptest.hpp"

using namespace std;
using match_fn = std::function<bool(int, char)>;

bool is_frequency_match_impl(std::string str, match_fn fn) {
    if (str.empty())return true;

    sort(str.begin(), str.end());

    const int total = (int)str.size();
    int cnt = 0;
    char last = '\0';
    for (int start = 0; start < total; start++) {
        if (start == 0) {
            last = str[0];
        }

        if (str[start] == last) {
            cnt++;
        } else {
            if (!fn(cnt, last))
                return false;
            cnt = 1;
            last = str[start];
        }

        if (start == total - 1) { // last one
            if (!fn(cnt, last))
                return false;
        }
    }
    return true;
}

/// aabbcc is valid, aabbccc is not valid
/// str may not be sorted.
bool is_frequency_match(std::string str) {
    int last_cnt = -1;
    return is_frequency_match_impl(std::move(str), [&last_cnt](int nb, char c) {
        if (last_cnt == -1)
            last_cnt = nb;
        return last_cnt == nb;
    });
}

/// the same as above condition, check if it can become valid when removing one char
bool is_frequency_match_ext(std::string str) {
    // add more logic  to determine 322 223 332 patterns to be valid or not.
    map<int, int> cnt_freq;
    return is_frequency_match_impl(std::move(str), [&cnt_freq](int nb, char c) {
        cnt_freq[nb]++;
        if (cnt_freq.size() >= 3)
            return false;
        else if (cnt_freq.size() <= 1) {
            return true;
        } else { // cnt_freq.sizie() == 2
            return cnt_freq.rbegin()->second == 1;
        }
    });
}

TEST(StringSuite, char_frequency) {
    EXPECT_TRUE(is_frequency_match("aabbcc"));
    EXPECT_FALSE(is_frequency_match("aabbccc"));
    EXPECT_FALSE(is_frequency_match("aaabbbcc"));
    EXPECT_FALSE(is_frequency_match("aaabbcc"));

    EXPECT_TRUE(is_frequency_match_ext("aabbcc"));
    EXPECT_TRUE(is_frequency_match_ext("aabbccc"));
    EXPECT_FALSE(is_frequency_match_ext("aaabbbcc"));
    EXPECT_TRUE(is_frequency_match_ext("aaabbcc"));
}