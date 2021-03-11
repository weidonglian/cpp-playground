#include <functional>
#include <map>
#include <string>
#include <unordered_map>

#include "base.hpp"

using namespace std;
using match_fn = function<bool(int, char)>;
enum class match_impl_policy { k_default, k_sorting, k_hashing };

bool is_frequency_match_impl_hashing(const string& str, match_fn fn) {
  if (str.empty())
    return true;

  unordered_map<char, int> counts;
  for (auto c : str)
    counts[c]++;

  for (const auto& e : counts) {
    if (!fn(e.second, e.first)) {
      return false;
    }
  }
  return true;
}

bool is_frequency_match_impl_sorting(string str, match_fn fn) {
  if (str.empty())
    return true;

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
bool is_frequency_match(string str, match_impl_policy policy = match_impl_policy::k_default) {
  int last_cnt = -1;
  auto fn = [&last_cnt](int nb, char c) {
    if (last_cnt == -1)
      last_cnt = nb;
    return last_cnt == nb;
  };

  if (policy == match_impl_policy::k_sorting) {
    return is_frequency_match_impl_sorting(move(str), move(fn));
  } else { // by default and hashing
    return is_frequency_match_impl_hashing(str, move(fn));
  }
}

/// the same as above condition, check if it can become valid when removing one
/// char
bool is_frequency_match_ext(string str, match_impl_policy policy = match_impl_policy::k_default) {
  // add more logic  to determine 322 223 332 patterns to be valid or not.
  map<int, int> cnt_freq;
  auto fn = [&cnt_freq](int nb, char c) {
    cnt_freq[nb]++;
    if (cnt_freq.size() >= 3)
      return false;
    else if (cnt_freq.size() <= 1) {
      return true;
    } else { // cnt_freq.sizie() == 2
      return cnt_freq.rbegin()->second == 1;
    }
  };

  if (policy == match_impl_policy::k_sorting) {
    return is_frequency_match_impl_sorting(move(str), move(fn));
  } else { // by default and hashing
    return is_frequency_match_impl_hashing(str, move(fn));
  }
}

TEST_CASE("char_frequency", "[string]") {
  CHECK(is_frequency_match("aabbcc"));
  CHECK_FALSE(is_frequency_match("aabbccc"));
  CHECK_FALSE(is_frequency_match("aaabbbcc"));
  CHECK_FALSE(is_frequency_match("aaabbcc"));

  CHECK(is_frequency_match_ext("aabbcc"));
  CHECK(is_frequency_match_ext("aabbccc"));
  CHECK_FALSE(is_frequency_match_ext("aaabbbcc"));
  CHECK(is_frequency_match_ext("aaabbcc"));

  CHECK(is_frequency_match("aabbcc", match_impl_policy::k_sorting));
  CHECK_FALSE(is_frequency_match("aabbccc", match_impl_policy::k_sorting));
  CHECK_FALSE(is_frequency_match("aaabbbcc", match_impl_policy::k_sorting));
  CHECK_FALSE(is_frequency_match("aaabbcc", match_impl_policy::k_sorting));

  CHECK(is_frequency_match_ext("aabbcc", match_impl_policy::k_sorting));
  CHECK(is_frequency_match_ext("aabbccc", match_impl_policy::k_sorting));
  CHECK_FALSE(is_frequency_match_ext("aaabbbcc", match_impl_policy::k_sorting));
  CHECK(is_frequency_match_ext("aaabbcc", match_impl_policy::k_sorting));
}