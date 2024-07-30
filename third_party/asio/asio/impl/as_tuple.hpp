//
// impl/as_tuple.hpp
// ~~~~~~~~~~~~~~~~~
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

#ifndef ASIO_IMPL_AS_TUPLE_HPP
#define ASIO_IMPL_AS_TUPLE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include "asio/detail/config.hpp"
<<<<<<< HEAD

#include <tuple>

#include "asio/associator.hpp"
#include "asio/async_result.hpp"
#include "asio/detail/handler_alloc_helpers.hpp"
#include "asio/detail/handler_cont_helpers.hpp"
#include "asio/detail/handler_invoke_helpers.hpp"
#include "asio/detail/type_traits.hpp"
#include "asio/detail/variadic_templates.hpp"
=======
#include <tuple>
#include "asio/associated_executor.hpp"
#include "asio/associator.hpp"
#include "asio/async_result.hpp"
#include "asio/detail/handler_cont_helpers.hpp"
#include "asio/detail/initiation_base.hpp"
#include "asio/detail/type_traits.hpp"
>>>>>>> 142038d (add asio new version)

#include "asio/detail/push_options.hpp"

namespace asio {
namespace detail {

// Class to adapt a as_tuple_t as a completion handler.
template <typename Handler>
class as_tuple_handler
{
public:
  typedef void result_type;

  template <typename CompletionToken>
  as_tuple_handler(as_tuple_t<CompletionToken> e)
<<<<<<< HEAD
    : handler_(ASIO_MOVE_CAST(CompletionToken)(e.token_))
=======
    : handler_(static_cast<CompletionToken&&>(e.token_))
>>>>>>> 142038d (add asio new version)
  {
  }

  template <typename RedirectedHandler>
<<<<<<< HEAD
  as_tuple_handler(ASIO_MOVE_ARG(RedirectedHandler) h)
    : handler_(ASIO_MOVE_CAST(RedirectedHandler)(h))
=======
  as_tuple_handler(RedirectedHandler&& h)
    : handler_(static_cast<RedirectedHandler&&>(h))
>>>>>>> 142038d (add asio new version)
  {
  }

  template <typename... Args>
<<<<<<< HEAD
  void operator()(ASIO_MOVE_ARG(Args)... args)
  {
    ASIO_MOVE_OR_LVALUE(Handler)(handler_)(
        std::make_tuple(ASIO_MOVE_CAST(Args)(args)...));
=======
  void operator()(Args&&... args)
  {
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
    as_tuple_handler<Handler>* this_handler)
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
    as_tuple_handler<Handler>* this_handler)
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
    as_tuple_handler<Handler>* this_handler)
{
  return asio_handler_cont_helpers::is_continuation(
        this_handler->handler_);
}

<<<<<<< HEAD
template <typename Function, typename Handler>
inline asio_handler_invoke_is_deprecated
asio_handler_invoke(Function& function,
    as_tuple_handler<Handler>* this_handler)
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
    as_tuple_handler<Handler>* this_handler)
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
struct as_tuple_signature;

template <typename R, typename... Args>
struct as_tuple_signature<R(Args...)>
{
<<<<<<< HEAD
  typedef R type(std::tuple<typename decay<Args>::type...>);
};

#if defined(ASIO_HAS_REF_QUALIFIED_FUNCTIONS)

template <typename R, typename... Args>
struct as_tuple_signature<R(Args...) &>
{
  typedef R type(std::tuple<typename decay<Args>::type...>) &;
=======
  typedef R type(std::tuple<decay_t<Args>...>);
};

template <typename R, typename... Args>
struct as_tuple_signature<R(Args...) &>
{
  typedef R type(std::tuple<decay_t<Args>...>) &;
>>>>>>> 142038d (add asio new version)
};

template <typename R, typename... Args>
struct as_tuple_signature<R(Args...) &&>
{
<<<<<<< HEAD
  typedef R type(std::tuple<typename decay<Args>::type...>) &&;
};

# if defined(ASIO_HAS_NOEXCEPT_FUNCTION_TYPE)
=======
  typedef R type(std::tuple<decay_t<Args>...>) &&;
};

#if defined(ASIO_HAS_NOEXCEPT_FUNCTION_TYPE)
>>>>>>> 142038d (add asio new version)

template <typename R, typename... Args>
struct as_tuple_signature<R(Args...) noexcept>
{
<<<<<<< HEAD
  typedef R type(std::tuple<typename decay<Args>::type...>) noexcept;
=======
  typedef R type(std::tuple<decay_t<Args>...>) noexcept;
>>>>>>> 142038d (add asio new version)
};

template <typename R, typename... Args>
struct as_tuple_signature<R(Args...) & noexcept>
{
<<<<<<< HEAD
  typedef R type(std::tuple<typename decay<Args>::type...>) & noexcept;
=======
  typedef R type(std::tuple<decay_t<Args>...>) & noexcept;
>>>>>>> 142038d (add asio new version)
};

template <typename R, typename... Args>
struct as_tuple_signature<R(Args...) && noexcept>
{
<<<<<<< HEAD
  typedef R type(std::tuple<typename decay<Args>::type...>) && noexcept;
};

# endif // defined(ASIO_HAS_NOEXCEPT_FUNCTION_TYPE)
#endif // defined(ASIO_HAS_REF_QUALIFIED_FUNCTIONS)
=======
  typedef R type(std::tuple<decay_t<Args>...>) && noexcept;
};

#endif // defined(ASIO_HAS_NOEXCEPT_FUNCTION_TYPE)
>>>>>>> 142038d (add asio new version)

} // namespace detail

#if !defined(GENERATING_DOCUMENTATION)

template <typename CompletionToken, typename... Signatures>
struct async_result<as_tuple_t<CompletionToken>, Signatures...>
  : async_result<CompletionToken,
      typename detail::as_tuple_signature<Signatures>::type...>
{
<<<<<<< HEAD
  typedef async_result<CompletionToken,
    typename detail::as_tuple_signature<Signatures>::type...>
      base_async_result;

  template <typename Initiation>
  struct init_wrapper
  {
    init_wrapper(Initiation init)
      : initiation_(ASIO_MOVE_CAST(Initiation)(init))
    {
    }

    template <typename Handler, typename... Args>
    void operator()(
        ASIO_MOVE_ARG(Handler) handler,
        ASIO_MOVE_ARG(Args)... args)
    {
      ASIO_MOVE_CAST(Initiation)(initiation_)(
          detail::as_tuple_handler<
            typename decay<Handler>::type>(
              ASIO_MOVE_CAST(Handler)(handler)),
          ASIO_MOVE_CAST(Args)(args)...);
    }

    Initiation initiation_;
  };

  template <typename Initiation, typename RawCompletionToken, typename... Args>
  static ASIO_INITFN_DEDUCED_RESULT_TYPE(CompletionToken,
      typename detail::as_tuple_signature<Signatures>::type...,
      (base_async_result::initiate(
        declval<init_wrapper<typename decay<Initiation>::type> >(),
        declval<CompletionToken>(),
        declval<ASIO_MOVE_ARG(Args)>()...)))
  initiate(
      ASIO_MOVE_ARG(Initiation) initiation,
      ASIO_MOVE_ARG(RawCompletionToken) token,
      ASIO_MOVE_ARG(Args)... args)
  {
    return base_async_result::initiate(
        init_wrapper<typename decay<Initiation>::type>(
          ASIO_MOVE_CAST(Initiation)(initiation)),
        token.token_, ASIO_MOVE_CAST(Args)(args)...);
  }
};

=======
  template <typename Initiation>
  struct init_wrapper : detail::initiation_base<Initiation>
  {
    using detail::initiation_base<Initiation>::initiation_base;

    template <typename Handler, typename... Args>
    void operator()(Handler&& handler, Args&&... args) &&
    {
      static_cast<Initiation&&>(*this)(
          detail::as_tuple_handler<decay_t<Handler>>(
            static_cast<Handler&&>(handler)),
          static_cast<Args&&>(args)...);
    }

    template <typename Handler, typename... Args>
    void operator()(Handler&& handler, Args&&... args) const &
    {
      static_cast<const Initiation&>(*this)(
          detail::as_tuple_handler<decay_t<Handler>>(
            static_cast<Handler&&>(handler)),
          static_cast<Args&&>(args)...);
    }
  };

  template <typename Initiation, typename RawCompletionToken, typename... Args>
  static auto initiate(Initiation&& initiation,
      RawCompletionToken&& token, Args&&... args)
    -> decltype(
      async_initiate<
        conditional_t<
          is_const<remove_reference_t<RawCompletionToken>>::value,
            const CompletionToken, CompletionToken>,
        typename detail::as_tuple_signature<Signatures>::type...>(
          init_wrapper<decay_t<Initiation>>(
            static_cast<Initiation&&>(initiation)),
          token.token_, static_cast<Args&&>(args)...))
  {
    return async_initiate<
      conditional_t<
        is_const<remove_reference_t<RawCompletionToken>>::value,
          const CompletionToken, CompletionToken>,
      typename detail::as_tuple_signature<Signatures>::type...>(
        init_wrapper<decay_t<Initiation>>(
          static_cast<Initiation&&>(initiation)),
        token.token_, static_cast<Args&&>(args)...);
  }
};

#if defined(ASIO_MSVC)

// Workaround for MSVC internal compiler error.

template <typename CompletionToken, typename Signature>
struct async_result<as_tuple_t<CompletionToken>, Signature>
  : async_result<CompletionToken,
      typename detail::as_tuple_signature<Signature>::type>
{
  template <typename Initiation>
  struct init_wrapper : detail::initiation_base<Initiation>
  {
    using detail::initiation_base<Initiation>::initiation_base;

    template <typename Handler, typename... Args>
    void operator()(Handler&& handler, Args&&... args) &&
    {
      static_cast<Initiation&&>(*this)(
          detail::as_tuple_handler<decay_t<Handler>>(
            static_cast<Handler&&>(handler)),
          static_cast<Args&&>(args)...);
    }

    template <typename Handler, typename... Args>
    void operator()(Handler&& handler, Args&&... args) const &
    {
      static_cast<const Initiation&>(*this)(
          detail::as_tuple_handler<decay_t<Handler>>(
            static_cast<Handler&&>(handler)),
          static_cast<Args&&>(args)...);
    }
  };

  template <typename Initiation, typename RawCompletionToken, typename... Args>
  static auto initiate(Initiation&& initiation,
      RawCompletionToken&& token, Args&&... args)
    -> decltype(
      async_initiate<
        conditional_t<
          is_const<remove_reference_t<RawCompletionToken>>::value,
            const CompletionToken, CompletionToken>,
        typename detail::as_tuple_signature<Signature>::type>(
          init_wrapper<decay_t<Initiation>>(
            static_cast<Initiation&&>(initiation)),
          token.token_, static_cast<Args&&>(args)...))
  {
    return async_initiate<
      conditional_t<
        is_const<remove_reference_t<RawCompletionToken>>::value,
          const CompletionToken, CompletionToken>,
      typename detail::as_tuple_signature<Signature>::type>(
        init_wrapper<decay_t<Initiation>>(
          static_cast<Initiation&&>(initiation)),
        token.token_, static_cast<Args&&>(args)...);
  }
};

#endif // defined(ASIO_MSVC)

>>>>>>> 142038d (add asio new version)
template <template <typename, typename> class Associator,
    typename Handler, typename DefaultCandidate>
struct associator<Associator,
    detail::as_tuple_handler<Handler>, DefaultCandidate>
  : Associator<Handler, DefaultCandidate>
{
  static typename Associator<Handler, DefaultCandidate>::type get(
<<<<<<< HEAD
      const detail::as_tuple_handler<Handler>& h,
      const DefaultCandidate& c = DefaultCandidate()) ASIO_NOEXCEPT
=======
      const detail::as_tuple_handler<Handler>& h) noexcept
  {
    return Associator<Handler, DefaultCandidate>::get(h.handler_);
  }

  static auto get(const detail::as_tuple_handler<Handler>& h,
      const DefaultCandidate& c) noexcept
    -> decltype(Associator<Handler, DefaultCandidate>::get(h.handler_, c))
>>>>>>> 142038d (add asio new version)
  {
    return Associator<Handler, DefaultCandidate>::get(h.handler_, c);
  }
};

<<<<<<< HEAD
=======
template <typename... Signatures>
struct async_result<partial_as_tuple, Signatures...>
{
  template <typename Initiation, typename RawCompletionToken, typename... Args>
  static auto initiate(Initiation&& initiation,
      RawCompletionToken&&, Args&&... args)
    -> decltype(
      async_initiate<Signatures...>(
        static_cast<Initiation&&>(initiation),
        as_tuple_t<
          default_completion_token_t<associated_executor_t<Initiation>>>{},
        static_cast<Args&&>(args)...))
  {
    return async_initiate<Signatures...>(
        static_cast<Initiation&&>(initiation),
        as_tuple_t<
          default_completion_token_t<associated_executor_t<Initiation>>>{},
        static_cast<Args&&>(args)...);
  }
};

>>>>>>> 142038d (add asio new version)
#endif // !defined(GENERATING_DOCUMENTATION)

} // namespace asio

#include "asio/detail/pop_options.hpp"

#endif // ASIO_IMPL_AS_TUPLE_HPP
