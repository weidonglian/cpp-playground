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

// This is not a realy async handling
// If the std::future obtained from std::async is not moved from or bound to a reference,
// the destructor of the std::future will block at the end of the full expression until
// the asynchronous operation completes.
// A real async example should look at continuable_asio.cpp
auto calc_square_async(float val) {
  return cti::make_continuable<float>([=](auto&& promise) {
    std::async(std::launch::async, [val, promise = std::forward<decltype(promise)>(promise)]() mutable {
      std::cout << "start async resolver\n";
      std::this_thread::sleep_for(std::chrono::seconds(5));
      promise.set_value(val * val);
      std::cout << "end async resolver\n";
    });
  });
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

  // calc square async continuable
  std::cout << "calc_square_async begin\n";
  calc_square_async(5.0f).then([](auto result) {
    std::cout << "calc_square is resolved with:" << result << " thread_id:" << std::this_thread::get_id() << std::endl;
  });
  std::cout << "calc_square_async end\n";
  return 0;
}