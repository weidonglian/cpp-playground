//
// experimental/impl/as_single.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
<<<<<<< HEAD
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
=======
// Copyright (c) 2003-2024 Christopher M. Kohlhoff (chris at kohlhoff dot com)
>>>>>>> 142038d (add asio new version)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef ASIO_IMPL_EXPERIMENTAL_AS_SINGLE_HPP
#define ASIO_IMPL_EXPERIMENTAL_AS_SINGLE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include "asio/detail/config.hpp"
#include <tuple>
<<<<<<< HEAD

=======
>>>>>>> 142038d (add asio new version)
#include "asio/associator.hpp"
#include "asio/async_result.hpp"
#include "asio/detail/handler_cont_helpers.hpp"
#include "asio/detail/initiation_base.hpp"
#include "asio/detail/type_traits.hpp"

#include "asio/detail/push_options.hpp"

namespace asio {
namespace experimental {
namespace detail {

// Class to adapt a as_single_t as a completion handler.
template <typename Handler>
class as_single_handler
{
public:
  typedef void result_type;

  template <typename CompletionToken>
  as_single_handler(as_single_t<CompletionToken> e)
    : handler_(static_cast<CompletionToken&&>(e.token_))
  {
  }

  template <typename RedirectedHandler>
  as_single_handler(RedirectedHandler&& h)
    : handler_(static_cast<RedirectedHandler&&>(h))
  {
  }

  void operator()()
  {
<<<<<<< HEAD
    ASIO_MOVE_OR_LVALUE(Handler)(handler_)();
=======
    static_cast<Handler&&>(handler_)();
>>>>>>> 142038d (add asio new version)
  }

  template <typename Arg>
  void operator()(Arg&& arg)
  {
<<<<<<< HEAD
    ASIO_MOVE_OR_LVALUE(Handler)(handler_)(
        ASIO_MOVE_CAST(Arg)(arg));
=======
    static_cast<Handler&&>(handler_)(static_cast<Arg&&>(arg));
>>>>>>> 142038d (add asio new version)
  }

  template <typename... Args>
  void operator()(Args&&... args)
  {
<<<<<<< HEAD
    ASIO_MOVE_OR_LVALUE(Handler)(handler_)(
        std::make_tuple(ASIO_MOVE_CAST(Args)(args)...));
=======
    static_cast<Handler&&>(handler_)(
        std::make_tuple(static_cast<Args&&>(args)...));
>>>>>>> 142038d (add asio new version)
  }

//private:
  Handler handler_;
};

template <typename Handler>
<<<<<<< HEAD
inline asio_handler_allocate_is_deprecated
asio_handler_allocate(std::size_t size,
    as_single_handler<Handler>* this_handler)
{
#if defined(ASIO_NO_DEPRECATED)
  asio_handler_alloc_helpers::allocate(size, this_handler->handler_);
  return asio_handler_allocate_is_no_longer_used();
#else // defined(ASIO_NO_DEPRECATED)
  return asio_handler_alloc_helpers::allocate(
      size, this_handler->handler_);
#endif // defined(ASIO_NO_DEPRECATED)
}

template <typename Handler>
inline asio_handler_deallocate_is_deprecated
asio_handler_deallocate(void* pointer, std::size_t size,
    as_single_handler<Handler>* this_handler)
{
  asio_handler_alloc_helpers::deallocate(
      pointer, size, this_handler->handler_);
#if defined(ASIO_NO_DEPRECATED)
  return asio_handler_deallocate_is_no_longer_used();
#endif // defined(ASIO_NO_DEPRECATED)
}

template <typename Handler>
=======
>>>>>>> 142038d (add asio new version)
inline bool asio_handler_is_continuation(
    as_single_handler<Handler>* this_handler)
{
  return asio_handler_cont_helpers::is_continuation(
        this_handler->handler_);
}

<<<<<<< HEAD
template <typename Function, typename Handler>
inline asio_handler_invoke_is_deprecated
asio_handler_invoke(Function& function,
    as_single_handler<Handler>* this_handler)
{
  asio_handler_invoke_helpers::invoke(
      function, this_handler->handler_);
#if defined(ASIO_NO_DEPRECATED)
  return asio_handler_invoke_is_no_longer_used();
#endif // defined(ASIO_NO_DEPRECATED)
}

template <typename Function, typename Handler>
inline asio_handler_invoke_is_deprecated
asio_handler_invoke(const Function& function,
    as_single_handler<Handler>* this_handler)
{
  asio_handler_invoke_helpers::invoke(
      function, this_handler->handler_);
#if defined(ASIO_NO_DEPRECATED)
  return asio_handler_invoke_is_no_longer_used();
#endif // defined(ASIO_NO_DEPRECATED)
}

=======
>>>>>>> 142038d (add asio new version)
template <typename Signature>
struct as_single_signature
{
  typedef Signature type;
};

template <typename R>
struct as_single_signature<R()>
{
  typedef R type();
};

template <typename R, typename Arg>
struct as_single_signature<R(Arg)>
{
  typedef R type(Arg);
};

template <typename R, typename... Args>
struct as_single_signature<R(Args...)>
{
  typedef R type(std::tuple<decay_t<Args>...>);
};

} // namespace detail
} // namespace experimental

#if !defined(GENERATING_DOCUMENTATION)

template <typename CompletionToken, typename Signature>
struct async_result<experimental::as_single_t<CompletionToken>, Signature>
{
  template <typename Initiation>
  struct init_wrapper : detail::initiation_base<Initiation>
  {
    using detail::initiation_base<Initiation>::initiation_base;

    template <typename Handler, typename... Args>
    void operator()(Handler&& handler, Args&&... args) &&
    {
      static_cast<Initiation&&>(*this)(
          experimental::detail::as_single_handler<decay_t<Handler>>(
            static_cast<Handler&&>(handler)),
          static_cast<Args&&>(args)...);
    }

    template <typename Handler, typename... Args>
    void operator()(Handler&& handler, Args&&... args) const &
    {
      static_cast<const Initiation&>(*this)(
          experimental::detail::as_single_handler<decay_t<Handler>>(
            static_cast<Handler&&>(handler)),
          static_cast<Args&&>(args)...);
    }
  };

  template <typename Initiation, typename RawCompletionToken, typename... Args>
  static auto initiate(Initiation&& initiation,
      RawCompletionToken&& token, Args&&... args)
    -> decltype(
      async_initiate<CompletionToken,
        typename experimental::detail::as_single_signature<Signature>::type>(
          init_wrapper<decay_t<Initiation>>(
            static_cast<Initiation&&>(initiation)),
          token.token_, static_cast<Args&&>(args)...))
  {
    return async_initiate<CompletionToken,
      typename experimental::detail::as_single_signature<Signature>::type>(
        init_wrapper<decay_t<Initiation>>(
          static_cast<Initiation&&>(initiation)),
        token.token_, static_cast<Args&&>(args)...);
  }
};

template <template <typename, typename> class Associator,
    typename Handler, typename DefaultCandidate>
struct associator<Associator,
    experimental::detail::as_single_handler<Handler>, DefaultCandidate>
  : Associator<Handler, DefaultCandidate>
{
  static typename Associator<Handler, DefaultCandidate>::type get(
<<<<<<< HEAD
      const experimental::detail::as_single_handler<Handler>& h,
      const DefaultCandidate& c = DefaultCandidate()) ASIO_NOEXCEPT
  {
=======
      const experimental::detail::as_single_handler<Handler>& h) noexcept
  {
    return Associator<Handler, DefaultCandidate>::get(h.handler_);
  }

  static auto get(const experimental::detail::as_single_handler<Handler>& h,
      const DefaultCandidate& c) noexcept
    -> decltype(Associator<Handler, DefaultCandidate>::get(h.handler_, c))
  {
>>>>>>> 142038d (add asio new version)
    return Associator<Handler, DefaultCandidate>::get(h.handler_, c);
  }
};

#endif // !defined(GENERATING_DOCUMENTATION)

} // namespace asio

#include "asio/detail/pop_options.hpp"

#endif // ASIO_IMPL_EXPERIMENTAL_AS_SINGLE_HPP
