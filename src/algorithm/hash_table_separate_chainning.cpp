#include <utility>
#include <vector>
#include <string>
#include <iostream>
#include <functional>
#include <unordered_map>

#include "cpptest.hpp"

using namespace std;

namespace {

template <typename T>
size_t hash_value(T &&t) {
    return std::hash<T>{}(std::forward<T>(t));
}

template <typename T>
void hash_combine(size_t &seed, T&& v) {
    seed ^= hash_value(std::forward<T>(v)) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

template <typename K, typename V, class Hash = hash<K>,
          class Pred = equal_to<K>>
class hash_table {
  public:
    using key_type = K;
    using value_type = V;
    using key_equal = Pred;
    using key_hash = Hash;

    hash_table() {
    }

    ~hash_table() {

    }

    void insert(key_type key, value_type val) {

    }

    void erase(const key_type& key) {

    }

    value_type* find(const key_type& key) {
        return nullptr;
    }

  private:
};

} // namespace

TEST(HashTableSuite, separate_chainning_common) {
    hash_table<int, int> ht;
    constexpr int k_size = 1000;
    const vector<int> key = generate_random_number(k_size);
    const vector<int> val = generate_random_number(k_size);
    std::unordered_map<int, int> expected_ht;
    for (int i = 0; i < k_size; i++) {
        ht.insert(key[i], val[i]);
        expected_ht[key[i]] = val[i];
    }

    for (int i = 0; i < k_size; i++) {
        auto r = ht.find(key[i]);
        ASSERT_TRUE(r != nullptr);
        EXPECT_EQ(*r, expected_ht[key[i]]);
    }

    for (int i = 0; i < k_size; i++) {
        ht.erase(key[i]);
        auto r = ht.find(key[i]);
        EXPECT_TRUE(r == nullptr);
    }
}