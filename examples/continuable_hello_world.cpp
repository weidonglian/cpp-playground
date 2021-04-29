#include <chrono>
#include <continuable/continuable-base.hpp>
#include <continuable/continuable.hpp>
#include <future>
#include <iostream>
#include <thread>
#include <utility>

auto do_one() {
  return cti::make_ready_continuable(0);
}

auto calc_square(float val) {
  return cti::make_continuable<float>([=](auto&& promise) { return promise.set_value(val * val); });
}

int main(int argc, char** argv) {
  std::cout << "main thread id:" << std::this_thread::get_id() << std::endl;
  // make one
  do_one().then([](auto v) { std::cout << "one is resolved with:" << v << std::endl; });
  // make three
  cti::continuable<int, float, char> three = cti::make_ready_continuable(0, 1.f, '2');
  std::move(three).then([](auto v) {});
  // make temp continuable
  cti::make_continuable<int>([](auto&& promise) { promise.set_value(100); }).then([](auto v) {
    std::cout << "promise is resolved with:" << v << std::endl;
  });

  // calc square continuable
  std::cout << "calc_square begin\n";
  calc_square(5.0f).then([](auto result) {
    std::cout << "calc_square is resolved with:" << result << " thread_id:" << std::this_thread::get_id() << std::endl;
  });
  std::cout << "calc_square end\n";
  return 0;
}