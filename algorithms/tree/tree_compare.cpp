#include <algorithm>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <vector>

#include "base.hpp"

struct tree_node {
  tree_node(int value) : value_(value), left_(nullptr), right_(nullptr) {}
  ~tree_node() {
    delete left_;
    delete right_;
  }

  int value_;
  tree_node* left_;
  tree_node* right_;
};

class tree {
public:
  tree() : root(nullptr) {}
  ~tree() { delete root; }

  // Load the data in the breadth first access order
  void populate(const std::vector<int>& data) {
    for (int v : data) {
      if (!root) {
        root = new tree_node(v);
      } else {
        int level = 0;
        while (!populate_bfs(root, level++, v)) {
        }
      }
    }
  }

  void print() const {
    int print_cnt;
    int level = 0;
    do {
      print_cnt = 0;
      std::cout << "level-" << level << ": ";
      visit_bfs(root, level, [&](tree_node* n) {
        print_cnt++;
        std::cout << n->value_ << "-";
      });
      std::cout << std::endl;
      level++;
    } while (print_cnt);

    std::cout << std::endl;
  }
  bool operator==(const tree& right) const { return true; }

private:
  using node_cb = std::function<void(tree_node*)>;

  static bool populate_bfs(tree_node* root, size_t level, int val) {
    if (!root) {
      return false;
    }
    if (!level) {
      if (!root->left_) {
        root->left_ = new tree_node(val);
        return true;
      }
      if (!root->right_) {
        root->right_ = new tree_node(val);
        return true;
      }
    } else {
      return populate_bfs(root->left_, level - 1, val) || populate_bfs(root->right_, level - 1, val);
    }
    return false;
  }

  static void visit_bfs(tree_node* root, size_t level, const node_cb& fn_cb) {
    if (!root) {
      return;
    }

    if (!level) {
      fn_cb(root);
    } else {
      visit_bfs(root->left_, level - 1, fn_cb);
      visit_bfs(root->right_, level - 1, fn_cb);
    }
  }
  tree_node* root;
};

std::vector<int> gen_random_list(int sz) {
  std::vector<int> data;
  data.resize(sz);
  for (auto& v : data) {
    v = std::rand();
  }
  return data;
}

/**
 * @brief Compare the equality of two binary tree.
 *
 * Note: it is necessarily binary search tree. We could
 * randomly populate the tree structure.
 */
TEST_CASE("tree_compare_random", "[tree]") {
  int k_test_cout = 100;
  while (k_test_cout-- > 0) {
    auto data = gen_random_list(std::rand() % 100);
    tree t1;
    t1.populate(data);
    t1.print();
    tree t2;
    t2.populate(data);
    t2.print();
    REQUIRE(t1 == t2);
  }
}

TEST_CASE("tree_compare", "[tree]") {
  std::vector<int> data{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
  tree t1;
  t1.populate(data);
  t1.print();
  tree t2;
  t2.populate(data);
  t2.print();
  REQUIRE(t1 == t2);
}