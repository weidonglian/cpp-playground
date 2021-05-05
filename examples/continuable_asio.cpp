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

#include "logger.hpp"

absl::Status make_asio_exception(asio::error_code e) {
  return absl::InternalError(e.message());
}

cti::continuable<int> calc_recursive_async(int val, asio::static_thread_pool* pool) {
  return cti::make_continuable<int>([=](auto&& promise) {
           LOGI("calc_recursive_async's promise thread_id:%s", ToString(std::this_thread::get_id()));
           asio::post(*pool, [val, promise = std::forward<decltype(promise)>(promise)]() mutable {
             LOGI("start recursive async resolver with:%d", val);
             if (val < 0) {
               promise.set_exception(absl::InvalidArgumentError(
                 absl::StrFormat("Input argument:%f should be a positive float number", val)));
             } else {
               std::this_thread::sleep_for(std::chrono::seconds(1));
               promise.set_value(val / 2);
             }
             LOGI("end recursive async resolver");
           });
         })
    .then([pool](int val) -> cti::continuable<int> {
      if (val == 1) {
        return cti::make_ready_continuable(val);
      }

      if (val > 0) {
        return calc_recursive_async(val, pool);
      }

      return cti::make_cancelling_continuable<int>();
    });
}

auto calc_square_async(float val, asio::thread_pool* pool) {
  return cti::make_continuable<float>([=](auto&& promise) {
    asio::post(*pool, [val, promise = std::forward<decltype(promise)>(promise)]() mutable {
      LOGI("start async resolver");
      if (val < 0) {
        promise.set_exception(
          absl::InvalidArgumentError(absl::StrFormat("Input argument:%f should be a positive float number", val)));
      } else {
        std::this_thread::sleep_for(std::chrono::seconds(5));
        promise.set_value(val * val);
      }
      LOGI("end async resolver");
    });
  });
}

auto calc_offset_async(int val, int offset, asio::thread_pool* pool) {
  return cti::make_continuable<int>([=](auto&& promise) {
    asio::post(*pool, [val, offset, promise = std::forward<decltype(promise)>(promise)]() mutable {
      LOGI("calc offset async begin...");
      if (offset < 0) {
        promise.set_exception(
          absl::InvalidArgumentError(absl::StrFormat("Input offset argument:%f should be a positive number", offset)));
      } else {
        promise.set_value(val + offset);
      }
      LOGI("calc offset async end...");
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

auto http_request_daytime_async(asio::io_context* ioc, const std::string& host, const std::string& service) {

  auto ctx = std::make_shared<tcp_socket_context>(ioc);

  return ctx->resolver.async_resolve(host, service, cti::use_continuable)
    .then([ctx](tcp::resolver::results_type endpoints) {
      return asio::async_connect(ctx->socket, endpoints, cti::use_continuable);
    })
    .then(
      [ctx] { return asio::async_read_until(ctx->socket, asio::dynamic_buffer(ctx->buf), '\n', cti::use_continuable); })
    .then([ctx](std::size_t) { LOGI("Continuation successfully got a daytime response:%s", ctx->buf); });
}

auto calc_square(float val) {
  return cti::make_continuable<float>([=](auto&& promise) { return promise.set_value(val * val); });
}

int main(int argc, char** argv) {
  asio::thread_pool pool(3);

  LOGI("main thread id:%s", ToString(std::this_thread::get_id()));
  // calc square continuable
  LOGI("calc_square begin");
  calc_square(5.0f).then([](auto result) {
    LOGI("calc_square is resolved with:%f with thread_id:%s", result, ToString(std::this_thread::get_id()));
  });
  LOGI( "calc_square end");

  // calc square async continuable
  LOGI( "calc_square_async begin");
  calc_square_async(5.25f, &pool)
    .then([](auto result) {
      LOGI("calc_square is resolved with:%f thread_id:%s", result, ToString(std::this_thread::get_id()));
      return static_cast<int>(result);
    })
    .then([](int abs_val) {
      LOGI("calc_square is resolved with abs:%d with thread_id:%s", abs_val, ToString(std::this_thread::get_id()));
      return abs_val;
    })
    .then([&pool](int val) {
    return calc_offset_async(val, 10, &pool); });

  LOGI("calc_square_async end");

  // calc square async continuable with failure
  LOGI( "calc_square_async failure begin");
  calc_square_async(-5.5f, &pool)
    .then([](float result) {
      LOGI("calc_square async failure is resolved with: %f", result);
    })
    .fail([](cti::exception_t status) {
      LOGI("calc_square async failure is rejected with:%s", status.ToString());
    });
  LOGI( "calc_square_async failure end");

  // calc divide by 2
  // calc square async continuable with failure
  LOGI( "calc_recursive_async ");
  calc_recursive_async(20, &pool)
    .then([](int result) { LOGI("==calc_recursive_async is resolved with:%d", result);
    })
    .fail([](cti::exception_t status) {
      LOGI("## calc_recursive_async is rejected with:%s", status.ToString());
    });
  LOGI( "calc_recursive_async end");

  // test the http request via asio socket
  asio::io_context ioc{};
  http_request_daytime_async(&ioc, "time.nist.gov", "daytime")
    .then([] {
    LOGI("==http_request_daytime_async has done now"); })
    .fail([](cti::exception_t e) {
    if (!e.ok()) {
        LOGI("Continuation failed with unexpected cancellation:%s", e.message());
    }
    });

  http_request_daytime_async(&ioc, "xxxx.nist.gov", "daytime")
    .then([] {
    LOGI("==http_request_daytime_async has done now"); })
    .fail([](cti::exception_t e) {
    if (!e.ok()) {
        LOGI("Continuation failed with unexpected cancellation:%s", e.message());
    }
    });
  // run it inside the pool until all jobs are done in ioc
  asio::post(pool, [&] {
    ioc.run(); });

  pool.join();
  return 0;
}