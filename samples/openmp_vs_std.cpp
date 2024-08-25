#include <chrono>
#include <cmath>
#include <execution>
#include <functional>
#include <iostream>
#include <vector>
#include <string>

namespace {
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

#define C_PI 3.14159265358979323846

void fill_array(std::vector<double>& arr) {
  const int total = static_cast<int>(arr.size());
  for (int i = 0; i < total; ++i)
    arr[i] = std::sin(2 * C_PI * i / total);
}

void fill_array_openmp(std::vector<double>& arr) {
  const int total = static_cast<int>(arr.size());
#pragma omp parallel for
  for (int i = 0; i < total; ++i)
    arr[i] = std::sin(2 * C_PI * i / total);
}

void fill_array_std_par(std::vector<double>& arr) {
  const int total = static_cast<int>(arr.size());
  std::for_each(std::execution::par, arr.begin(), arr.end(), [&](auto& v) {
    const int i = static_cast<int>(&v - &arr[0]);
    v = std::sin(2 * C_PI * i / total);
  });
}

} // namespace

int main(int argc, char** argv) {
  const auto k_scales = {1000, 10000, 100000, 1000000};
  for (auto sz : k_scales) {
    std::cout << "profiling N=" << sz << std::endl;
    std::vector<double> arr(sz, 0);
    struct algor {
      std::string name;
      std::function<void(std::vector<double>&)> fn_call;
    };
    using algor_list = std::vector<algor>;
    for (const auto& alg : algor_list{{"fill_array", fill_array},
                                      {"fill_array_openmp", fill_array_openmp},
                                      {"fill_array_std_par", fill_array_std_par}}) {
      cpu_timer scope_timer(alg.name);
      alg.fn_call(arr);
    }
  }
  return 0;
}