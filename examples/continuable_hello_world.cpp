#include <continuable/continuable.hpp>

int main(int argc, char** argv) {
  auto one = cti::make_ready_continuable(0);

  cti::continuable<int, float, char> three = cti::make_ready_continuable(0, 1.f, '2');
  return 0;
}