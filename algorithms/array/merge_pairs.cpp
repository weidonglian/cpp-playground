#include "base.hpp"

using m_pair = std::pair<int, int>;
using m_vector = std::vector<m_pair>;
m_vector merge_pairs(const m_vector& arr) {
  return {};
}

TEST_CASE("merge_pairs", "[array]") {
  // REQUIRE(merge_pairs({{0, 1}, {1, 2}, {2, 3}}) == m_vector({{0, 3}}));
  // REQUIRE(merge_pairs({{0, 2}, {1, 2}) == m_vector({{0, 1}}));
}