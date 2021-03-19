#include <algorithm>
#include <cstdlib>
#include <execution>
#include <future>
#include <iterator>
#include <thread>

#include "base.hpp"

struct kv_pair {
  int key;
  int val;
  bool operator==(const kv_pair& right) const { return this->key == right.key && this->val == right.val; }
};

// input kv_pair must have been sorted in key order
std::vector<kv_pair> merge_kv_pairs(std::vector<kv_pair> pairs) {
  if (pairs.empty()) {
    return {};
  }
  std::vector<kv_pair> result;
  int key = pairs[0].key;
  int val = pairs[0].val;
  for (int i = 1; i < pairs.size(); ++i) {
    if (key == pairs[i].key) {
      val += pairs[i].val;
    } else {
      result.push_back(kv_pair{key, val});
      key = pairs[i].key;
      val = pairs[i].val;
    }
  }
  result.push_back(kv_pair{key, val});
  return result;
}

std::vector<kv_pair> merge_kv_pairs_async(std::vector<kv_pair> pairs) {
  if (pairs.size() <= 10000) {
    return merge_kv_pairs(std::move(pairs));
  }
  // sort the pairs in the pair's `key` order.
  std::sort(pairs.begin(), pairs.end(), [](const kv_pair& p1, const kv_pair& p2) { return p1.key < p2.key; });
  const int k_processor_count = std::thread::hardware_concurrency();
  std::vector<std::future<std::vector<kv_pair>>> futures;
  const int count_per_group = pairs.size() / k_processor_count;
  futures.reserve(k_processor_count);
  int left = 0;
  int cnt = count_per_group;
  while (left + cnt <= pairs.size()) {
    while (left + cnt < pairs.size() && pairs[left + cnt - 1].key == pairs[left + cnt].key) {
      ++cnt;
    }
    futures.push_back(std::async(std::launch::async, merge_kv_pairs,
                                 std::vector<kv_pair>{pairs.begin() + left, pairs.begin() + left + cnt}));
    if (left + cnt >= pairs.size()) {
      break;
    }
    left = left + cnt;
    cnt = k_processor_count;
    if (left + cnt > pairs.size()) {
      cnt = pairs.size() - left;
    }
  }
  std::vector<std::vector<kv_pair>> results;
  results.reserve(futures.size());
  size_t total_count = 0;
  for (auto& f : futures) {
    results.push_back(f.get());
    total_count += results.back().size();
  }
  std::vector<kv_pair> all;
  all.reserve(total_count);
  for (auto& r : results) {
    std::copy(r.begin(), r.end(), std::back_inserter(all));
  }
  return all;
}

std::vector<kv_pair> merge_kv_pairs_parallel(std::vector<kv_pair> pairs) {
  if (pairs.size() <= 10000) {
    return merge_kv_pairs(std::move(pairs));
  }
  // sort the pairs in the pair's `key` order.
  std::sort(std::execution::par, pairs.begin(), pairs.end(),
            [](const kv_pair& p1, const kv_pair& p2) { return p1.key < p2.key; });
  const int k_processor_count = std::thread::hardware_concurrency();
  std::vector<std::thread> runners;
  std::vector<std::vector<kv_pair>> results;
  const int count_per_group = pairs.size() / k_processor_count;
  runners.reserve(k_processor_count);
  results.reserve(k_processor_count);
  int left = 0;
  int cnt = count_per_group;
  while (left + cnt <= pairs.size()) {
    while (left + cnt < pairs.size() && pairs[left + cnt - 1].key == pairs[left + cnt].key) {
      ++cnt;
    }
    results.push_back({});
    runners.push_back(std::thread{[&pairs, left, cnt, result = &results.back()] {
      *result = merge_kv_pairs(std::vector<kv_pair>{pairs.begin() + left, pairs.begin() + left + cnt});
    }});
    if (left + cnt >= pairs.size()) {
      break;
    }
    left = left + cnt;
    cnt = k_processor_count;
    if (left + cnt > pairs.size()) {
      cnt = pairs.size() - left;
    }
  }
  for (auto& f : runners) {
    f.join();
  }
  size_t total_count = 0;
  for (auto& v : results) {
    total_count += v.size();
  }
  std::vector<kv_pair> all;
  all.reserve(total_count);
  for (auto& r : results) {
    std::copy(r.begin(), r.end(), std::back_inserter(all));
  }
  return all;
}

static const size_t total_count = 10000000;

TEST_CASE("pair_sum_in_parallel", "[array]") {
  std::vector<kv_pair> pairs;
  pairs.resize(total_count);
  for (auto& v : pairs) {
    std::srand(time(nullptr));
    v.key = std::rand();
    v.val = std::rand();
  }
  merge_kv_pairs_parallel(std::move(pairs));
}

TEST_CASE("pair_sum_huge", "[array]") {
  std::vector<kv_pair> pairs;
  pairs.resize(total_count);
  for (auto& v : pairs) {
    std::srand(time(nullptr));
    v.key = std::rand();
    v.val = std::rand();
  }
  merge_kv_pairs(std::move(pairs));
}

TEST_CASE("pair_sum", "[array]") {
  REQUIRE(merge_kv_pairs(std::vector<kv_pair>{kv_pair{0, 1}, kv_pair{0, 2}, kv_pair{2, 4}, kv_pair{3, 8}, kv_pair{3, 7},
                                              kv_pair{10, 3}}) ==
          std::vector<kv_pair>{kv_pair{0, 3}, kv_pair{2, 4}, kv_pair{3, 15}, kv_pair{10, 3}});
}