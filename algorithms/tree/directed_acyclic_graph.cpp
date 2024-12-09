#include <cstdlib>
#include <queue>

#include "absl/container/inlined_vector.h"
#include "base.hpp"

namespace {

template <typename T>
struct node {
  T val;      // node value
  int degree; // number of edges connected to parent node
  absl::InlinedVector<T, 8> children; // children nodes
};

template <typename T>
class graph {
public:
  graph() : nodes() {}

  void add_node(const T& val) {
    if (!nodes.contains(val)) {
      auto& n = nodes[val];
      n.val = val;
      n.degree = 0;
    }
  }

  void add_edge(const T& from, const T& to) {
    add_node(from);
    add_node(to);
    nodes[from].children.push_back(to);
    nodes[to].degree++;
  }

  // Topological sort returns nodes in order of their level.
  // Throws an exception if the graph has a cycle.
  // Otherwise, returns nodes in topological order.
  // Nodes are sorted by value per level for deterministic results.
  std::vector<T> topological_sort() const {
    std::vector<T> result;
    std::map<T, int> current_degrees;
    std::queue<T> queue;
    // Group nodes by their level
    for (const auto& [val, n] : nodes) {
      current_degrees[val] = n.degree;
      if (n.degree == 0) {
        queue.push(val);
      }
    }

    absl::InlinedVector<T, 8> sorted_children;
    while (!queue.empty()) {
      auto val = queue.front();
      queue.pop();
      result.push_back(val);

      sorted_children.clear();
      for (const auto& adj : nodes.at(val).children) {
        if (--current_degrees[adj] == 0) {
          sorted_children.push_back(adj);
        }
      }
      std::sort(sorted_children.begin(), sorted_children.end());
      for (const auto& adj : sorted_children) {
        queue.push(adj);
      }
    }

    if (result.size() != nodes.size()) {
      throw std::runtime_error("graph has cycle.");
    }

    return result;
  }

private:
  std::map<T, node<T>> nodes;
};

} // namespace

TEST_CASE("dag_has_cycle", "[tree]") {
  graph<int> g;
  g.add_edge(1, 2);
  g.add_edge(2, 3);
  g.add_edge(3, 4);
  g.add_edge(4, 1);
  CHECK_THROWS(g.topological_sort());
}

TEST_CASE("dag_topological_sort", "[tree]") {
  graph<int> g;
  g.add_edge(1, 2);
  g.add_edge(2, 3);
  g.add_edge(3, 4);
  g.add_node(5); // isolated node
  g.add_edge(7, 6);
  REQUIRE(g.topological_sort() == std::vector<int>({1, 5, 7, 2, 6, 3, 4}));
}

TEST_CASE("dag_topological_sort_single_node", "[tree]") {
  graph<int> g;
  g.add_node(5); // isolated node
  REQUIRE(g.topological_sort() == std::vector<int>({5}));
}