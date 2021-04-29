
/*

                        /~` _  _ _|_. _     _ |_ | _
                        \_,(_)| | | || ||_|(_||_)|(/_

                    https://github.com/Naios/continuable
                                   v4.1.0

  Copyright(c) 2015 - 2020 Denis Blank <denis.blank at outlook dot com>

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files(the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions :

  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
**/

#ifndef CONTINUABLE_DETAIL_TRANSFORMS_WAIT_HPP_INCLUDED
#define CONTINUABLE_DETAIL_TRANSFORMS_WAIT_HPP_INCLUDED

#include <atomic>
#include <cassert>
#include <condition_variable>
#include <memory>
#include <mutex>
#include <continuable/continuable-primitives.hpp>
#include <continuable/continuable-result.hpp>
#include <continuable/detail/core/annotation.hpp>
#include <continuable/detail/core/base.hpp>
#include <continuable/detail/core/types.hpp>
#include <continuable/detail/features.hpp>

#if defined(CONTINUABLE_HAS_EXCEPTIONS)
#  include <exception>
#endif

namespace cti {
namespace detail {
namespace transforms {
#if defined(CONTINUABLE_HAS_EXCEPTIONS)
class wait_transform_canceled_exception : public std::exception {
public:
  wait_transform_canceled_exception() noexcept = default;

  char const* what() const noexcept override {
    return "cti::transforms::wait canceled due to cancellation of the "
           "continuation";
  }
};
#endif // CONTINUABLE_HAS_EXCEPTIONS

template <typename Hint>
struct sync_trait;
template <typename... Args>
struct sync_trait<identity<Args...>> {
  using result_t = result<Args...>;
};

using lock_t = std::unique_lock<std::mutex>;
using condition_variable_t = std::condition_variable;

template <typename Data, typename Annotation,
          typename Result = typename sync_trait<Annotation>::result_t>
Result wait_relaxed(continuable_base<Data, Annotation>&& continuable) {

  // Do an immediate unpack if the continuable is ready
  if (continuable.is_ready()) {
    return std::move(continuable).unpack();
  }

  condition_variable_t cv;
  std::mutex cv_mutex;

  bool ready{false};
  Result sync_result;

  std::move(continuable)
      .next([&](auto&&... args) {
        sync_result = Result::from(std::forward<decltype(args)>(args)...);

        lock_t lock(cv_mutex);
        ready = true;
        cv.notify_all();
      })
      .done();

  lock_t lock(cv_mutex);
  if (!ready) {
    cv.wait(lock, [&] {
      return ready;
    });
  }

  return sync_result;
}

/// Transforms the continuation to sync execution and unpacks the result the if
/// possible
template <typename Data, typename Annotation>
auto wait_and_unpack(continuable_base<Data, Annotation>&& continuable) {

  auto sync_result = wait_relaxed(std::move(continuable));

#if defined(CONTINUABLE_HAS_EXCEPTIONS)
  if (sync_result.is_value()) {
    return std::move(sync_result).get_value();
  } else {
    assert(sync_result.is_exception());
    if (exception_t e = sync_result.get_exception()) {
      std::rethrow_exception(e);
    } else {
      throw wait_transform_canceled_exception();
    }
  }
#else
  return sync_result;
#endif // CONTINUABLE_HAS_EXCEPTIONS
}

template <typename Result>
struct wait_frame {
  std::mutex cv_mutex;
  std::mutex rw_mutex;
  condition_variable_t cv;
  std::atomic_bool ready{false};
  Result sync_result;
};

template <typename Data, typename Annotation, typename Waiter,
          typename Result = typename sync_trait<Annotation>::result_t>
Result wait_unsafe(continuable_base<Data, Annotation>&& continuable,
                   Waiter&& waiter) {

  // Do an immediate unpack if the continuable is ready
  if (continuable.is_ready()) {
    return std::move(continuable).unpack();
  }

  using frame_t = wait_frame<Result>;

  auto frame = std::make_shared<frame_t>();

  std::move(continuable)
      .next([frame = std::weak_ptr<frame_t>(frame)](auto&&... args) {
        if (auto locked = frame.lock()) {
          {
            std::lock_guard<std::mutex> rw_lock(locked->rw_mutex);
            locked->sync_result = Result::from(
                std::forward<decltype(args)>(args)...);
          }

          locked->ready.store(true, std::memory_order_release);
          locked->cv.notify_all();
        }
      })
      .done();

  if (!frame->ready.load(std::memory_order_acquire)) {
    lock_t lock(frame->cv_mutex);
    std::forward<Waiter>(waiter)(frame->cv, lock, [&] {
      return frame->ready.load(std::memory_order_acquire);
    });
  }

  return ([&] {
    std::lock_guard<std::mutex> rw_lock(frame->rw_mutex);
    Result cached = std::move(frame->sync_result);
    return cached;
  })();
}
} // namespace transforms
} // namespace detail
} // namespace cti

#endif // CONTINUABLE_DETAIL_TRANSFORMS_WAIT_HPP_INCLUDED
