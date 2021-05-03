#include <absl/status/status.h>
#include <absl/strings/str_format.h>

#include <asio.hpp>
#include <asio/execution_context.hpp>
#include <asio/post.hpp>
#include <asio/thread_pool.hpp>
#include <chrono>
#include <continuable/continuable-base.hpp>
#include <continuable/continuable.hpp>
#include <continuable/external/asio.hpp>
#include <future>
#include <iostream>
#include <thread>
#include <utility>

auto calc_square_async(float val, asio::thread_pool* pool) {
  return cti::make_continuable<float>([=](auto&& promise) {
    asio::post(*pool, [val, promise = std::forward<decltype(promise)>(promise)]() mutable {
      std::cout << "start async resolver\n";
      if (val < 0) {
        promise.set_exception(
          absl::InvalidArgumentError(absl::StrFormat("Input argument:%f should be a positive float number", val)));
      } else {
        std::this_thread::sleep_for(std::chrono::seconds(5));
        promise.set_value(val * val);
      }
      std::cout << "end async resolver\n";
    });
  });
}

auto calc_offset_async(int val, int offset, asio::thread_pool* pool) {
  return cti::make_continuable<int>([=](auto&& promise) {
    asio::post(*pool, [val, offset, promise = std::forward<decltype(promise)>(promise)]() mutable {
      std::cout << "calc offset async begin...";
      if (offset < 0) {
        promise.set_exception(
          absl::InvalidArgumentError(absl::StrFormat("Input offset argument:%f should be a positive number", offset)));
      } else {
        promise.set_value(val + offset);
      }
      std::cout << "calc offset async end...";
    });
  });
}

using asio::ip::tcp;

struct tcp_socket_context {
  tcp::resolver resolver;
  tcp::socket socket;
  std::string buf;

  tcp_socket_context(asio::io_context* ioc) : resolver(*ioc), socket(*ioc), buf() {}
};

void unexpected_error(cti::exception_t e) {
  if (!e.ok()) {
    puts("Continuation failed with unexpected cancellation!");
    std::terminate();
  }
}

auto http_request_daytime_async(asio::io_context* ioc) {

  auto ctx = std::make_shared<tcp_socket_context>(ioc);

  ctx->resolver.async_resolve("time.nist.gov", "daytime", cti::use_continuable)
    .then([ctx](tcp::resolver::results_type endpoints) {
      return asio::async_connect(ctx->socket, endpoints, cti::use_continuable);
    })
    .then(
      [ctx] { return asio::async_read_until(ctx->socket, asio::dynamic_buffer(ctx->buf), '\n', cti::use_continuable); })
    .then([ctx](std::size_t) {
      puts("Continuation successfully got a daytime response:");
      puts(ctx->buf.c_str());
    })
    .fail(&unexpected_error);
}

auto calc_square(float val) {
  return cti::make_continuable<float>([=](auto&& promise) { return promise.set_value(val * val); });
}

int main(int argc, char** argv) {
  asio::thread_pool pool(3);

  std::cout << "main thread id:" << std::this_thread::get_id() << std::endl;
  // calc square continuable
  std::cout << "calc_square begin\n";
  calc_square(5.0f).then([](auto result) {
    std::cout << "calc_square is resolved with:" << result << " thread_id:" << std::this_thread::get_id() << std::endl;
  });
  std::cout << "calc_square end\n";

  // calc square async continuable
  std::cout << "calc_square_async begin\n";
  calc_square_async(5.25f, &pool)
    .then([](auto result) {
      std::cout << "calc_square is resolved with:" << result << " thread_id:" << std::this_thread::get_id()
                << std::endl;
      return static_cast<int>(result);
    })
    .then([](int abs_val) {
      std::cout << "calc_square is resolved with abs:" << abs_val << " thread_id:" << std::this_thread::get_id()
                << std::endl;
      return abs_val;
    })
    .then([&pool](int val) { return calc_offset_async(val, 10, &pool); });

  std::cout << "calc_square_async end\n";

  // calc square async continuable with failure
  std::cout << "calc_square_async failure begin\n";
  calc_square_async(-5.5f, &pool)
    .then([](float result) {
      std::cout << "calc_square async failure is resolved with:" << result
                << " thread_id:" << std::this_thread::get_id() << std::endl;
    })
    .fail([](cti::exception_t status) {
      std::cout << "calc_square async failure is rejected with:" << status.ToString()
                << " thread_id:" << std::this_thread::get_id() << std::endl;
    });
  std::cout << "calc_square_async failure end\n";

  pool.join();
  return 0;
}