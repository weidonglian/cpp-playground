#include <iostream>

#include "algorithms.hpp"

namespace {

class vt_node {
public:
  vt_node(std::string name) : name_(std::move(name)), left_(nullptr), right_(nullptr) {}

  ~vt_node() {
    delete left_;
    delete right_;
  }

  void set_left(vt_node* left) {
    delete left_;
    left_ = left;
  }

  vt_node* left() const { return left_; }

  void set_right(vt_node* right) {
    delete right_;
    right_ = right;
  }

  vt_node* right() const { return right_; }

  void insert_bfs(const std::string& name) {
    size_t level = 0;
    vt_node* node = nullptr;
    while (!node) {
      visit_bfs(this, level++, [&](vt_node* n) {
        if (!node && !n->left_) {
          node = new vt_node(name);
          n->set_left(node);
        }

        if (!node && !n->right_) {
          node = new vt_node(name);
          n->set_right(node);
        }
      });
    }
  }

  void insert_dfs(const std::string& name) { insert_dfs(this, name); }

  void print_bfs() {
    size_t level = 0;
    size_t print_cnt = 0;
    do {
      print_cnt = 0;
      std::cout << "level_" << level << ": -";
      visit_bfs(this, level, [&](vt_node* n) {
        ++print_cnt;
        std::cout << n->name_ << "-";
      });
      std::cout << std::endl;
      level++;
    } while (print_cnt);
  }

  void print_dfs() {
    visit_dfs(this, [](vt_node* n) { std::cout << n->name_ << "-"; });
    std::cout << std::endl;
  }

private:
  using node_cb = std::function<void(vt_node*)>;
  using node_cb_t = std::function<bool(vt_node*)>;

  // visit the tree in depth first search if callback return true
  static void insert_dfs(vt_node* root, const std::string& name) {
    if (!root) {
      return;
    }
    if (!root->left()) {
      root->set_left(new vt_node(name));
      return;
    }
    if (!root->right()) {
      root->set_right(new vt_node(name));
      return;
    }
    insert_dfs(root->left(), name);
  }

  // visit the tree in depth first search
  static void visit_dfs(vt_node* root, const node_cb& cb) {
    if (!root) {
      return;
    }
    cb(root);
    visit_dfs(root->left_, cb);
    visit_dfs(root->right_, cb);
  }

  // visit the tree in breadth first search
  static void visit_bfs(vt_node* root, size_t level, const node_cb& cb) {
    if (!root) {
      return;
    }

    if (!level) {
      cb(root);
    } else {
      visit_bfs(root->left_, level - 1, cb);
      visit_bfs(root->right_, level - 1, cb);
    }
  }

  std::string name_;
  vt_node* left_;
  vt_node* right_;
};

} // namespace

TEST_CASE("visit_tree_bst", "[tree]") {
  auto root = std::make_unique<vt_node>("0");
  for (int i = 1; i <= 50; ++i) {
    root->insert_bfs(std::to_string(i));
  }
  root->print_bfs();
  std::cout << std::endl;
}

TEST_CASE("visit_tree_dst", "[tree]") {
  auto root = std::make_unique<vt_node>("0");
  for (int i = 1; i <= 10; ++i) {
    root->insert_dfs(std::to_string(i));
  }
  root->print_dfs();
  root->print_bfs();
  std::cout << std::endl;
}