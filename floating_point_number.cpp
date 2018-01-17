#include <array>
#include <iomanip>
#include <iostream>

int main() {
  // Notice that what ever double or float, the 0.0, 0.25, 0.5, 1.0 can keep
  // the exact precision without losing any precision, but neither can
  // other values.
  std::array<float, 9> fa{ 0.0f, 0.1f, 0.2f, 0.3f, 0.25f, 0.4f, 0.5f, 1.0f, 23.4f };
  std::cout << "Float:" << std::endl;
  for (const auto& a : fa) {
    std::cout << std::fixed << std::setprecision(20) << a << std::endl;
  }

  std::cout << "Double:" << std::endl;
  std::array<double, 9> da{ 0.0, 0.1, 0.2, 0.3, 0.25, 0.4, 0.5, 1.0, 23.4 };
  for (const auto& a : fa) {
    std::cout << std::fixed << std::setprecision(20) << a << std::endl;
  }
}