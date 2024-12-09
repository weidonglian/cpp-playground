#include <algorithm>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <iterator>
#include <optional>
#include <vector>

#include "base.hpp"

struct tree_node {
  explicit tree_node(int value) : value_(value), left_(nullptr), right_(nullptr) {}
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
  tree() : root_(nullptr) {}
  ~tree() { delete root_; }

  // Load the data in the breadth first access order
  void populate(const std::vector<int>& data) {
    for (int v : data) {
      if (!root_) {
        root_ = new tree_node(v);
      } else {
        int level = 0;
        while (!populate_bfs(root_, level++, v)) {
        }
      }
    }
  }

  void populate(const std::vector<std::optional<int>>& data) {
    if (data.empty()) {
      return;
    }

    if (root_) {
      delete root_;
      root_ = nullptr;
    }

    if (!data[0]) {
      return;
    }
    root_ = new tree_node(data[0].value());

    value_iter it(data.begin() + 1, data.end());
    int level = 0;
    while (it.has_next()) {
      fill_bfs(root_, level++, it);
    }
  }

  void print() const {
    int print_cnt;
    int level = 0;
    do {
      print_cnt = 0;
      std::cout << "L" << level << ": -";
      visit_bfs(root_, level, [&](tree_node* n) {
        print_cnt++;
        std::cout << (n ? std::to_string(n->value_) : "x") << "-";
      });
      std::cout << std::endl;
      level++;
    } while (print_cnt);

    std::cout << std::endl;
  }
  bool operator==(const tree& right) const {
    const tree_node* r1 = root_;
    const tree_node* r2 = right.root_;
    return node_equal(r1, r2);
  }

  bool operator!=(const tree& right) const { return !(*this == right); }

  void swap_left_right() { node_swap_left_right(root_); }
  int measure_level() const { return measure_level_recur(this->root_, 0); }

private:
  using node_cb = std::function<void(tree_node*)>;

  template <class Iter>
  struct value_iter_t {
    using value_type = typename std::iterator_traits<Iter>::value_type;

    value_iter_t(Iter start, Iter end) : current_(start), end_(end) {}
    bool has_next() const { return current_ != end_; }
    const value_type& next() { return *current_++; }

  private:
    Iter current_;
    Iter end_;
  };

  using value_iter = value_iter_t<std::vector<std::optional<int>>::const_iterator>;

  static int measure_level_recur(const tree_node* root, int level) {
    if (root && root->left_ && root->right_) {
      return std::max(measure_level_recur(root->left_, level + 1), measure_level_recur(root->right_, level + 1));
    } else if (root && root->left_) {
      return measure_level_recur(root->left_, level + 1);
    } else if (root && root->right_) {
      return measure_level_recur(root->right_, level + 1);
    } else {
      return level;
    }
  }

  static void node_swap_left_right(tree_node* root) {
    if (!root) {
      return;
    }
    node_swap_left_right(root->left_);
    node_swap_left_right(root->right_);
    std::swap(root->left_, root->right_);
  }

  static bool node_equal(const tree_node* r1, const tree_node* r2) {
    if (!r1 && !r2) {
      return true;
    }
    if (!(r1 && r2)) {
      return false;
    }
    if (r1->value_ != r2->value_) {
      return false;
    }
    return node_equal(r1->left_, r2->left_) && node_equal(r2->right_, r2->right_);
  }

  static void fill_bfs(tree_node* root, size_t level, value_iter& vit) {
    if (!root) {
      return;
    }
    if (!level) {
      if (vit.has_next()) {
        auto& v1 = vit.next();
        if (v1) {
          root->left_ = new tree_node(*v1);
        }
      }

      if (vit.has_next()) {
        const auto& v2 = vit.next();
        if (v2) {
          root->right_ = new tree_node(*v2);
        }
      }
    } else {
      fill_bfs(root->left_, level - 1, vit);
      fill_bfs(root->right_, level - 1, vit);
    }
  }

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
    if (!level) {
      fn_cb(root);
    } else if (root) {
      visit_bfs(root->left_, level - 1, fn_cb);
      visit_bfs(root->right_, level - 1, fn_cb);
    }
  }
  tree_node* root_;
};

std::vector<int> gen_random_list(int sz) {
  std::vector<int> data;
  data.resize(sz);
  for (auto& v : data) {
    v = std::rand();
  }
  return data;
}

// Calculate the level of full bindary search tree with given size.
int calculate_level(int sz) {
  int level = 0;
  int cnt = 1;
  int power = 2;
  while (sz > cnt) {
    ++level;
    cnt += power;
    power *= 2;
  }
  return level;
}

TEST_CASE("calcualte_level", "[tree]") {
  REQUIRE(calculate_level(0) == 0);
  REQUIRE(calculate_level(1) == 0);
  REQUIRE(calculate_level(2) == 1);
  REQUIRE(calculate_level(3) == 1);
  REQUIRE(calculate_level(4) == 2);
  REQUIRE(calculate_level(5) == 2);
  REQUIRE(calculate_level(6) == 2);
  REQUIRE(calculate_level(7) == 2);
  REQUIRE(calculate_level(8) == 3);
  REQUIRE(calculate_level(11) == 3);
  REQUIRE(calculate_level(12) == 3);
  REQUIRE(calculate_level(20) == 4);
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
    // t1.print();
    tree t2;
    t2.populate(data);
    // t2.print();
    REQUIRE(t1 == t2);
    REQUIRE(t1.measure_level() == calculate_level(static_cast<int>(data.size())));
    REQUIRE(t2.measure_level() == calculate_level(static_cast<int>(data.size())));
  }
}

TEST_CASE("tree_compare_equal", "[tree]") {
  std::vector<int> data1{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
  tree t1;
  t1.populate(data1);
  // t1.print();
  tree t2;
  t2.populate(data1);
  // t2.print();
  REQUIRE(t1 == t2);
  REQUIRE(t1.measure_level() == 3);
  REQUIRE(t1.measure_level() == calculate_level(static_cast<int>(data1.size())));
}

TEST_CASE("tree_compare_not_equal", "[tree]") {
  std::vector<int> data1{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
  std::vector<int> data2{1, 2, 3, 5, 4, 7, 6, 8, 9, 10, 11, 12};
  tree t1;
  t1.populate(data1);
  // t1.print();
  tree t2;
  t2.populate(data2);
  // t2.print();
  REQUIRE(t1 != t2);
}

TEST_CASE("tree_compare_opt_equal", "[tree]") {
  std::vector<std::optional<int>> data1{1, 2, 3, std::nullopt, 5, 6, 7, 8, 9, 10, 11, 12};
  std::vector<std::optional<int>> data2{1, 2, 3, std::nullopt, 5, 6, 7, 8, 9, 10, 11, 12};
  tree t1;
  t1.populate(data1);
  // t1.print();
  tree t2;
  t2.populate(data2);
  // t2.print();
  REQUIRE(t1 == t2);
}

TEST_CASE("tree_compare_opt_not_equal", "[tree]") {
  std::vector<std::optional<int>> data1{1, 2, 3, std::nullopt, 5, 6, 7, 8, 9, 10, 11, 12};
  std::vector<std::optional<int>> data2{1, 2, 3, 5, std::nullopt, 6, 7, 8, 9, 10, 11, 12};
  tree t1;
  t1.populate(data1);
  // t1.print();
  tree t2;
  t2.populate(data2);
  // t2.print();
  REQUIRE(t1 != t2);
}

TEST_CASE("tree_compare_swap", "[tree]") {
  std::vector<std::optional<int>> data1{1, 3, 2, std::nullopt, 5, 7, 6, 8, 9, 10, 11, 12, std::nullopt};
  std::vector<std::optional<int>> data2{1, 2, 3, 6, 7, 5, std::nullopt, std::nullopt, 12, 11, 10, 9, 8};
  tree t1;
  t1.populate(data1);
  // t1.print();
  tree t2;
  t2.populate(data2);
  // t2.print();
  REQUIRE(t1 != t2);
  t1.swap_left_right();
  // t1.print();
  REQUIRE(t1 == t2);
}