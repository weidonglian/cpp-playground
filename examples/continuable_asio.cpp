#include <asio.hpp>
#include <chrono>
#include <continuable/continuable-base.hpp>
#include <continuable/continuable.hpp>
#include <future>
#include <iostream>
#include <thread>
#include <utility>

#include "asio/execution_context.hpp"
#include "asio/post.hpp"
#include "asio/thread_pool.hpp"

auto calc_square_async(float val, asio::thread_pool* pool) {
  return cti::make_continuable<float>([=](auto&& promise) {
    asio::post(*pool, [val, promise = std::forward<decltype(promise)>(promise)]() mutable {
      std::cout << "start async resolver\n";
      std::this_thread::sleep_for(std::chrono::seconds(5));
      if (val < 0) {
        promise.set_exception(std::make_error_condition(std::errc::invalid_argument));
      } else {
        promise.set_value(val * val);
      }
      std::cout << "end async resolver\n";
    });
  });
}

auto calc_square(float val) {
  return cti::make_continuable<float>([=](auto&& promise) { return promise.set_value(val * val); });
}

int main(int argc, char** argv) {
  asio::thread_pool pool(2);

  std::cout << "main thread id:" << std::this_thread::get_id() << std::endl;
  // calc square continuable
  std::cout << "calc_square begin\n";
  calc_square(5.0f).then([](auto result) {
    std::cout << "calc_square is resolved with:" << result << " thread_id:" << std::this_thread::get_id() << std::endl;
  });
  std::cout << "calc_square end\n";

  // calc square async continuable
  std::cout << "calc_square_async begin\n";
  calc_square_async(5.0f, &pool).then([](auto result) {
    std::cout << "calc_square is resolved with:" << result << " thread_id:" << std::this_thread::get_id() << std::endl;
  });
  std::cout << "calc_square_async end\n";

  // calc square async continuable with failure
  std::cout << "calc_square_async fail begin\n";
  calc_square_async(-5.0f, &pool)
    .then([](float result) {
      std::cout << "calc_square async fail is resolved with:" << result << " thread_id:" << std::this_thread::get_id()
                << std::endl;
    })
    .fail([](cti::exception_t e) {
      std::cout << "calc_square async fail is rejected with:" << e.value() << "," << e.message()
                << " thread_id:" << std::this_thread::get_id() << std::endl;
    });
  std::cout << "calc_square_async fail end\n";

  pool.join();
  return 0;
}