#include <cstddef>
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "test.hpp"

using namespace std;

namespace {

template <typename T>
size_t hash_value(T &&t) {
    return std::hash<T>{}(std::forward<T>(t));
}

template <typename T>
void hash_combine(size_t &seed, T &&v) {
    seed ^=
        hash_value(std::forward<T>(v)) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
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
          equal_pred_() {
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
        hash_node *entry = buckets_[idx];
        if (!entry) { // empty slot
            buckets_[idx] = hash_node_new(move(key), move(val));
            return;
        }

        while (entry) {
            if (equal_pred_(entry->key, key)) {
                entry->val = move(val);
                return;
            }
            if (!entry->next) {
                entry->next = hash_node_new(move(key), move(val));
                return;
            }
            entry = entry->next;
        }
    }

    void erase(const key_type &key) {
        int idx = bucket_index(key);
        buckets_[idx] = erase(this->buckets_[idx], key);
    }

    value_type *find(const key_type &key) {
        int idx = bucket_index(key);
        hash_node *entry = buckets_[idx];
        while (entry && !equal_pred_(entry->key, key)) {
            entry = entry->next;
        }
        return entry && equal_pred_(entry->key, key) ? &entry->val : nullptr;
    }

  private:
    struct hash_node {
        key_type key;
        value_type val;
        hash_node *next;
    };

    hash_node *hash_node_new(key_type key, value_type val) {
        return new hash_node{move(key), move(val), nullptr};
    }

    void hash_node_delete(hash_node *entry) {
        while (entry) {
            hash_node *current = entry;
            entry = entry->next;
            delete current;
        }
    }

    hash_node *erase(hash_node *root, const key_type &key) {
        if (!root) {
            return root;
        }
        if (equal_pred_(root->key, key)) {
            hash_node *next = root->next;
            root->next = nullptr;
            hash_node_delete(root);
            return next;
        }
        root->next = erase(root->next, key);
        return root;
    }

    int bucket_index(const key_type &key) const {
        return hasher_(key) % bucket_size_;
    }

  private:
    int bucket_size_;
    unique_ptr<hash_node *[]> buckets_;
    key_hash hasher_;
    key_equal equal_pred_;
};

} // namespace

TEST_CASE("separate_chainning_common", "[hashtable]") {
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
        REQUIRE(r != nullptr);
        CHECK(*r == expected_ht[key[i]]);
    }

    for (int i = 0; i < k_size; i++) {
        ht.erase(key[i]);
        auto r = ht.find(key[i]);
        CHECK(r == nullptr);
    }
}