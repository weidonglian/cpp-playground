#pragma once

#include <chrono>
#include <iostream>
#include <string>

#include "catch2/catch.hpp"
#include "random.hpp"

class cpu_timer {
public:
  cpu_timer(std::string description)
  : description(std::move(description)), start(std::chrono::high_resolution_clock::now()) {}
  ~cpu_timer() {
    auto duration = std::chrono::high_resolution_clock::now() - start;
    std::cout << description << " takes: " << std::chrono::duration_cast<std::chrono::milliseconds>(duration).count()
              << " ms" << std::endl;
  }

private:
  std::string description;
  std::chrono::high_resolution_clock::time_point start;
};