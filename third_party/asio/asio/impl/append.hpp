//
// impl/append.hpp
// ~~~~~~~~~~~~~~~
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

#ifndef ASIO_IMPL_APPEND_HPP
#define ASIO_IMPL_APPEND_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include "asio/detail/config.hpp"
<<<<<<< HEAD

#include "asio/associator.hpp"
#include "asio/async_result.hpp"
#include "asio/detail/handler_alloc_helpers.hpp"
#include "asio/detail/handler_cont_helpers.hpp"
#include "asio/detail/handler_invoke_helpers.hpp"
#include "asio/detail/type_traits.hpp"
#include "asio/detail/utility.hpp"
#include "asio/detail/variadic_templates.hpp"
=======
#include "asio/associator.hpp"
#include "asio/async_result.hpp"
#include "asio/detail/handler_cont_helpers.hpp"
#include "asio/detail/initiation_base.hpp"
#include "asio/detail/type_traits.hpp"
#include "asio/detail/utility.hpp"
>>>>>>> 142038d (add asio new version)

#include "asio/detail/push_options.hpp"

namespace asio {
namespace detail {

// Class to adapt an append_t as a completion handler.
template <typename Handler, typename... Values>
class append_handler
{
public:
  typedef void result_type;

  template <typename H>
<<<<<<< HEAD
  append_handler(ASIO_MOVE_ARG(H) handler, std::tuple<Values...> values)
    : handler_(ASIO_MOVE_CAST(H)(handler)),
      values_(ASIO_MOVE_CAST(std::tuple<Values...>)(values))
=======
  append_handler(H&& handler, std::tuple<Values...> values)
    : handler_(static_cast<H&&>(handler)),
      values_(static_cast<std::tuple<Values...>&&>(values))
>>>>>>> 142038d (add asio new version)
  {
  }

  template <typename... Args>
<<<<<<< HEAD
  void operator()(ASIO_MOVE_ARG(Args)... args)
  {
    this->invoke(
        index_sequence_for<Values...>{},
        ASIO_MOVE_CAST(Args)(args)...);
  }

  template <std::size_t... I, typename... Args>
  void invoke(index_sequence<I...>, ASIO_MOVE_ARG(Args)... args)
  {
    ASIO_MOVE_OR_LVALUE(Handler)(handler_)(
        ASIO_MOVE_CAST(Args)(args)...,
        ASIO_MOVE_CAST(Values)(std::get<I>(values_))...);
=======
  void operator()(Args&&... args)
  {
    this->invoke(
        index_sequence_for<Values...>{},
        static_cast<Args&&>(args)...);
  }

  template <std::size_t... I, typename... Args>
  void invoke(index_sequence<I...>, Args&&... args)
  {
    static_cast<Handler&&>(handler_)(
        static_cast<Args&&>(args)...,
        static_cast<Values&&>(std::get<I>(values_))...);
>>>>>>> 142038d (add asio new version)
  }

//private:
  Handler handler_;
  std::tuple<Values...> values_;
};

template <typename Handler>
<<<<<<< HEAD
inline asio_handler_allocate_is_deprecated
asio_handler_allocate(std::size_t size,
    append_handler<Handler>* this_handler)
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
    append_handler<Handler>* this_handler)
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
    append_handler<Handler>* this_handler)
{
  return asio_handler_cont_helpers::is_continuation(
      this_handler->handler_);
}

<<<<<<< HEAD
template <typename Function, typename Handler>
inline asio_handler_invoke_is_deprecated
asio_handler_invoke(Function& function,
    append_handler<Handler>* this_handler)
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
    append_handler<Handler>* this_handler)
{
  asio_handler_invoke_helpers::invoke(
      function, this_handler->handler_);
#if defined(ASIO_NO_DEPRECATED)
  return asio_handler_invoke_is_no_longer_used();
#endif // defined(ASIO_NO_DEPRECATED)
}

=======
>>>>>>> 142038d (add asio new version)
template <typename Signature, typename... Values>
struct append_signature;

template <typename R, typename... Args, typename... Values>
struct append_signature<R(Args...), Values...>
{
<<<<<<< HEAD
  typedef R type(typename decay<Args>::type..., Values...);
=======
  typedef R type(decay_t<Args>..., Values...);
>>>>>>> 142038d (add asio new version)
};

} // namespace detail

#if !defined(GENERATING_DOCUMENTATION)

template <typename CompletionToken, typename... Values, typename Signature>
<<<<<<< HEAD
struct async_result<
    append_t<CompletionToken, Values...>, Signature>
=======
struct async_result<append_t<CompletionToken, Values...>, Signature>
>>>>>>> 142038d (add asio new version)
  : async_result<CompletionToken,
      typename detail::append_signature<
        Signature, Values...>::type>
{
  typedef typename detail::append_signature<
      Signature, Values...>::type signature;

  template <typename Initiation>
<<<<<<< HEAD
  struct init_wrapper
  {
    init_wrapper(Initiation init)
      : initiation_(ASIO_MOVE_CAST(Initiation)(init))
    {
    }

    template <typename Handler, typename... Args>
    void operator()(
        ASIO_MOVE_ARG(Handler) handler,
        std::tuple<Values...> values,
        ASIO_MOVE_ARG(Args)... args)
    {
      ASIO_MOVE_CAST(Initiation)(initiation_)(
          detail::append_handler<
            typename decay<Handler>::type, Values...>(
              ASIO_MOVE_CAST(Handler)(handler),
              ASIO_MOVE_CAST(std::tuple<Values...>)(values)),
          ASIO_MOVE_CAST(Args)(args)...);
    }

    Initiation initiation_;
  };

  template <typename Initiation, typename RawCompletionToken, typename... Args>
  static ASIO_INITFN_DEDUCED_RESULT_TYPE(CompletionToken, signature,
      (async_initiate<CompletionToken, signature>(
        declval<init_wrapper<typename decay<Initiation>::type> >(),
        declval<CompletionToken&>(),
        declval<std::tuple<Values...> >(),
        declval<ASIO_MOVE_ARG(Args)>()...)))
  initiate(
      ASIO_MOVE_ARG(Initiation) initiation,
      ASIO_MOVE_ARG(RawCompletionToken) token,
      ASIO_MOVE_ARG(Args)... args)
  {
    return async_initiate<CompletionToken, signature>(
        init_wrapper<typename decay<Initiation>::type>(
          ASIO_MOVE_CAST(Initiation)(initiation)),
        token.token_,
        ASIO_MOVE_CAST(std::tuple<Values...>)(token.values_),
        ASIO_MOVE_CAST(Args)(args)...);
=======
  struct init_wrapper : detail::initiation_base<Initiation>
  {
    using detail::initiation_base<Initiation>::initiation_base;

    template <typename Handler, typename... Args>
    void operator()(Handler&& handler,
        std::tuple<Values...> values, Args&&... args) &&
    {
      static_cast<Initiation&&>(*this)(
          detail::append_handler<decay_t<Handler>, Values...>(
            static_cast<Handler&&>(handler),
            static_cast<std::tuple<Values...>&&>(values)),
          static_cast<Args&&>(args)...);
    }

    template <typename Handler, typename... Args>
    void operator()(Handler&& handler,
        std::tuple<Values...> values, Args&&... args) const &
    {
      static_cast<const Initiation&>(*this)(
          detail::append_handler<decay_t<Handler>, Values...>(
            static_cast<Handler&&>(handler),
            static_cast<std::tuple<Values...>&&>(values)),
          static_cast<Args&&>(args)...);
    }
  };

  template <typename Initiation, typename RawCompletionToken, typename... Args>
  static auto initiate(Initiation&& initiation,
      RawCompletionToken&& token, Args&&... args)
    -> decltype(
      async_initiate<CompletionToken, signature>(
        declval<init_wrapper<decay_t<Initiation>>>(),
        token.token_,
        static_cast<std::tuple<Values...>&&>(token.values_),
        static_cast<Args&&>(args)...))
  {
    return async_initiate<CompletionToken, signature>(
        init_wrapper<decay_t<Initiation>>(
          static_cast<Initiation&&>(initiation)),
        token.token_,
        static_cast<std::tuple<Values...>&&>(token.values_),
        static_cast<Args&&>(args)...);
>>>>>>> 142038d (add asio new version)
  }
};

template <template <typename, typename> class Associator,
    typename Handler, typename... Values, typename DefaultCandidate>
struct associator<Associator,
    detail::append_handler<Handler, Values...>, DefaultCandidate>
  : Associator<Handler, DefaultCandidate>
{
  static typename Associator<Handler, DefaultCandidate>::type get(
<<<<<<< HEAD
      const detail::append_handler<Handler, Values...>& h,
      const DefaultCandidate& c = DefaultCandidate()) ASIO_NOEXCEPT
=======
      const detail::append_handler<Handler, Values...>& h) noexcept
  {
    return Associator<Handler, DefaultCandidate>::get(h.handler_);
  }

  static auto get(const detail::append_handler<Handler, Values...>& h,
      const DefaultCandidate& c) noexcept
    -> decltype(Associator<Handler, DefaultCandidate>::get(h.handler_, c))
>>>>>>> 142038d (add asio new version)
  {
    return Associator<Handler, DefaultCandidate>::get(h.handler_, c);
  }
};

#endif // !defined(GENERATING_DOCUMENTATION)

} // namespace asio

#include "asio/detail/pop_options.hpp"

#endif // ASIO_IMPL_APPEND_HPP
