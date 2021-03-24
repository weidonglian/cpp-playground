#include <algorithm>
#include <cstdlib>
#include <vector>

#include "base.hpp"

struct dg_node {
  dg_node(int value) : value_(value), neighbours() {}

  int value_;
  // we do not own them, they are created in higher level and
  // should not be deleted when the current dg_node is destructed.
  std::vector<dg_node*> neighbours;
};

struct dg_edge {
  int from;
  int to;
};

class dg_tree {
public:
  dg_tree() : nodes(), edges() {}

private:
  std::vector<dg_node> nodes;
  std::vector<dg_edge> edges;
};

TEST_CASE("directed_graph", "[tree]") {