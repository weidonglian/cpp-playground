//
// experimental/detail/partial_promise.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
<<<<<<< HEAD
// Copyright (c) 2021-2022 Klemens D. Morgenstern
=======
// Copyright (c) 2021-2023 Klemens D. Morgenstern
>>>>>>> 142038d (add asio new version)
//                         (klemens dot morgenstern at gmx dot net)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef ASIO_EXPERIMENTAL_DETAIL_PARTIAL_PROMISE_HPP
#define ASIO_EXPERIMENTAL_DETAIL_PARTIAL_PROMISE_HPP

#include "asio/detail/config.hpp"
<<<<<<< HEAD
=======
#include "asio/append.hpp"
>>>>>>> 142038d (add asio new version)
#include "asio/awaitable.hpp"
#include "asio/experimental/coro_traits.hpp"

#if defined(ASIO_HAS_STD_COROUTINE)
# include <coroutine>
#else // defined(ASIO_HAS_STD_COROUTINE)
# include <experimental/coroutine>
#endif // defined(ASIO_HAS_STD_COROUTINE)

namespace asio {
namespace experimental {
namespace detail {

#if defined(ASIO_HAS_STD_COROUTINE)

using std::coroutine_handle;
using std::coroutine_traits;
using std::suspend_never;
using std::suspend_always;
using std::noop_coroutine;

#else // defined(ASIO_HAS_STD_COROUTINE)

using std::experimental::coroutine_handle;
using std::experimental::coroutine_traits;
using std::experimental::suspend_never;
using std::experimental::suspend_always;
using std::experimental::noop_coroutine;

#endif // defined(ASIO_HAS_STD_COROUTINE)

<<<<<<< HEAD
struct partial_promise
=======
struct partial_coro
{
  coroutine_handle<void> handle{nullptr};
};

template <typename Allocator>
struct partial_promise_base
{
  template <typename Executor, typename Token, typename... Args>
  void* operator new(std::size_t size, Executor&, Token& tk, Args&...)
  {
    return allocate_coroutine<Allocator>(size, get_associated_allocator(tk));
  }

  void operator delete(void* raw, std::size_t size)
  {
    deallocate_coroutine<Allocator>(raw, size);
  }
};

template <>
struct partial_promise_base<std::allocator<void>>
{
};

template <typename Allocator>
struct partial_promise : partial_promise_base<Allocator>
>>>>>>> 142038d (add asio new version)
{
  auto initial_suspend() noexcept
  {
    return asio::detail::suspend_always{};
  }

  auto final_suspend() noexcept
  {
    struct awaitable_t
    {
      partial_promise *p;

      constexpr bool await_ready() noexcept { return true; }

      auto await_suspend(asio::detail::coroutine_handle<>) noexcept
      {
<<<<<<< HEAD
        p->get_return_object().destroy();
=======
        p->get_return_object().handle.destroy();
>>>>>>> 142038d (add asio new version)
      }

      constexpr void await_resume() noexcept {}
    };

    return awaitable_t{this};
  }

  void return_void() {}

<<<<<<< HEAD
  coroutine_handle<partial_promise> get_return_object()
  {
    return coroutine_handle<partial_promise>::from_promise(*this);
=======
  partial_coro get_return_object()
  {
    return partial_coro{coroutine_handle<partial_promise>::from_promise(*this)};
>>>>>>> 142038d (add asio new version)
  }

  void unhandled_exception()
  {
    assert(false);
  }
};

} // namespace detail
} // namespace experimental
} // namespace asio

#if defined(ASIO_HAS_STD_COROUTINE)

namespace std {

<<<<<<< HEAD
template <typename ... Args>
struct coroutine_traits<
    coroutine_handle<asio::experimental::detail::partial_promise>,
    Args...>
{
  using promise_type = asio::experimental::detail::partial_promise;
=======
template <typename Executor, typename Completion, typename... Args>
struct coroutine_traits<
    asio::experimental::detail::partial_coro,
    Executor, Completion, Args...>
{
  using promise_type =
    asio::experimental::detail::partial_promise<
      asio::associated_allocator_t<Completion>>;
>>>>>>> 142038d (add asio new version)
};

} // namespace std

#else // defined(ASIO_HAS_STD_COROUTINE)

namespace std { namespace experimental {

<<<<<<< HEAD
template <typename... Args>
struct coroutine_traits<
    coroutine_handle<asio::experimental::detail::partial_promise>,
    Args...>
{
  using promise_type = asio::experimental::detail::partial_promise;
=======
template <typename Executor, typename Completion, typename... Args>
struct coroutine_traits<
    asio::experimental::detail::partial_coro,
    Executor, Completion, Args...>
{
  using promise_type =
    asio::experimental::detail::partial_promise<
      asio::associated_allocator_t<Completion>>;
>>>>>>> 142038d (add asio new version)
};

}} // namespace std::experimental

#endif // defined(ASIO_HAS_STD_COROUTINE)

namespace asio {
namespace experimental {
namespace detail {

<<<<<<< HEAD
template <typename CompletionToken>
auto post_coroutine(CompletionToken token) noexcept
  -> coroutine_handle<partial_promise>
{
  post(std::move(token));
  co_return;
}

template <execution::executor Executor, typename CompletionToken>
auto post_coroutine(Executor exec, CompletionToken token) noexcept
  -> coroutine_handle<partial_promise>
{
  post(exec, std::move(token));
  co_return;
}

template <detail::execution_context Context, typename CompletionToken>
auto post_coroutine(Context &ctx, CompletionToken token) noexcept
  -> coroutine_handle<partial_promise>
{
  post(ctx, std::move(token));
  co_return;
}

template <typename CompletionToken>
auto dispatch_coroutine(CompletionToken token) noexcept
  -> coroutine_handle<partial_promise>
{
  dispatch(std::move(token));
  co_return;
}

template <execution::executor Executor, typename CompletionToken>
auto dispatch_coroutine(Executor exec, CompletionToken token) noexcept
  -> coroutine_handle<partial_promise>
{
  dispatch(exec, std::move(token));
  co_return;
}

template <detail::execution_context Context, typename CompletionToken>
auto dispatch_coroutine(Context &ctx, CompletionToken token) noexcept
  -> coroutine_handle<partial_promise>
{
  dispatch(ctx, std::move(token));
=======
template <execution::executor Executor,
    typename CompletionToken, typename... Args>
partial_coro post_coroutine(Executor exec,
    CompletionToken token, Args&&... args) noexcept
{
  post(exec, asio::append(std::move(token), std::move(args)...));
  co_return;
}

template <detail::execution_context Context,
    typename CompletionToken, typename... Args>
partial_coro post_coroutine(Context& ctx,
    CompletionToken token, Args&&... args) noexcept
{
  post(ctx, asio::append(std::move(token), std::move(args)...));
  co_return;
}

template <execution::executor Executor,
    typename CompletionToken, typename... Args>
partial_coro dispatch_coroutine(Executor exec,
    CompletionToken token, Args&&... args) noexcept
{
  dispatch(exec, asio::append(std::move(token), std::move(args)...));
  co_return;
}

template <detail::execution_context Context,
    typename CompletionToken, typename... Args>
partial_coro dispatch_coroutine(Context& ctx,
    CompletionToken token, Args &&... args) noexcept
{
  dispatch(ctx, asio::append(std::move(token), std::move(args)...));
>>>>>>> 142038d (add asio new version)
  co_return;
}

} // namespace detail
} // namespace experimental
} // namespace asio

#endif // ASIO_EXPERIMENTAL_DETAIL_PARTIAL_PROMISE_HPP
