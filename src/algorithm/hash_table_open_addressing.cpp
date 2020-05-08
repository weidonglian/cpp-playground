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
          buckets_(make_unique<bucket[]>(bucket_size_)), hasher_(),
          equal_to_() {
    }

    ~hash_table() = default;

    void insert(key_type key, value_type val) {
        // first get
        int idx = bucket_index(key);
        while (true) {
            check_resize_if_needed(idx);
            bucket &entry = buckets_[idx];
            if (!entry.is_filled() || equal_to_(entry.key, key)) {
                entry.fill(std::move(key), std::move(val));
                return;
            }
            ++idx;
        }
    }

    void erase(const key_type& key) {
        int idx = do_find(key);
        if (idx != -1) {
            bucket& entry = buckets_[idx];
            entry.remove();
        }
    }

    value_type* find(const key_type& key) {
        int idx = do_find(key);
        if (idx != -1)
            return &buckets_[idx].val;
        return nullptr;
    }

  private:
    // 'empty' means a fresh untouched bucket, should always be in the end.
    // 'filled' stands for a value has been filled in
    // 'deleted' indicates a used bucket but now empty.
    enum class bucket_state { empty = 0, filled = 2, deleted = 3 };

    struct bucket {
        bucket() : key{}, val{}, state(bucket_state::empty) {
        }

        bool is_empty() const {
            return state == bucket_state::empty;
        }

        bool is_filled() const {
            return state == bucket_state::filled;
        }

        bool is_deleted() const {
            return state == bucket_state::deleted;
        }

        void fill(key_type key, value_type val) {
            this->key = std::move(key);
            this->val = std::move(val);
            state = bucket_state::filled;
        }

        void remove() {
            key_type local_key{};
            value_type local_val{};
            swap(local_key, key);
            swap(local_val, val);
            state = bucket_state::deleted;
        }

        key_type key;
        value_type val;
        bucket_state state;
    };

    int bucket_index(const key_type& key) const {
        return hasher_(key) % bucket_size_;
    }

    void check_resize_if_needed(int idx) {
        // silly resize if bigger, ignore the load factor for now.
        if (idx >= bucket_size_) {
            unique_ptr<bucket[]> bks = make_unique<bucket[]>(bucket_size_*2);
            move(buckets_.get(), buckets_.get() + bucket_size_, bks.get());
            swap(buckets_, bks);
            bucket_size_ = bucket_size_*2;
        }
    }

    int do_find(const key_type &key) const {
        for (int idx = bucket_index(key); idx < bucket_size_; ++idx) {
            const bucket& entry = buckets_[idx];
            if (entry.is_empty()) {
                break;
            }
            if (entry.is_filled() && equal_to_(entry.key, key)) {
                return idx;
            }
        }
        return -1;
    }

  private:
    int bucket_size_;
    unique_ptr<bucket[]> buckets_;
    key_hash hasher_;
    key_equal equal_to_;
};

} // namespace

TEST(HashTableSuite, open_addressing_common) {
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
        ASSERT_TRUE(r != nullptr) << i;
        EXPECT_EQ(*r, expected_ht[key[i]]);
    }

    for (int i = 0; i < k_size; i++) {
        ht.erase(key[i]);
        auto r = ht.find(key[i]);
        EXPECT_TRUE(r == nullptr);
    }
}