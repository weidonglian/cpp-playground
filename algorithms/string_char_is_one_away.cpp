#include "test.hpp"
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

bool is_one_away(std::string s1, std::string s2) {
    const int len1 = (int)s1.size();
    const int len2 = (int)s2.size();
    if (abs(len1 - len2) > 1)
        return false;
    else if (len1 == len2) {
        int cnt_diff = 0;
        for (int i = 0; i < len1; i++) {
            if (s1[i] != s2[i] && ++cnt_diff > 1) {
                return false;
            }
        }
    } else { // len1 and len2 distance is 1
        int i = 0, j = 0;
        int cnt_diff = 0;
        while (i < len1 && j < len2) {
            if (s1[i] != s2[j]) {
                if (len1 > len2)
                    i++;
                else
                    j++;
                if (++cnt_diff > 1)
                    return false;
            } else {
                i++;
                j++;
            }
        }
    }
    return true;
}

TEST_CASE("is_one_away", "[string]") {
    CHECK(is_one_away("abcde", "abcd"));      // should return true
    CHECK(is_one_away("abde", "abcde"));      // should return true
    CHECK(is_one_away("a", "a"));             // should return true
    CHECK(is_one_away("abcdef", "abqdef"));   // should return true
    CHECK(is_one_away("abcdef", "abccef"));   // should return true
    CHECK(is_one_away("abcdef", "abcde"));    // should return true
    CHECK_FALSE(is_one_away("aaa", "abc"));   // should return false
    CHECK_FALSE(is_one_away("abcde", "abc")); // should return false
    CHECK_FALSE(is_one_away("abc", "abcde")); // should return false
    CHECK_FALSE(is_one_away("abc", "bcc"));   // should return false
}