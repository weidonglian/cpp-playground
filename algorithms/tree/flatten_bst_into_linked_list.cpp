#include "base.hpp"

namespace {

struct bst_node {
  bst_node* left;
  bst_node* right;
  int val;
};

struct lk_node {
  lk_node* next;
  int val;
};

} // namespace

/**
 * @brief Flatten the bst tree into a sorted linked list.
 *
 */
TEST_CASE("flatten_bst_into_linked_list", "[tree]") {}