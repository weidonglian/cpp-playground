#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <string>

#include "base.hpp"

namespace {

struct linked_node {
  linked_node(int digit) : digit_(digit), next_(nullptr) {}
  ~linked_node() { delete next_; }
  int digit_;
  linked_node* next_;
};

class linked_list {
public:
  linked_list() : head{nullptr}, tail(nullptr) {}
  ~linked_list() {
    delete head;
    tail = nullptr;
    head = nullptr;
  }

  void push_back(int digit) {
    linked_node* node = new linked_node(digit);
    if (!tail) {
      tail = head = node;
    } else {
      tail->next_ = node;
      tail = tail->next_;
    }
  }

  size_t size() const {
    size_t cnt = 0;
    linked_node* h = head;
    while (h) {
      ++cnt;
      h = h->next_;
    }
    return cnt;
  }
  std::string to_string() const {
    std::string result;
    linked_node* h = head;
    if (!h)
      return {};
    result.resize(size());
    int idx = result.size() - 1;
    while (h) {
      result[idx--] = '0' + h->digit_;
      h = h->next_;
    }
    return result;
  }

  linked_list operator+(const linked_list& right) const {
    linked_list result;
    const linked_node* h1 = this->head;
    const linked_node* h2 = right.head;
    bool carray = false;
    while (h1 || h2) {
      const int sum = (h1 ? h1->digit_ : 0) + (h2 ? h2->digit_ : 0) + carray;
      carray = sum / 10;
      result.push_back(sum % 10);
      h1 = h1 ? h1->next_ : h1;
      h2 = h2 ? h2->next_ : h2;
    }
    if (carray) {
      result.push_back(carray);
    }
    return result;
  }

private:
  linked_node* head;
  linked_node* tail;
};

int test_two_integers(int v1, int v2) {
  const std::string n1 = std::to_string(v1);
  const std::string n2 = std::to_string(v2);
  // create two linked list from the given strings
  linked_list l1, l2;
  for (auto rit = n1.rbegin(); rit != n1.rend(); ++rit) {
    l1.push_back(*rit - '0');
  }
  for (auto rit = n2.rbegin(); rit != n2.rend(); ++rit) {
    l2.push_back(*rit - '0');
  }
  return std::stoi((l1 + l2).to_string());
}

} // namespace
/**
 * @brief Given the head pointers of two linked lists where each linked list represents
 * an integer number (each node is a digit), add them and return the resulting linked list.
 * Here, the first node in a list represents the least significant digit. *
 */
TEST_CASE("add_two_integers", "[link_list]") {
  REQUIRE(test_two_integers(9901, 237) == 10138);
  int k_test_count = 100;
  while (k_test_count-- > 0) {
    const int v1 = std::rand();
    const int v2 = std::rand();
    INFO("testing " + std::to_string(v1) + " + " + std::to_string(v2));
    REQUIRE(test_two_integers(v1, v2) == v1 + v2);
  }
}