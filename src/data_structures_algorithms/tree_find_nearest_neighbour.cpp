#include "cpptest.hpp"
#include "gtest/gtest.h"
#include <cstddef>
#include <functional>
#include <iostream>
#include <limits>
#include <memory>
#include <optional>
#include <random>
#include <vector>
#include <map>
#include <cmath>

using namespace std;

namespace nns {

constexpr int k_dims = 2;

using point = array<int, k_dims>;

// Mahatan distance
int distance(const point& p1, const point& p2) {
  int dist = 0;
  for (int i = 0; i < k_dims; ++i)
    dist += abs(p1[i] - p2[i]);
  return dist;
}

struct kd_node {
  kd_node *lo; // left/below, lower
  kd_node *hi; // right/above, higher
  point pt;    // the node's point if no children node, i.e. leaf
};

kd_node *kd_new(point pt) {
  return new kd_node{nullptr, nullptr, pt};
}

void kd_delete(kd_node* root) {
  if (!root) {
    return;
  }

  if (root->lo) {
    kd_delete(root->lo);
  }

  if (root->hi) {
    kd_delete(root->hi);
  }

  delete root;
}

kd_node *kd_insert(kd_node *root, point pt, int depth = 0) {
  if (!root) {
    return kd_new(pt); // tree is empty and return a new root
  }

  const int dim = depth % k_dims;
  if (pt[dim] < root->pt[dim]) {
    root->lo = kd_insert(root->lo, pt, depth+1);
  } else {
    root->hi = kd_insert(root->hi, pt, depth+1);
  }
  return root;
}

template <class InputIterator>
kd_node* kd_build(InputIterator first, InputIterator last) {
  kd_node* root = nullptr;
  while (first != last) {
    root = kd_insert(root, *first);
    ++first;
  }
  return root;
}

// Find the node that the given point should be inserted
const kd_node* kd_find_insert_position(const kd_node* root, point pt, int depth = 0) {
  if (!root)
    return root;
  const int dim = depth % k_dims;
  if (pt[dim] < root->pt[dim]) {
    return root->lo ? kd_find_insert_position(root->lo, pt, depth+1) : root;
  } else {
    return root->hi ? kd_find_insert_position(root->hi, pt, depth+1) : root;
  }
}

// Find the nearest neightbour with condtion <= min_dist, otherwise return nullptr
const kd_node* kd_find_nearest(const kd_node* root, point pt_query, int min_dist, int depth = 0) {
  // Current node is empty, then return it.
  if (!root)
    return nullptr;

  const kd_node* best = nullptr;
  // Current node to update the min_dist
  {
    const int dst = distance(pt_query, root->pt);
    if (dst < min_dist) {
      min_dist = dst;
      best = root;
    }
  }

  // determine which branch to search
  const int dim = depth % k_dims;
  // distance in the corresponding dimension
  const int signed_dst = pt_query[dim] - root->pt[dim]; // signed distance
  bool should_search_lo = false;
  bool should_search_hi = false;
  if (signed_dst < -min_dist && root->lo) {
    // the query point on the far left side of the dim axis. search the lo branch
    should_search_lo = true;
  } else if (signed_dst > min_dist) {
    // the query point on the far right side of the dim axis. search only the hi branch
    should_search_hi = true;
  } else {
    // Too close the boundary, We need to search two branches, lo and hi.
    should_search_lo = true;
    should_search_hi = true;
  }

  if (should_search_lo && root->lo) {
    const kd_node* best_lo = kd_find_nearest(root->lo, pt_query, min_dist);
    if (best_lo) { // exist must be smaller
      min_dist = distance(pt_query, best_lo->pt);
      best = best_lo;
    }
  }

  if (should_search_hi && root->hi) {
    const kd_node* best_hi = kd_find_nearest(root->hi, pt_query, min_dist);
    if (best_hi) {
      min_dist = distance(pt_query, best_hi->pt);
      best = best_hi;
    }
  }
  // both lo and hi branches do not find anything, then return root.
  return best;
}

optional<point> nns_kd_tree_search(const vector<point>& points, point pt_query) {
  const kd_node* root = kd_build(begin(points), end(points));

  int min_dist = numeric_limits<int>::max();
  const kd_node* best_node = nullptr;
  {
    // Try to guess what is possible min distance
    const kd_node *init_guess = kd_find_insert_position(root, pt_query);
    if (init_guess) {
      min_dist = distance(pt_query, init_guess->pt);
      best_node = init_guess;
    }
  }

  const kd_node *nearest = kd_find_nearest(root, pt_query, min_dist);
  if (nearest) {
    min_dist = distance(pt_query, nearest->pt);
    best_node = nearest;
  }

  if (best_node) {
    return make_optional(best_node->pt);
  }

  return nullopt;
}


optional<point> nns_linear_search(const vector<point>& points, point pt_query) {
  optional<point> result;
  int min_dst = 0;
  const int sz_total = points.size();
  for (int idx = 0; idx < sz_total; ++idx) {
    const int dst = distance(points[idx], pt_query);
    if (!result || dst < min_dst) {
      result = points[idx];
      min_dst = dst;
    }
  }
  return result;
}

enum class find_policy {
  defaut,
  linear_search,
  kd_tree
};

optional<point> find_nearest_neighbour(const vector<point>& points, point pt_query, find_policy policy) {
  using fn_search = std::function<optional<point>(const vector<point>&, point)>;
  static const std::map<find_policy, fn_search> algors = {
    { find_policy::linear_search, nns_linear_search},
    { find_policy::kd_tree, nns_kd_tree_search},
    { find_policy::defaut, nns_kd_tree_search}
  };
  return algors.at(policy)(points, pt_query);
}

vector<point> generate_random_cloud_points(size_t sz) {
  // Seed with a real random value, if available
  std::random_device r;
  // Choose a random mean between 1 and 6
  std::default_random_engine e1(r());
  std::uniform_int_distribution<int> uniform_dist(-1000, 1000);

  int mean = uniform_dist(e1);
  int var = uniform_dist(e1);
  // Generate a normal distribution around that mean
  std::seed_seq seed2{r(), r(), r(), r(), r(), r(), r(), r()};
  std::mt19937 e2(seed2);
  std::normal_distribution<> normal_dist(mean, var);

  vector<point> points;
  points.reserve(sz);
  int cnt = 0;
  while (cnt++ < sz) {
    points.push_back({int(normal_dist(e2)), int(normal_dist(e2))});
  }
  return points;
}


} // namespace nns

TEST(TreeSuite, find_nearest_neighbour) {
  using namespace nns;
  const vector<point> points = {
    {1, 2},
    {5, 8},
    {20, 4},
    {2, 9},
    {100, 40},
    {43, -30},
    {-10, 8}
  };

  for (const auto& p : points) {
    const auto q_linear = find_nearest_neighbour(points, p, find_policy::linear_search);
    ASSERT_TRUE(q_linear.has_value());
    EXPECT_EQ(q_linear.value(), p); // they should be the same

    const auto q_kd_tree = find_nearest_neighbour(points, p, find_policy::kd_tree);
    ASSERT_TRUE(q_kd_tree.has_value());
    EXPECT_EQ(q_kd_tree, q_linear);
  }
}
