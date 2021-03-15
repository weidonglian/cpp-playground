#include <cstdlib>

#include "base.hpp"

double calc_power(double x, int n) {
  if (n == 0) {
    return 1;
  }
  if (n == 1) {
    return x;
  }
  if (x == 0) {
    return 0;
  }
  const bool is_negative = n < 0;
  const double main = calc_power(x, n / 2);
  double result = main * main * (n % 2 == 1 ? x : 1.0);
  return is_negative ? 1 / result : result;
}

double gen_random_double(double fmin, double fmax) {
  return fmin + (fmax - fmin) * (std::rand() / RAND_MAX);
}

/**
 * @brief Calculate the value of x powers n.
 *
 * Solution: we could perform x*x n times. Then the complexity will be O(N).
 * An optiomal one should done by n divide by 2 recursively then we will gain
 * the optimal complexity with O(Log(N)).
 *
 */
TEST_CASE("x_power_y", "[math]") {
  REQUIRE(calc_power(0, 2) == 0);
  REQUIRE(calc_power(2, 0) == 1);
  REQUIRE(calc_power(1, 2) == 1);
  REQUIRE(calc_power(2, 2) == 4);
  REQUIRE(calc_power(2, 5) == 32);
  int k_test_cnt = 1000;
  while (k_test_cnt-- > 0) {
    const int y = std::rand() % 100;
    const double x = gen_random_double(0, 1000000);
    INFO("x and y:" + std::to_string(x) + ", " << std::to_string(y));
    REQUIRE(calc_power(x, y) == std::pow(x, y));
  }
}