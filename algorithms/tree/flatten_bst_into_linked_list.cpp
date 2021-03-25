#include <vector>

#include "base.hpp"
#include "random.hpp"

namespace {

using namespace std;

struct bst_node {
  int val;
  bst_node* left;
  bst_node* right;

  bst_node(int v) : val(v), left(nullptr), right(nullptr) {}
  ~bst_node() {
    delete left;
    delete right;
  }
};

struct lk_node {
  int val;
  lk_node* next;

  lk_node(int v) : val(v), next(nullptr) {}
  ~lk_node() { delete next; }
};

lk_node* linked_list_insert(lk_node* head, int val) {
  if (!head) {
    head = new lk_node{val};
  } else {
    lk_node* current = head;
    while (current && current->next) {
      current = current->next;
    }
    current->next = new lk_node{val};
  }
  return head;
}

bst_node* bst_tree_insert(bst_node* root, int val) {
  if (!root) {
    root = new bst_node{val};
  } else {
    if (val > root->val) {
      root->right = bst_tree_insert(root->right, val);
    } else {
      root->left = bst_tree_insert(root->left, val);
    }
  }
  return root;
}

using fn_node = std::function<void(bst_node*)>;

void bst_tree_visit_dfs(bst_node* root, const fn_node& fn) {
  if (!root) {
    return;
  }
  // visit left child
  if (root->left) {
    bst_tree_visit_dfs(root->left, fn);
  }
  // vist node itself
  fn(root);

  // vist right child
  if (root->right) {
    bst_tree_visit_dfs(root->right, fn);
  }
}

bst_node* build_bst_tree(const vector<int>& arr) {
  bst_node* root = nullptr;
  for (auto v : arr) {
    root = bst_tree_insert(root, v);
  }
  return root;
}

lk_node* flatten_bst_into_linked_list(bst_node* root) {
  lk_node* head = nullptr;
  bst_tree_visit_dfs(root, [&](bst_node* node) { head = linked_list_insert(head, node->val); });
  return head;
}

vector<int> convert_linked_list_to_vector(lk_node* head) {
  vector<int> result;
  while (head) {
    result.push_back(head->val);
    head = head->next;
  }
  return result;
}

vector<int> test_flatten_bst_into_linked_list(const vector<int>& arr) {
  std::unique_ptr<bst_node> root(build_bst_tree(arr));
  std::unique_ptr<lk_node> head(flatten_bst_into_linked_list(root.get()));
  auto result = convert_linked_list_to_vector(head.get());
}

} // namespace

/**
 * @brief Flatten the bst tree into a sorted linked list.
 *
 */
TEST_CASE("flatten_bst_into_linked_list", "[tree]") {
  const vector<int> input = {1, 2, 8, 5, 3, 9, 6};
  auto expected = input;
  std::sort(expected.begin(), expected.end());
  REQUIRE(test_flatten_bst_into_linked_list(input) == expected);
}

TEST_CASE("flatten_bst_into_linked_list_random", "[tree]") {
  int k_test_count = 1000;
  while (k_test_count-- >= 0) {
    const vector<int> input = generate_random_number(1000);
    auto expected = input;
    std::sort(expected.begin(), expected.end());
    REQUIRE(test_flatten_bst_into_linked_list(input) == expected);
  }
}