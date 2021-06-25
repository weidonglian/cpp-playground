#include <cstdlib>
#include <iostream>
#include <iterator>

#include "base.hpp"

struct linked_node {
  linked_node(int value) : value_(value), next_(nullptr) {}
  ~linked_node() { delete next_; }
  int value_;
  linked_node* next_;
};

class linked_list {
public:
  linked_list() : head_(nullptr), tail_(nullptr) {}
  ~linked_list() { delete head_; }

  void push_back(int value) {
    linked_node* node = new linked_node(value);
    if (!tail_) {
      head_ = tail_ = node;
    } else {
      tail_->next_ = node;
      tail_ = tail_->next_;
    }
  }

  linked_list operator+(const linked_list& right) const {
    linked_list result;
    linked_node* h1 = this->head_;
    linked_node* h2 = right.head_;
    while (h1 && h2) {
      if (h1->value_ <= h2->value_) {
        result.push_back(h1->value_);
        h1 = h1->next_;
      } else {
        result.push_back(h2->value_);
        h2 = h2->next_;
      }
    }

    while (h1) {
      result.push_back(h1->value_);
      h1 = h1->next_;
    }

    while (h2) {
      result.push_back(h2->value_);
      h2 = h2->next_;
    }

    return result;
  }

  std::vector<int> to_vector() const {
    std::vector<int> v;
    linked_node* h = head_;
    while (h) {
      v.push_back(h->value_);
      h = h->next_;
    }
    return v;
  }

private:
  linked_node* head_;
  linked_node* tail_; // not owned
};

std::vector<int> test_sorted_link_list(const std::vector<int>& arr1, const std::vector<int>& arr2) {
  linked_list l1, l2;
  for (auto v : arr1) {
    l1.push_back(v);
  }
  for (auto v : arr2) {
    l2.push_back(v);
  }
  return (l1 + l2).to_vector();
}

std::vector<int> gen_random_list(size_t sz) {
  std::vector<int> arr;
  arr.reserve(sz);
  while (sz-- > 0) {
    arr.push_back(rand());
  }
  return arr;
}

/**
 * @brief Merge two sorted linked and the new one should keep sorted.
 *
 */
TEST_CASE("merge_two_sorted_link_list", "[link_list]") {
  REQUIRE(test_sorted_link_list({1, 4, 9, 10}, {1, 2, 4, 4, 5, 7, 8, 10}) ==
          std::vector{1, 1, 2, 4, 4, 4, 5, 7, 8, 9, 10, 10});
  int k_test_cnt = 100;
  while (k_test_cnt-- > 0) {
    auto l1 = gen_random_list(std::rand() % 1000);
    auto l2 = gen_random_list(std::rand() % 1000);
    std::sort(l1.begin(), l1.end());
    std::sort(l2.begin(), l2.end());
    std::vector<int> expected;
    expected.reserve(l1.size() + l2.size());
    std::merge(l1.begin(), l1.end(), l2.begin(), l2.end(), std::back_inserter(expected));
    auto result = test_sorted_link_list(l1, l2);
    REQUIRE(result == expected);
  }
}