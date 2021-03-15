#include <deque>
#include <unordered_map>

#include "base.hpp"

namespace {
class lru_cache {
public:
  lru_cache() : cache(), accessed() {}
  int get(int key) {}
  int put(int key, int val) {
    auto cit = cache.find(key);
    if (cit != cache.end()) {
      cit->second = key;
      accessed.erase(std::find(accessed.begin(), accessed.end(), key));
      accessed.push_back(cit->first);
    } else {
    }
  }

private:
  std::unordered_map<int, int> cache;
  std::deque<int> accessed;
};
} // namespace