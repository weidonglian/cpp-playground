//
// experimental/impl/use_coro.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
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

#ifndef ASIO_EXPERIMENTAL_IMPL_USE_CORO_HPP
#define ASIO_EXPERIMENTAL_IMPL_USE_CORO_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

<<<<<<< HEAD
#include "asio/detail/push_options.hpp"

namespace asio {
namespace experimental {

template <typename Yield, typename Return, typename Executor>
struct coro;

namespace detail {

template <typename Yield, typename Return, typename Executor>
struct coro_promise;

template <typename Executor, typename... Ts>
struct coro_init_handler
{
  struct handler_t
  {
  };

  constexpr static handler_t handler{};

  struct init_helper;

  struct promise_type
  {
    auto initial_suspend() noexcept { return suspend_always{}; }

    auto final_suspend() noexcept { return suspend_always(); }

    void return_void() {}

    void unhandled_exception() { assert(false); }

    auto await_transform(handler_t)
    {
      assert(executor);
      assert(h);
      return init_helper{this};
    }

    std::optional<Executor> executor;
    std::optional<std::tuple<Ts...>> result;
    coroutine_handle<> h;

    coro_init_handler get_return_object() { return coro_init_handler{this}; }

    cancellation_slot cancel_slot;
  };

  struct init_helper
  {
    promise_type *self_;

    constexpr static bool await_ready() noexcept { return true; }

    constexpr static void await_suspend(coroutine_handle<>) noexcept {}

    auto await_resume() const noexcept
    {
      assert(self_);
      return bind_cancellation_slot(self_->cancel_slot,
          bind_executor(*self_->executor, [self = self_](Ts... ts)
          {
            self->cancel_slot.clear();
            self->result.emplace(std::move(ts)...);
            self->h.resume();
          }));
    }
  };

  promise_type* promise;

  void unhandled_exception() noexcept
  {
    throw;
  }

  struct noexcept_version
  {
    promise_type *promise;

    constexpr static bool await_ready() noexcept { return false; }

    template <typename Yield, typename Return,
        convertible_to<Executor> Executor1>
    auto await_suspend(
        coroutine_handle<coro_promise<Yield, Return, Executor1> > h) noexcept
    {
      promise->executor = h.promise().get_executor();
      promise->h = h;
      return coroutine_handle<promise_type>::from_promise(*promise);
    }

    template <typename... Args>
    static auto resume_impl(std::tuple<Args...>&& tup)
    {
      return std::move(tup);
    }

    template <typename Arg>
    static auto resume_impl(std::tuple<Arg>&& tup)
    {
      return get<0>(std::move(tup));
    }

    static void resume_impl(std::tuple<>&&) {}

    auto await_resume() const noexcept
    {
      auto res = std::move(promise->result.value());
      coroutine_handle<promise_type>::from_promise(*promise).destroy();
      return resume_impl(std::move(res));
    }
  };

  struct throwing_version
  {
    promise_type *promise;

    constexpr static bool await_ready() noexcept { return false; }

    template <typename Yield, typename Return,
        convertible_to<Executor> Executor1>
    auto await_suspend(
        coroutine_handle<coro_promise<Yield, Return, Executor1> > h) noexcept
    {
      promise->executor = h.promise().get_executor();
      promise->h = h;
      return coroutine_handle<promise_type>::from_promise(*promise);
    }

    template <typename... Args>
    static auto resume_impl(std::tuple<Args...>&& tup)
    {
      return std::move(tup);
    }

    static void resume_impl(std::tuple<>&&) {}

    template <typename Arg>
    static auto resume_impl(std::tuple<Arg>&& tup)
    {
      return get<0>(std::move(tup));
    }

    template <typename... Args>
    static auto resume_impl(std::tuple<std::exception_ptr, Args...>&& tup)
    {
      auto ex = get<0>(std::move(tup));
      if (ex)
        std::rethrow_exception(ex);

      if constexpr (sizeof...(Args) == 0u)
        return;
      else if constexpr (sizeof...(Args) == 1u)
        return get<1>(std::move(tup));
      else
      {
        return
          [&]<std::size_t... Idx>(std::index_sequence<Idx...>)
          {
            return std::make_tuple(std::get<Idx + 1>(std::move(tup))...);
          }(std::make_index_sequence<sizeof...(Args) - 1>{});
      }
    }

    template <typename... Args>
    static auto resume_impl(
        std::tuple<asio::error_code, Args...>&& tup)
    {
      auto ec = get<0>(std::move(tup));
      if (ec)
        asio::detail::throw_exception(
            asio::system_error(ec, "error_code in use_coro"));

      if constexpr (sizeof...(Args) == 0u)
        return;
      else if constexpr (sizeof...(Args) == 1u)
        return get<1>(std::move(tup));
      else
        return
          [&]<std::size_t... Idx>(std::index_sequence<Idx...>)
          {
            return std::make_tuple(std::get<Idx + 1>(std::move(tup))...);
          }(std::make_index_sequence<sizeof...(Args) - 1>{});
    }

    static auto resume_impl(std::tuple<std::exception_ptr>&& tup)
    {
      auto ex = get<0>(std::move(tup));
      if (ex)
        std::rethrow_exception(ex);
    }

    static auto resume_impl(
        std::tuple<asio::error_code>&& tup)
    {
      auto ec = get<0>(std::move(tup));
      if (ec)
        asio::detail::throw_error(ec, "error_code in use_coro");
    }

    auto await_resume() const
    {
      auto res = std::move(promise->result.value());
      coroutine_handle<promise_type>::from_promise(*promise).destroy();
      return resume_impl(std::move(res));
    }
  };

  auto as_noexcept(cancellation_slot&& sl) && noexcept
  {
    promise->cancel_slot = std::move(sl);
    return noexcept_version{promise};
  }

  auto as_throwing(cancellation_slot&& sl) && noexcept
  {
    promise->cancel_slot = std::move(sl);
    return throwing_version{promise};
  }
};

} // namespace detail
} // namespace experimental

#if !defined(GENERATING_DOCUMENTATION)

template <typename Executor, typename R, typename... Args>
struct async_result<experimental::use_coro_t<Executor>, R(Args...)>
{
  using return_type = experimental::detail::coro_init_handler<
    Executor, typename decay<Args>::type...>;

  template <typename Initiation, typename... InitArgs>
  static return_type initiate(Initiation initiation,
      experimental::use_coro_t<Executor>, InitArgs... args)
  {
    std::move(initiation)(co_await return_type::handler, std::move(args)...);
=======
#include "asio/deferred.hpp"
#include "asio/experimental/coro.hpp"

#include "asio/detail/push_options.hpp"

namespace asio {

#if !defined(GENERATING_DOCUMENTATION)

template <typename Allocator, typename R>
struct async_result<experimental::use_coro_t<Allocator>, R()>
{
  template <typename Initiation, typename... InitArgs>
  static auto initiate_impl(Initiation initiation,
      std::allocator_arg_t, Allocator, InitArgs... args)
    -> experimental::coro<void() noexcept, void,
      asio::associated_executor_t<Initiation>, Allocator>
  {
    co_await deferred_async_operation<R(), Initiation, InitArgs...>(
        deferred_init_tag{}, std::move(initiation), std::move(args)...);
  }

  template <typename... InitArgs>
  static auto initiate_impl(asio::detail::initiation_archetype<R()>,
      std::allocator_arg_t, Allocator, InitArgs... args)
    -> experimental::coro<void(), void,
      asio::any_io_executor, Allocator>;

  template <typename Initiation, typename... InitArgs>
  static auto initiate(Initiation initiation,
      experimental::use_coro_t<Allocator> tk, InitArgs&&... args)
  {
    return initiate_impl(std::move(initiation), std::allocator_arg,
        tk.get_allocator(), std::forward<InitArgs>(args)...);
  }
};

template <typename Allocator, typename R>
struct async_result<
    experimental::use_coro_t<Allocator>, R(asio::error_code)>
{
  template <typename Initiation, typename... InitArgs>
  static auto initiate_impl(Initiation initiation,
      std::allocator_arg_t, Allocator, InitArgs... args)
    -> experimental::coro<void() noexcept, void,
      asio::associated_executor_t<Initiation>, Allocator>
  {
    co_await deferred_async_operation<
      R(asio::error_code), Initiation, InitArgs...>(
        deferred_init_tag{}, std::move(initiation), std::move(args)...);
  }

  template <typename... InitArgs>
  static auto initiate_impl(
      asio::detail::initiation_archetype<R(asio::error_code)>,
      std::allocator_arg_t, Allocator, InitArgs... args)
    -> experimental::coro<void(), void,
      asio::any_io_executor, Allocator>;

  template <typename Initiation, typename... InitArgs>
  static auto initiate(Initiation initiation,
      experimental::use_coro_t<Allocator> tk, InitArgs&&... args)
  {
    return initiate_impl(std::move(initiation), std::allocator_arg,
        tk.get_allocator(), std::forward<InitArgs>(args)...);
  }
};

template <typename Allocator, typename R>
struct async_result<
    experimental::use_coro_t<Allocator>, R(std::exception_ptr)>
{
  template <typename Initiation, typename... InitArgs>
  static auto initiate_impl(Initiation initiation,
      std::allocator_arg_t, Allocator, InitArgs... args)
    -> experimental::coro<void(), void,
      asio::associated_executor_t<Initiation>, Allocator>
  {
    co_await deferred_async_operation<
      R(std::exception_ptr), Initiation, InitArgs...>(
        deferred_init_tag{}, std::move(initiation), std::move(args)...);
  }

  template <typename... InitArgs>
  static auto initiate_impl(
      asio::detail::initiation_archetype<R(std::exception_ptr)>,
      std::allocator_arg_t, Allocator, InitArgs... args)
    -> experimental::coro<void(), void,
      asio::any_io_executor, Allocator>;

  template <typename Initiation, typename... InitArgs>
  static auto initiate(Initiation initiation,
      experimental::use_coro_t<Allocator> tk, InitArgs&&... args)
  {
    return initiate_impl(std::move(initiation), std::allocator_arg,
        tk.get_allocator(), std::forward<InitArgs>(args)...);
  }
};

template <typename Allocator, typename R, typename T>
struct async_result<experimental::use_coro_t<Allocator>, R(T)>
{

  template <typename Initiation, typename... InitArgs>
  static auto initiate_impl(Initiation initiation,
      std::allocator_arg_t, Allocator, InitArgs... args)
    -> experimental::coro<void() noexcept, T,
      asio::associated_executor_t<Initiation>, Allocator>
  {
    co_return co_await deferred_async_operation<R(T), Initiation, InitArgs...>(
        deferred_init_tag{}, std::move(initiation), std::move(args)...);
  }

  template <typename... InitArgs>
  static auto initiate_impl(asio::detail::initiation_archetype<R(T)>,
      std::allocator_arg_t, Allocator, InitArgs... args)
    -> experimental::coro<void() noexcept, T,
      asio::any_io_executor, Allocator>;

  template <typename Initiation, typename... InitArgs>
  static auto initiate(Initiation initiation,
      experimental::use_coro_t<Allocator> tk, InitArgs&&... args)
  {
    return initiate_impl(std::move(initiation), std::allocator_arg,
        tk.get_allocator(), std::forward<InitArgs>(args)...);
  }
};

template <typename Allocator, typename R, typename T>
struct async_result<
    experimental::use_coro_t<Allocator>, R(asio::error_code, T)>
{
  template <typename Initiation, typename... InitArgs>
  static auto initiate_impl(Initiation initiation,
      std::allocator_arg_t, Allocator, InitArgs... args)
    -> experimental::coro<void(), T,
      asio::associated_executor_t<Initiation>, Allocator>
  {
    co_return co_await deferred_async_operation<
      R(asio::error_code, T), Initiation, InitArgs...>(
        deferred_init_tag{}, std::move(initiation), std::move(args)...);
  }

  template <typename... InitArgs>
  static auto initiate_impl(
      asio::detail::initiation_archetype<
        R(asio::error_code, T)>,
      std::allocator_arg_t, Allocator, InitArgs... args)
    -> experimental::coro<void(), T, asio::any_io_executor, Allocator>;

  template <typename Initiation, typename... InitArgs>
  static auto initiate(Initiation initiation,
      experimental::use_coro_t<Allocator> tk, InitArgs&&... args)
  {
    return initiate_impl(std::move(initiation), std::allocator_arg,
        tk.get_allocator(), std::forward<InitArgs>(args)...);
  }
};

template <typename Allocator, typename R, typename T>
struct async_result<
    experimental::use_coro_t<Allocator>, R(std::exception_ptr, T)>
{
  template <typename Initiation, typename... InitArgs>
  static auto initiate_impl(Initiation initiation,
      std::allocator_arg_t, Allocator, InitArgs... args)
    -> experimental::coro<void(), T,
      asio::associated_executor_t<Initiation>, Allocator>
  {
    co_return co_await deferred_async_operation<
      R(std::exception_ptr, T), Initiation, InitArgs...>(
        deferred_init_tag{}, std::move(initiation), std::move(args)...);
  }

  template <typename... InitArgs>
  static auto initiate_impl(
      asio::detail::initiation_archetype<R(std::exception_ptr, T)>,
      std::allocator_arg_t, Allocator, InitArgs... args)
    -> experimental::coro<void(), T, asio::any_io_executor, Allocator>;

  template <typename Initiation, typename... InitArgs>
  static auto initiate(Initiation initiation,
      experimental::use_coro_t<Allocator> tk, InitArgs&&... args)
  {
    return initiate_impl(std::move(initiation), std::allocator_arg,
        tk.get_allocator(), std::forward<InitArgs>(args)...);
>>>>>>> 142038d (add asio new version)
  }
};

#endif // !defined(GENERATING_DOCUMENTATION)

} // namespace asio

#include "asio/detail/pop_options.hpp"

#endif // ASIO_EXPERIMENTAL_IMPL_USE_CORO_HPP
