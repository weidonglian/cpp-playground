#include <iterator>

#include "base.hpp"

namespace {
struct point {
  int x;
  int y;

  bool operator==(const point& right) const { return x == right.x && y == right.y; }
  friend std::ostream& operator<<(std::ostream& osm, const point& p) {
    osm << "(" << p.x << ", " << p.y << ")";
    return osm;
  }
};

using point_list = std::vector<point>;

// points should have already been sorted in y direction.
point_list sort_xy(const point_list& points, point target) {
  point_list r = points;
  std::sort(r.begin(), r.end(), [&](const point& p1, const point& p2) {
    if ((p1.x <= target.x && p2.x > target.x) || (p1.x > target.x && p2.x <= target.x)) { // keep y sorted
      return p1.x < p2.x;
    } else {
      return p1.y < p2.y;
    }
  });
  return r;
}
} // namespace

template <class T>
inline std::ostream& operator<<(std::ostream& osm, const std::vector<T>& arr) {
  std::cout << "[";
  if (!arr.empty()) {
    std::copy(arr.begin(), std::prev(arr.end()), std::ostream_iterator<T>(osm, ", "));
    osm << *arr.rbegin();
  }
  std::cout << "]";
  return osm;
}

TEST_CASE("sort_two_directions", "[sort]") {
  point_list input({{2, 1}, {3, 2}, {5, 4}, {3, 6}, {4, 7}, {2, 9}});
  auto output = sort_xy(input, point{2, 9});
  point_list expected({{2, 1}, {2, 9}, {3, 2}, {5, 4}, {3, 6}, {4, 7}});
  std::cout << "output:" << output << std::endl;
  REQUIRE(output == expected);
}