#include <absl/strings/str_format.h>

#include <asio.hpp>
#include <asio/post.hpp>
#include <asio/thread_pool.hpp>
#include <chrono>
#include <continuable/continuable-base.hpp>
#include <continuable/continuable.hpp>
#include <continuable/external/asio.hpp>
#include <exception>
#include <function2/function2.hpp>
#include <iostream>
#include <thread>
#include <utility>

#include "logger.hpp"

using on_complete_t = fu2::unique_function<void(cti::exception_t)>;

struct next_handler {
  on_complete_t on_complete;
  explicit next_handler(on_complete_t cb) : on_complete(std::move(cb)) {}
  auto operator()() {
    on_complete(nullptr);
    return 1;
  }
  auto operator()(cti::exception_arg_t, const std::exception_ptr& e) {
    on_complete(e);
    return cti::rethrow(e);
  }
};

cti::continuable<int> calc_recursive_async(int val, asio::static_thread_pool* pool) {
  return cti::make_continuable<int>([=](auto&& promise) {
           LOGI("calc_recursive_async's promise thread_id:%s", ToString(std::this_thread::get_id()));
           asio::post(*pool, [val, promise = std::forward<decltype(promise)>(promise)]() mutable {
             LOGI("start recursive async resolver with:%d", val);
             if (val < 0) {
               promise.set_exception(
                 std::make_exception_ptr(std::invalid_argument("Input argument should be a positive number")));
             } else {
               std::this_thread::sleep_for(std::chrono::milliseconds (10));
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
          std::make_exception_ptr(std::invalid_argument("Input argument should be a positive number")));
      } else {
        std::this_thread::sleep_for(std::chrono::milliseconds (5));
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
          std::make_exception_ptr(std::invalid_argument("Input offset argument should be a positive number")));
      } else {
        promise.set_value(val + offset);
      }
      LOGI("calc offset async end...");
    });
  });
}

auto test_next_handler_async(int val) {
  return cti::make_continuable<int>([=](auto&& promise) {
           if (val > 0) {
             promise.set_value(val);
           } else {
             promise.set_exception(
               std::make_exception_ptr(std::invalid_argument("Input argument should be a positive number")));
           }
         })
    .next(next_handler{[](const cti::exception_t& e) {
      try {
        if (e) {
          std::rethrow_exception(e);
        }
        LOGI("next_handler's common lambda is calling with no exception");
      } catch (const std::exception& e) {
        LOGI("next_handler's common lambda caught exception: %s", e.what());
      }
    }});
}

cti::continuable<> test_ready_continuable() {
  return cti::make_ready_continuable<>();
}

cti::continuable<> test_ready_continuable_void() {
  return cti::make_continuable<void>([](auto&& promise) { promise.set_value(); });
}

cti::continuable<> continuable_a() {
  LOGI("enter:continuable_a");
  return cti::make_continuable<void>([](auto&& promise) {
    LOGI("resolve:continuable_a");
    promise.set_value();
  });
  LOGI("leave:continuable_a");
}

cti::continuable<> continuable_b() {
  LOGI("enter:continuable_b");
  return cti::make_continuable<void>([](auto&& promise) {
    LOGI("resolve:continuable_b");
    promise.set_value();
  });
  LOGI("leave:continuable_b");
}

using asio::ip::tcp;

struct tcp_socket_context {
  tcp::resolver resolver;
  tcp::socket socket;
  std::string buf;

  explicit tcp_socket_context(asio::io_context* ioc) : resolver(*ioc), socket(*ioc), buf() {}
};

auto http_request_daytime_async(asio::io_context* ioc, const std::string& host, const std::string& service) {

  auto ctx = std::make_shared<tcp_socket_context>(ioc);

  return ctx->resolver.async_resolve(host, service, cti::use_continuable)
    .then([ctx](const tcp::resolver::results_type& endpoints) {
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
  LOGI("calc_square end");

  // calc square async continuable
  LOGI("calc_square_async begin");
  calc_square_async(5.25f, &pool)
    .then([](auto result) {
      LOGI("calc_square is resolved with:%f thread_id:%s", result, ToString(std::this_thread::get_id()));
      return static_cast<int>(result);
    })
    .then([](int abs_val) {
      LOGI("calc_square is resolved with abs:%d with thread_id:%s", abs_val, ToString(std::this_thread::get_id()));
      return abs_val;
    })
    .then([&pool](int val) { return calc_offset_async(val, 10, &pool); });

  LOGI("calc_square_async end");

  // calc square async continuable with failure
  LOGI("calc_square_async failure begin");
  calc_square_async(-5.5f, &pool)
    .then([](float result) { LOGI("calc_square async failure is resolved with: %f", result); })
    .fail([](const cti::exception_t& e) {
      try {
        if (e) {
          std::rethrow_exception(e);
        }
      } catch (const std::exception& e) {
        LOGI("calc_square async failure is rejected with:%s", e.what());
      }
    });
  LOGI("calc_square_async failure end");

  // calc divide by 2
  // calc square async continuable with failure
  LOGI("calc_recursive_async ");
  calc_recursive_async(20, &pool)
    .then([](int result) { LOGI("==calc_recursive_async is resolved with:%d", result); })
    .fail([](const cti::exception_t& e) {
      try {
        if (e) {
          std::rethrow_exception(e);
        }
      } catch (const std::exception& e) {
        LOGI("## calc_recursive_async is rejected with:%s", e.what());
      }
    });
  LOGI("calc_recursive_async end");

  // test the http request via asio socket
  asio::io_context ioc{};
  http_request_daytime_async(&ioc, "time.nist.gov", "daytime")
    .then([] { LOGI("==http_request_daytime_async has done now"); })
    .fail([](const cti::exception_t& eptr) {
      try {
        if (eptr) {
          std::rethrow_exception(eptr);
        }
      } catch (const std::exception& e) {
        LOGI("Continuation failed with unexpected cancellation:%s", e.what());
      }
    });

  http_request_daytime_async(&ioc, "xxxx.nist.gov", "daytime")
    .then([] { LOGI("==http_request_daytime_async has done now"); })
    .fail([](const cti::exception_t& eptr) {
      try {
        if (eptr) {
          std::rethrow_exception(eptr);
        }
      } catch (const std::exception& e) {
        LOGI("Continuation failed with unexpected cancellation:%s", e.what());
      }
    });
  // run it inside the pool until all jobs are done in ioc
  asio::post(pool, [&] { ioc.run(); });

  // test next handler
  test_next_handler_async(10)
    .then([](int v) { LOGI("==test_next_handler_async resolved:%d", v); })
    .fail([](const cti::exception_t& eptr) {
      try {
        if (eptr) {
          std::rethrow_exception(eptr);
        }
      } catch (const std::exception& e) {
        LOGI("Continuation failed with unexpected cancellation:%s", e.what());
      }
    });
  test_next_handler_async(-10)
    .then([](int v) { LOGI("==test_next_handler_async resolved:%d", v); })
    .fail([](const cti::exception_t& eptr) {
      try {
        if (eptr) {
          std::rethrow_exception(eptr);
        }
      } catch (const std::exception& e) {
        LOGI("Continuation failed with unexpected cancellation:%s", e.what());
      }
    });

  // test ready void continuable
  test_ready_continuable().then([] { LOGI("test_ready_continuable is resolved now"); });

  // test continuable order a, b
  continuable_a() >> continuable_b();
  pool.join();
  return 0;
}