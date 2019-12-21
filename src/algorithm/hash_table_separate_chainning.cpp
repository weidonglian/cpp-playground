#include <cstddef>
#include <memory>
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
    static constexpr int k_def_bucket_size = 100;
    using key_type = K;
    using value_type = V;
    using key_equal = Pred;
    using key_hash = Hash;

    hash_table()
        : bucket_size_(k_def_bucket_size),
          buckets_(make_unique<hash_node *[]>(bucket_size_)), hasher_(),
          equaler_() {
    }

    ~hash_table() {
        for (int i = 0; i < bucket_size_; ++i) {
            hash_node *entry = buckets_[i];
            while (entry) {
                hash_node *next = entry->next;
                delete entry;
                entry = next;
            }
            buckets_[i] = nullptr;
        }
    }

    void insert(key_type key, value_type val) {
        // first get
        int idx = bucket_index(key);
        //while ()
    }

    void erase(const key_type& key) {

    }

    value_type* find(const key_type& key) {
        return nullptr;
    }

  private:
    struct hash_node {
        key_type key;
        value_type val;
        hash_node* next;
    };

    int bucket_index(const key_type& key) const {
        return hasher_(key) % bucket_size_;
    }

  private:
    int bucket_size_;
    unique_ptr<hash_node*[]> buckets_;
    key_hash hasher_;
    key_equal equaler_;
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