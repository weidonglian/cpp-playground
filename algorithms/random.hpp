#pragma once

#include <random>
#include <vector>

inline std::vector<int> generate_random_number(size_t sz) {
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
  std::normal_distribution<> normal_dist(mean, std::abs(var));

  std::vector<int> points;
  points.reserve(sz);
  size_t cnt = 0;
  while (cnt++ < sz)
    points.push_back((int)normal_dist(e2));
  return points;
}