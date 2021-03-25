#include <unordered_set>

#include "base.hpp"

namespace {

using namespace std;

struct linked_node {
  int val;
  linked_node* next;

  linked_node(int v) : val(v), next(nullptr) {}
  ~linked_node() { delete next; }
};

linked_node* linked_list_insert(linked_node* head, int val) {
  if (!head) {
    head = new linked_node(val);
  } else {
    linked_node* current = head;
    while (current && current->next) {
      current = current->next;
    }
    current->next = new linked_node(val);
  }
  return head;
}

linked_node* linked_list_find(linked_node* head, int val) {
  linked_node* current = head;
  while (current) {
    if (current->val == val) {
      return current;
    }
    current = current->next;
  }
  return nullptr;
}

linked_node* build_linked_list(const vector<int>& values) {
  linked_node* head = nullptr;
  for (int v : values) {
    head = linked_list_insert(head, v);
  }
  return head;
}

bool has_circular_loop(linked_node* head) {
  unordered_set<linked_node*> visisted_nodes;
  while (head) {
    if (visisted_nodes.count(head)) {
      return true;
    }
    visisted_nodes.insert(head);
    head = head->next;
  }
  return false;
}

} // namespace

TEST_CASE("find_curcular_loop", "[link_list]") {
  int k_test_count = 100;
  while (k_test_count-- >= 0) {
    const vector<int> input = generate_random_number(100);
    unique_ptr<linked_node> head{build_linked_list(input)};
    REQUIRE_FALSE(has_circular_loop(head.get()));

    const int m = input[input.size() / 2];
    auto median_node = linked_list_find(head.get(), m);
    REQUIRE(median_node != nullptr);
    // save the old median_next
    auto old_median_next = median_node->next;
    // mess the next with the head
    median_node->next = head.get();
    REQUIRE(has_circular_loop(head.get()));
    // cleanup the mess to avoid potential crash
    median_node->next = old_median_next;
  }
}