#include <array>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <limits>
#include <map>
#include <memory>
#include <optional>
#include <vector>

#include "base.hpp"
#include "random.hpp"
#include "simple_svg.hpp"

using namespace std;

namespace nns {

struct point {
  static constexpr int kDim = 2;
  array<int, kDim> data;
  point(int x, int y) : data{x, y} {}
  bool operator==(const point& right) const { return data == right.data; }
  bool operator!=(const point& right) const { return data != right.data; }
  int& operator[](size_t index) { return data[index]; }
  const int& operator[](size_t index) const { return data[index]; }
  // Mahatan distance
  int distance(const point& p) const {
    int dist = 0;
    for (int i = 0; i < kDim; ++i)
      dist += abs(data[i] - p.data[i]);
    return dist;
  }
};

struct kd_node {
  point pt;    // the node's point if no children node, i.e. leaf
  kd_node* lo; // left/below, lower
  kd_node* hi; // right/above, higher

  kd_node(const point& p) : pt(p), lo(nullptr), hi(nullptr) {}
};

class kd_tree {
public:
  kd_tree() : root_(nullptr), nodes_() {}

  kd_node* root() { return root_; }

  kd_node* build(vector<point> points) {
    nodes_.clear();
    nodes_.reserve(points.size());
    root_ = kd_fill_recursive(0, points.begin(), points.end());
    return root_;
  }

  kd_node* kd_insert(kd_node* root, point pt, int depth = 0) {
    if (!root) {
      return kd_new(pt);
    }

    const int dim = depth % point::kDim;
    if (pt[dim] < root->pt[dim]) {
      root->lo = kd_insert(root->lo, pt, depth + 1);
    } else {
      root->hi = kd_insert(root->hi, pt, depth + 1);
    }
    return root;
  }

  // Find the node that the given point should be inserted
  const kd_node* kd_find_insert_position(const kd_node* root, point pt, int depth = 0) const {
    if (!root)
      return root;
    const int dim = depth % point::kDim;
    if (pt[dim] < root->pt[dim]) {
      return root->lo ? kd_find_insert_position(root->lo, pt, depth + 1) : root;
    } else {
      return root->hi ? kd_find_insert_position(root->hi, pt, depth + 1) : root;
    }
  }

  optional<point> find_nearest_point(const point& pt_query) const {
    int min_dist = numeric_limits<int>::max();
    const kd_node* best_node = nullptr;
    // Try to guess what is possible min distance
    const kd_node* init_guess = kd_find_insert_position(this->root_, pt_query);
    if (init_guess) {
      min_dist = pt_query.distance(init_guess->pt);
      best_node = init_guess;
    }

    const kd_node* nearest = kd_find_nearest(root_, pt_query, min_dist);
    if (nearest) {
      min_dist = pt_query.distance(nearest->pt);
      best_node = nearest;
    }

    if (best_node) {
      return make_optional(best_node->pt);
    }
    return nullopt;
  }

private:
  kd_node* kd_new(point pt) { return &nodes_.emplace_back(pt); }
  kd_node* kd_fill_recursive(int depth, vector<point>::iterator first, vector<point>::iterator last) {
    const int dim = depth % point::kDim;
    kd_node* root = nullptr;
    if (first != last) {
      sort(first, last, [dim](const point& p1, const point& p2) { return p1[dim] < p2[dim]; });
      auto mid = first + distance(first, last) / 2;
      root = kd_new(*mid);
      root->lo = kd_fill_recursive(depth + 1, first, mid);
      root->hi = kd_fill_recursive(depth + 1, next(mid), last);
    }
    return root;
  }

  // Find the nearest neightbour with condtion <= min_dist, otherwise return nullptr
  const kd_node* kd_find_nearest(const kd_node* root, const point& pt_query, int min_dist, int depth = 0) const {
    // Current node is empty, then return it.
    if (!root)
      return nullptr;

    const kd_node* best = nullptr;
    // Current node to update the min_dist
    {
      const int dst = pt_query.distance(root->pt);
      if (dst < min_dist) {
        min_dist = dst;
        best = root;
      }
    }

    // determine which branch to search
    const int dim = depth % point::kDim;
    // distance in the corresponding dimension
    const int signed_dst = pt_query[dim] - root->pt[dim]; // signed distance
    bool should_search_lo = false;
    bool should_search_hi = false;
    if (signed_dst < -min_dist) {
      // the query point on the far left side of the dim axis. search the lo
      // branch
      should_search_lo = true;
    } else if (signed_dst > min_dist) {
      // the query point on the far right side of the dim axis. search only
      // the hi branch
      should_search_hi = true;
    } else {
      // Too close the boundary, We need to search two branches, lo and hi.
      should_search_lo = true;
      should_search_hi = true;
    }

    if (should_search_lo && root->lo) {
      const kd_node* best_lo = kd_find_nearest(root->lo, pt_query, min_dist, depth + 1);
      if (best_lo) { // exist must be smaller
        assert(pt_query.distance(best_lo->pt) < min_dist);
        min_dist = pt_query.distance(best_lo->pt);
        best = best_lo;
      }
    }

    if (should_search_hi && root->hi) {
      const kd_node* best_hi = kd_find_nearest(root->hi, pt_query, min_dist, depth + 1);
      if (best_hi) {
        assert(pt_query.distance(best_hi->pt) < min_dist);
        min_dist = pt_query.distance(best_hi->pt);
        best = best_hi;
      }
    }
    // both lo and hi branches do not find anything, then return root.
    return best;
  }

  kd_node* root_;
  std::vector<kd_node> nodes_;
};

struct qd_node {};

struct qd_leaf {};

class qd_tree {};

optional<point> nns_kd_tree_search(const vector<point>& points, const point& pt_query) {
  kd_tree tree;
  tree.build(points);
  return tree.find_nearest_point(pt_query);
}

optional<point> nns_linear_search(const vector<point>& points, const point& pt_query) {
  optional<point> result;
  int min_dst = numeric_limits<int>::max();
  const int sz_total = static_cast<int>(points.size());
  for (int idx = 0; idx < sz_total; ++idx) {
    const int dst = points[idx].distance(pt_query);
    if (dst < min_dst) {
      result = points[idx];
      min_dst = dst;
    }
  }
  return result;
}

enum class find_policy { defaut, linear_search, kd_tree };

optional<point> find_nearest_neighbour(const vector<point>& points, point pt_query, find_policy policy) {
  using fn_search = std::function<optional<point>(const vector<point>&, point)>;
  static const std::map<find_policy, fn_search> algors = {{find_policy::linear_search, nns_linear_search},
                                                          {find_policy::kd_tree, nns_kd_tree_search},
                                                          {find_policy::defaut, nns_kd_tree_search}};
  return algors.at(policy)(points, pt_query);
}

} // namespace nns

namespace details {

using namespace nns;

vector<point> generate_random_cloud_points(size_t n) {
  vector<point> points;
  points.reserve(n);
  std::srand(static_cast<unsigned int>(time(nullptr)));
  std::generate(points.begin(), points.end(), []() -> point { return {std::rand() % 1000, std::rand() % 1000}; });
  return points;
}

void dump_svg(const string& file_name, const vector<point>& points, point test, point q_linear, point q_kd_tree) {
  using namespace svg;
  Dimensions dimensions(-1000, 1000);
  Document doc(file_name, Layout(dimensions, Layout::BottomLeft));

  // Red image border.
  // Polygon border(Stroke(1, Color::Red));
  // border << Point(0, 0) << Point(dimensions.width, 0)
  //       << Point(dimensions.width, dimensions.height)
  //       << Point(0, dimensions.height);
  // doc << border;

  for (const auto& p : points) {
    doc << Circle(Point(p[0], p[1]), 8, Fill(Color(0, 255, 0)), Stroke(1, Color(0, 255, 0)));
  }

  doc << Circle(Point(test[0], test[1]), 16, Fill(Color(0, 0, 255)), Stroke(1, Color(0, 0, 200)));

  doc << Circle(Point(q_linear[0], q_linear[1]), 20, Fill(Color(125, 0, 0)), Stroke(2, Color(0, 0, 0)));

  doc << Circle(Point(q_kd_tree[0], q_kd_tree[1]), 20, Fill(Color(255, 0, 0)), Stroke(2, Color(0, 0, 0)));

  doc.save();
}
} // namespace details

TEST_CASE("find_nns_query_point_in_cluster", "[tree]") {
  using namespace nns;
  const vector<point> fixed_points = {{1, 2}, {5, 8}, {20, 4}, {2, 9}, {100, 40}, {43, -30}, {-10, 8}};

  for (const auto& p : fixed_points) {
    const auto q_linear = find_nearest_neighbour(fixed_points, p, find_policy::linear_search);
    REQUIRE(q_linear.has_value());
    CHECK(q_linear.value() == p); // they should be the same

    const auto q_kd_tree = find_nearest_neighbour(fixed_points, p, find_policy::kd_tree);
    REQUIRE(q_kd_tree.has_value());
    CHECK(q_kd_tree == q_linear); // find the existing point in cluster
  }
}

TEST_CASE("find_nns_query_point_in_cluster_random", "[tree]") {
  using namespace nns;
  const vector<point> cluster_points = details::generate_random_cloud_points(1000);
  int cnt = 0;
  kd_tree tree;
  tree.build(cluster_points);
  for (const auto& p : cluster_points) {
    const auto q_linear = find_nearest_neighbour(cluster_points, p, find_policy::linear_search);
    REQUIRE(q_linear.has_value());
    CHECK(q_linear.value() == p); // they should be the same

    const auto q_kd_tree = tree.find_nearest_point(p);
    REQUIRE(q_kd_tree.has_value());
    // find existing point in cluster
    INFO("with p=[" << p[0] << ", " << p[1] << "]");
    CHECK(q_kd_tree.value() == q_linear.value());
    if (q_kd_tree.value() != q_linear.value()) {
      details::dump_svg("find_nearest_neighbour_random" + to_string(cnt++) + ".svg", cluster_points, p,
                        q_linear.value(), q_kd_tree.value());
    }
  }
}

TEST_CASE("find_nns_query_not_necessarily_from_cluster", "[tree]") {
  using namespace nns;
  const vector<point> points = details::generate_random_cloud_points(1000);
  const vector<point> points_to_test = details::generate_random_cloud_points(1000);
  int cnt = 0;
  kd_tree tree;
  tree.build(points);
  for (const auto& p : points_to_test) {
    const auto q_linear = find_nearest_neighbour(points, p, find_policy::linear_search);
    REQUIRE(q_linear.has_value());

    const auto q_kd_tree = tree.find_nearest_point(p);
    REQUIRE(q_kd_tree.has_value());
    const int min_dist_linear = q_linear.value().distance(p);
    const int min_dist_kd_tree = q_kd_tree.value().distance(p);
    CHECK(min_dist_linear == min_dist_kd_tree);
    if (min_dist_kd_tree != min_dist_linear) {
      details::dump_svg("find_nearest_neighbour_random_point_" + to_string(cnt++) + ".svg", points, p, q_linear.value(),
                        q_kd_tree.value());
    }
  }
}
