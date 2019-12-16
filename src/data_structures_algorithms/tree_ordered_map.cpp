#include <iostream>
#include <string>
#include <functional>
#include <array>
#include <random>

#include "cpptest.hpp"

using namespace std;

namespace {

template <class K, class V, class Compare = std::less<K>>
class ordered_map {
public:
    using key_type = K;
    using value_type = V;
    using key_compare = Compare;
    using size_type = size_t;

    ordered_map() : pred(), head(nullptr), cnt(0) {
    }

    ~ordered_map() {
        bst_delete(head);
    }

    bool insert(key_type key, value_type val) {
        head = bst_insert(head, move(key), move(val), pred);
        ++cnt;
        return head;
    }

    bool erase(const key_type& key) {
        head = bst_remove(head, key, pred);
        --cnt;
        return false;
    }

    const value_type* find(const key_type& key) const {
        const tree_node* node = bst_find(head, key, pred);
        if (node) {
            return &node->val;
        }
        return nullptr;
    }

    size_type size() const {
        return cnt;
    }

private:
    template <class K, class V>
    struct bst_node {
        bst_node* left;
        bst_node* right;
        K key;
        V val;
    };

    using tree_node = bst_node<key_type, value_type>;

    static tree_node* bst_new(key_type key, value_type val) {
        return new tree_node {
            nullptr,
            nullptr,
            std::move(key),
            std::move(val)
        };
    }

    static void bst_delete(tree_node* root) {
        if (root == nullptr)
            return;
        bst_delete(root->left);
        bst_delete(root->right);
        delete root;
    }

    static tree_node* bst_insert(tree_node* root, key_type key, value_type val, const key_compare& pred) {
        if (root == nullptr) {
            return bst_new(std::move(key), std::move(val));
        }

        if (pred(key, root->key)) { // strickly less
            root->left = bst_insert(root->left, move(key), move(val), pred);
        } else if (pred(root->key, key)) { // strickly bigger
            root->right = bst_insert(root->right, move(key), move(val), pred);
        } else { // equal
            root->val = move(val);
        }
        return root;
    }

    static tree_node* bst_remove(tree_node* root, const key_type& key, const key_compare& pred) {
        if (root == nullptr) {
            return root;
        }

        // a bit more complex and figure out later
        return nullptr;
    }

    static const tree_node* bst_find(const tree_node* root, const key_type& key, const key_compare& pred) {
        if (root == nullptr) {
            return root;
        }

        if (pred(key, root->key)) { // strickly less
            return bst_find(root->left, key, pred);
        } else if (pred(root->key, key)) { // strickly bigger
            return bst_find(root->right, key, pred);
        } else { // equal
            return root;
        }
    }

private:
    key_compare pred;
    tree_node* head;
    size_type cnt;
};

}

TEST(TreeSuite, ordered_map_int_int) {
    ordered_map<int, int> mp;
    constexpr int k_size = 1000;
    const vector<int> key = generate_random_number(k_size);
    const vector<int> val = generate_random_number(k_size);
    for (int i = 0; i < k_size; i++) {
        EXPECT_TRUE(mp.insert(key[i], val[i]));
    }

    for (int i = 0; i < k_size; i++) {
        auto r = mp.find(key[i]);
        EXPECT_TRUE(r != nullptr);
        EXPECT_EQ(*r, val[i]);
    }
}