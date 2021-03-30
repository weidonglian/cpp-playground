#include "base.hpp"

namespace {

struct lk_node {
  int data;
  lk_node* next;
  lk_node* child;

  lk_node(int val) : data(val), next(nullptr), child(nullptr) {}
  lk_node(int val, lk_node* chd) : data(val), next(nullptr), child(chd) {}
  ~lk_node() {
    delete next;
    delete child;
  }
};

lk_node* populate(const std::vector<int>& samples) {
  lk_node* root = nullptr;
  return root;
}

lk_node* tail(lk_node* head) {
  lk_node* current = head;
  while (current && current->next) {
    current = current->next;
  }
  return current;
}

lk_node* flatten(lk_node* head) {
  lk_node* current = head;
  while (current) {
    if (current->child) {
      lk_node* flat_child_list = flatten(current->child);
      lk_node* flat_child_list_tail = tail(flat_child_list);
      flat_child_list_tail->next = current->next;
      current->next = flat_child_list;
      current = flat_child_list_tail->next;
    } else {
      current = current->next;
    }
  }
  return head;
}

} // namespace

/**
 * @brief A link list node could store the normal data and a pointer may/maynot point to another linked_list.
 *        The goal is flattern the given link list into a link list that only contains normal data.
 * Note: the nested/child linked list could also has nested multiple levels. We should recursively flatten
         the child node using divide and conquer.
 */
TEST_CASE("flatten_nested_link_list", "[link_list]") {}

/**
 * @brief A link list node could store the normal data and a pointer may/maynot point to another linked_list.
 *        The goal is flattern the given link list into a link list level by level. Level 0 first and then
 *        second level, ..., etc.
 * Note: the nested/child linked list could also has nested multiple levels. We should recursively flatten
         the child node using divide and conquer.
 */
TEST_CASE("flatten_nested_link_list_level_by_level", "[link_list]") {}
