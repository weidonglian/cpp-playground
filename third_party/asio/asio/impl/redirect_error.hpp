
// impl/redirect_error.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~
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

#ifndef ASIO_IMPL_REDIRECT_ERROR_HPP
#define ASIO_IMPL_REDIRECT_ERROR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include "asio/detail/config.hpp"
<<<<<<< HEAD
=======
#include "asio/associated_executor.hpp"
>>>>>>> 142038d (add asio new version)
#include "asio/associator.hpp"
#include "asio/async_result.hpp"
#include "asio/detail/handler_cont_helpers.hpp"
#include "asio/detail/initiation_base.hpp"
#include "asio/detail/type_traits.hpp"
#include "asio/system_error.hpp"

#include "asio/detail/push_options.hpp"

namespace asio {
namespace detail {

// Class to adapt a redirect_error_t as a completion handler.
template <typename Handler>
class redirect_error_handler
{
public:
  typedef void result_type;

  template <typename CompletionToken>
  redirect_error_handler(redirect_error_t<CompletionToken> e)
    : ec_(e.ec_),
      handler_(static_cast<CompletionToken&&>(e.token_))
  {
  }

  template <typename RedirectedHandler>
  redirect_error_handler(asio::error_code& ec,
      RedirectedHandler&& h)
    : ec_(ec),
      handler_(static_cast<RedirectedHandler&&>(h))
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

  template <typename Arg, typename... Args>
  enable_if_t<
    !is_same<decay_t<Arg>, asio::error_code>::value
  >
  operator()(Arg&& arg, Args&&... args)
  {
<<<<<<< HEAD
    ASIO_MOVE_OR_LVALUE(Handler)(handler_)(
        ASIO_MOVE_CAST(Arg)(arg),
        ASIO_MOVE_CAST(Args)(args)...);
=======
    static_cast<Handler&&>(handler_)(
        static_cast<Arg&&>(arg),
        static_cast<Args&&>(args)...);
>>>>>>> 142038d (add asio new version)
  }

  template <typename... Args>
  void operator()(const asio::error_code& ec, Args&&... args)
  {
    ec_ = ec;
<<<<<<< HEAD
    ASIO_MOVE_OR_LVALUE(Handler)(handler_)(
        ASIO_MOVE_CAST(Args)(args)...);
  }

#else // defined(ASIO_HAS_VARIADIC_TEMPLATES)

  template <typename Arg>
  typename enable_if<
    !is_same<typename decay<Arg>::type, asio::error_code>::value
  >::type
  operator()(ASIO_MOVE_ARG(Arg) arg)
  {
    ASIO_MOVE_OR_LVALUE(Handler)(handler_)(
        ASIO_MOVE_CAST(Arg)(arg));
  }

  void operator()(const asio::error_code& ec)
  {
    ec_ = ec;
    ASIO_MOVE_OR_LVALUE(Handler)(handler_)();
  }

#define ASIO_PRIVATE_REDIRECT_ERROR_DEF(n) \
  template <typename Arg, ASIO_VARIADIC_TPARAMS(n)> \
  typename enable_if< \
    !is_same<typename decay<Arg>::type, asio::error_code>::value \
  >::type \
  operator()(ASIO_MOVE_ARG(Arg) arg, ASIO_VARIADIC_MOVE_PARAMS(n)) \
  { \
    ASIO_MOVE_OR_LVALUE(Handler)(handler_)( \
        ASIO_MOVE_CAST(Arg)(arg), \
        ASIO_VARIADIC_MOVE_ARGS(n)); \
  } \
  \
  template <ASIO_VARIADIC_TPARAMS(n)> \
  void operator()(const asio::error_code& ec, \
      ASIO_VARIADIC_MOVE_PARAMS(n)) \
  { \
    ec_ = ec; \
    ASIO_MOVE_OR_LVALUE(Handler)(handler_)( \
        ASIO_VARIADIC_MOVE_ARGS(n)); \
  } \
  /**/
  ASIO_VARIADIC_GENERATE(ASIO_PRIVATE_REDIRECT_ERROR_DEF)
#undef ASIO_PRIVATE_REDIRECT_ERROR_DEF

#endif // defined(ASIO_HAS_VARIADIC_TEMPLATES)

=======
    static_cast<Handler&&>(handler_)(static_cast<Args&&>(args)...);
  }

>>>>>>> 142038d (add asio new version)
//private:
  asio::error_code& ec_;
  Handler handler_;
};

template <typename Handler>
inline bool asio_handler_is_continuation(
    redirect_error_handler<Handler>* this_handler)
{
  return asio_handler_cont_helpers::is_continuation(
        this_handler->handler_);
}

template <typename Signature>
struct redirect_error_signature
{
  typedef Signature type;
};

template <typename R, typename... Args>
struct redirect_error_signature<R(asio::error_code, Args...)>
{
  typedef R type(Args...);
};

template <typename R, typename... Args>
struct redirect_error_signature<R(const asio::error_code&, Args...)>
{
  typedef R type(Args...);
};

<<<<<<< HEAD
# if defined(ASIO_HAS_REF_QUALIFIED_FUNCTIONS)

template <typename R, typename... Args>
struct redirect_error_signature<R(asio::error_code, Args...) &>
{
  typedef R type(Args...) &;
};

template <typename R, typename... Args>
struct redirect_error_signature<R(const asio::error_code&, Args...) &>
{
  typedef R type(Args...) &;
};

template <typename R, typename... Args>
struct redirect_error_signature<R(asio::error_code, Args...) &&>
{
  typedef R type(Args...) &&;
};

template <typename R, typename... Args>
struct redirect_error_signature<R(const asio::error_code&, Args...) &&>
{
  typedef R type(Args...) &&;
};

#  if defined(ASIO_HAS_NOEXCEPT_FUNCTION_TYPE)

template <typename R, typename... Args>
struct redirect_error_signature<
  R(asio::error_code, Args...) noexcept>
{
  typedef R type(Args...) & noexcept;
};

template <typename R, typename... Args>
struct redirect_error_signature<
  R(const asio::error_code&, Args...) noexcept>
{
  typedef R type(Args...) & noexcept;
};

template <typename R, typename... Args>
struct redirect_error_signature<
  R(asio::error_code, Args...) & noexcept>
{
  typedef R type(Args...) & noexcept;
};

template <typename R, typename... Args>
struct redirect_error_signature<
  R(const asio::error_code&, Args...) & noexcept>
{
  typedef R type(Args...) & noexcept;
};

template <typename R, typename... Args>
struct redirect_error_signature<
  R(asio::error_code, Args...) && noexcept>
{
  typedef R type(Args...) && noexcept;
};

template <typename R, typename... Args>
struct redirect_error_signature<
  R(const asio::error_code&, Args...) && noexcept>
{
  typedef R type(Args...) && noexcept;
};

#  endif // defined(ASIO_HAS_NOEXCEPT_FUNCTION_TYPE)
# endif // defined(ASIO_HAS_REF_QUALIFIED_FUNCTIONS)
#else // defined(ASIO_HAS_VARIADIC_TEMPLATES)

template <typename R>
struct redirect_error_signature<R(asio::error_code)>
=======
template <typename R, typename... Args>
struct redirect_error_signature<R(asio::error_code, Args...) &>
>>>>>>> 142038d (add asio new version)
{
  typedef R type(Args...) &;
};

template <typename R, typename... Args>
struct redirect_error_signature<R(const asio::error_code&, Args...) &>
{
  typedef R type(Args...) &;
};

template <typename R, typename... Args>
struct redirect_error_signature<R(asio::error_code, Args...) &&>
{
  typedef R type(Args...) &&;
};

<<<<<<< HEAD
# if defined(ASIO_HAS_REF_QUALIFIED_FUNCTIONS)

template <typename R>
struct redirect_error_signature<R(asio::error_code) &>
{
  typedef R type() &;
};

template <typename R>
struct redirect_error_signature<R(const asio::error_code&) &>
{
  typedef R type() &;
};

template <typename R>
struct redirect_error_signature<R(asio::error_code) &&>
{
  typedef R type() &&;
};

template <typename R>
struct redirect_error_signature<R(const asio::error_code&) &&>
{
  typedef R type() &&;
};

#define ASIO_PRIVATE_REDIRECT_ERROR_DEF(n) \
  template <typename R, ASIO_VARIADIC_TPARAMS(n)> \
  struct redirect_error_signature< \
      R(asio::error_code, ASIO_VARIADIC_TARGS(n)) &> \
  { \
    typedef R type(ASIO_VARIADIC_TARGS(n)) &; \
  }; \
  \
  template <typename R, ASIO_VARIADIC_TPARAMS(n)> \
  struct redirect_error_signature< \
      R(const asio::error_code&, ASIO_VARIADIC_TARGS(n)) &> \
  { \
    typedef R type(ASIO_VARIADIC_TARGS(n)) &; \
  }; \
  \
  template <typename R, ASIO_VARIADIC_TPARAMS(n)> \
  struct redirect_error_signature< \
      R(asio::error_code, ASIO_VARIADIC_TARGS(n)) &&> \
  { \
    typedef R type(ASIO_VARIADIC_TARGS(n)) &&; \
  }; \
  \
  template <typename R, ASIO_VARIADIC_TPARAMS(n)> \
  struct redirect_error_signature< \
      R(const asio::error_code&, ASIO_VARIADIC_TARGS(n)) &&> \
  { \
    typedef R type(ASIO_VARIADIC_TARGS(n)) &&; \
  }; \
  /**/
  ASIO_VARIADIC_GENERATE(ASIO_PRIVATE_REDIRECT_ERROR_DEF)
#undef ASIO_PRIVATE_REDIRECT_ERROR_DEF

#  if defined(ASIO_HAS_NOEXCEPT_FUNCTION_TYPE)

template <typename R>
struct redirect_error_signature<
  R(asio::error_code) noexcept>
{
  typedef R type() noexcept;
};

template <typename R>
struct redirect_error_signature<
  R(const asio::error_code&) noexcept>
{
  typedef R type() noexcept;
};

template <typename R>
struct redirect_error_signature<
  R(asio::error_code) & noexcept>
{
  typedef R type() & noexcept;
};

template <typename R>
struct redirect_error_signature<
  R(const asio::error_code&) & noexcept>
{
  typedef R type() & noexcept;
};

template <typename R>
struct redirect_error_signature<
  R(asio::error_code) && noexcept>
{
  typedef R type() && noexcept;
};

template <typename R>
struct redirect_error_signature<
  R(const asio::error_code&) && noexcept>
{
  typedef R type() && noexcept;
};

#define ASIO_PRIVATE_REDIRECT_ERROR_DEF(n) \
  template <typename R, ASIO_VARIADIC_TPARAMS(n)> \
  struct redirect_error_signature< \
      R(asio::error_code, ASIO_VARIADIC_TARGS(n)) noexcept> \
  { \
    typedef R type(ASIO_VARIADIC_TARGS(n)) noexcept; \
  }; \
  \
  template <typename R, ASIO_VARIADIC_TPARAMS(n)> \
  struct redirect_error_signature< \
      R(const asio::error_code&, \
        ASIO_VARIADIC_TARGS(n)) noexcept> \
  { \
    typedef R type(ASIO_VARIADIC_TARGS(n)) noexcept; \
  }; \
  \
  template <typename R, ASIO_VARIADIC_TPARAMS(n)> \
  struct redirect_error_signature< \
      R(asio::error_code, \
        ASIO_VARIADIC_TARGS(n)) & noexcept> \
  { \
    typedef R type(ASIO_VARIADIC_TARGS(n)) & noexcept; \
  }; \
  \
  template <typename R, ASIO_VARIADIC_TPARAMS(n)> \
  struct redirect_error_signature< \
      R(const asio::error_code&, \
        ASIO_VARIADIC_TARGS(n)) & noexcept> \
  { \
    typedef R type(ASIO_VARIADIC_TARGS(n)) & noexcept; \
  }; \
  \
  template <typename R, ASIO_VARIADIC_TPARAMS(n)> \
  struct redirect_error_signature< \
      R(asio::error_code, \
        ASIO_VARIADIC_TARGS(n)) && noexcept> \
  { \
    typedef R type(ASIO_VARIADIC_TARGS(n)) && noexcept; \
  }; \
  \
  template <typename R, ASIO_VARIADIC_TPARAMS(n)> \
  struct redirect_error_signature< \
      R(const asio::error_code&, \
        ASIO_VARIADIC_TARGS(n)) && noexcept> \
  { \
    typedef R type(ASIO_VARIADIC_TARGS(n)) && noexcept; \
  }; \
  /**/
  ASIO_VARIADIC_GENERATE(ASIO_PRIVATE_REDIRECT_ERROR_DEF)
#undef ASIO_PRIVATE_REDIRECT_ERROR_DEF

#  endif // defined(ASIO_HAS_NOEXCEPT_FUNCTION_TYPE)
# endif // defined(ASIO_HAS_REF_QUALIFIED_FUNCTIONS)
#endif // defined(ASIO_HAS_VARIADIC_TEMPLATES)
=======
template <typename R, typename... Args>
struct redirect_error_signature<R(const asio::error_code&, Args...) &&>
{
  typedef R type(Args...) &&;
};

#if defined(ASIO_HAS_NOEXCEPT_FUNCTION_TYPE)

template <typename R, typename... Args>
struct redirect_error_signature<
  R(asio::error_code, Args...) noexcept>
{
  typedef R type(Args...) & noexcept;
};

template <typename R, typename... Args>
struct redirect_error_signature<
  R(const asio::error_code&, Args...) noexcept>
{
  typedef R type(Args...) & noexcept;
};

template <typename R, typename... Args>
struct redirect_error_signature<
  R(asio::error_code, Args...) & noexcept>
{
  typedef R type(Args...) & noexcept;
};

template <typename R, typename... Args>
struct redirect_error_signature<
  R(const asio::error_code&, Args...) & noexcept>
{
  typedef R type(Args...) & noexcept;
};

template <typename R, typename... Args>
struct redirect_error_signature<
  R(asio::error_code, Args...) && noexcept>
{
  typedef R type(Args...) && noexcept;
};

template <typename R, typename... Args>
struct redirect_error_signature<
  R(const asio::error_code&, Args...) && noexcept>
{
  typedef R type(Args...) && noexcept;
};

#endif // defined(ASIO_HAS_NOEXCEPT_FUNCTION_TYPE)
>>>>>>> 142038d (add asio new version)

} // namespace detail

#if !defined(GENERATING_DOCUMENTATION)

template <typename CompletionToken, typename Signature>
struct async_result<redirect_error_t<CompletionToken>, Signature>
  : async_result<CompletionToken,
      typename detail::redirect_error_signature<Signature>::type>
{
  template <typename Initiation>
  struct init_wrapper : detail::initiation_base<Initiation>
  {
    using detail::initiation_base<Initiation>::initiation_base;

    template <typename Handler, typename... Args>
    void operator()(Handler&& handler,
        asio::error_code* ec, Args&&... args) &&
    {
      static_cast<Initiation&&>(*this)(
          detail::redirect_error_handler<decay_t<Handler>>(
            *ec, static_cast<Handler&&>(handler)),
          static_cast<Args&&>(args)...);
    }

    template <typename Handler, typename... Args>
    void operator()(Handler&& handler,
        asio::error_code* ec, Args&&... args) const &
    {
      static_cast<const Initiation&>(*this)(
          detail::redirect_error_handler<decay_t<Handler>>(
            *ec, static_cast<Handler&&>(handler)),
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
        typename detail::redirect_error_signature<Signature>::type>(
          declval<init_wrapper<decay_t<Initiation>>>(),
          token.token_, &token.ec_, static_cast<Args&&>(args)...))
  {
    return async_initiate<
      conditional_t<
        is_const<remove_reference_t<RawCompletionToken>>::value,
          const CompletionToken, CompletionToken>,
      typename detail::redirect_error_signature<Signature>::type>(
<<<<<<< HEAD
        init_wrapper<typename decay<Initiation>::type>(
          token.ec_, ASIO_MOVE_CAST(Initiation)(initiation)),
        token.token_, ASIO_MOVE_CAST(Args)(args)...);
  }

#else // defined(ASIO_HAS_VARIADIC_TEMPLATES)

  template <typename Initiation, typename RawCompletionToken>
  static return_type initiate(
      ASIO_MOVE_ARG(Initiation) initiation,
      ASIO_MOVE_ARG(RawCompletionToken) token)
  {
    return async_initiate<CompletionToken,
      typename detail::redirect_error_signature<Signature>::type>(
        init_wrapper<typename decay<Initiation>::type>(
          token.ec_, ASIO_MOVE_CAST(Initiation)(initiation)),
        token.token_);
  }

#define ASIO_PRIVATE_INITIATE_DEF(n) \
  template <typename Initiation, typename RawCompletionToken, \
      ASIO_VARIADIC_TPARAMS(n)> \
  static return_type initiate( \
      ASIO_MOVE_ARG(Initiation) initiation, \
      ASIO_MOVE_ARG(RawCompletionToken) token, \
      ASIO_VARIADIC_MOVE_PARAMS(n)) \
  { \
    return async_initiate<CompletionToken, \
      typename detail::redirect_error_signature<Signature>::type>( \
        init_wrapper<typename decay<Initiation>::type>( \
          token.ec_, ASIO_MOVE_CAST(Initiation)(initiation)), \
        token.token_, ASIO_VARIADIC_MOVE_ARGS(n)); \
  } \
  /**/
  ASIO_VARIADIC_GENERATE(ASIO_PRIVATE_INITIATE_DEF)
#undef ASIO_PRIVATE_INITIATE_DEF

#endif // defined(ASIO_HAS_VARIADIC_TEMPLATES)
=======
        init_wrapper<decay_t<Initiation>>(
          static_cast<Initiation&&>(initiation)),
        token.token_, &token.ec_, static_cast<Args&&>(args)...);
  }
>>>>>>> 142038d (add asio new version)
};

template <template <typename, typename> class Associator,
    typename Handler, typename DefaultCandidate>
struct associator<Associator,
    detail::redirect_error_handler<Handler>, DefaultCandidate>
  : Associator<Handler, DefaultCandidate>
{
  static typename Associator<Handler, DefaultCandidate>::type get(
<<<<<<< HEAD
      const detail::redirect_error_handler<Handler>& h,
      const DefaultCandidate& c = DefaultCandidate()) ASIO_NOEXCEPT
  {
    return Associator<Handler, DefaultCandidate>::get(h.handler_, c);
=======
      const detail::redirect_error_handler<Handler>& h) noexcept
  {
    return Associator<Handler, DefaultCandidate>::get(h.handler_);
  }

  static auto get(const detail::redirect_error_handler<Handler>& h,
      const DefaultCandidate& c) noexcept
    -> decltype(Associator<Handler, DefaultCandidate>::get(h.handler_, c))
  {
    return Associator<Handler, DefaultCandidate>::get(h.handler_, c);
  }
};

template <typename... Signatures>
struct async_result<partial_redirect_error, Signatures...>
{
  template <typename Initiation, typename RawCompletionToken, typename... Args>
  static auto initiate(Initiation&& initiation,
      RawCompletionToken&& token, Args&&... args)
    -> decltype(
      async_initiate<Signatures...>(
        static_cast<Initiation&&>(initiation),
        redirect_error_t<
          default_completion_token_t<associated_executor_t<Initiation>>>(
            default_completion_token_t<associated_executor_t<Initiation>>{},
            token.ec_),
        static_cast<Args&&>(args)...))
  {
    return async_initiate<Signatures...>(
        static_cast<Initiation&&>(initiation),
        redirect_error_t<
          default_completion_token_t<associated_executor_t<Initiation>>>(
            default_completion_token_t<associated_executor_t<Initiation>>{},
            token.ec_),
        static_cast<Args&&>(args)...);
>>>>>>> 142038d (add asio new version)
  }
};

#endif // !defined(GENERATING_DOCUMENTATION)

} // namespace asio

#include "asio/detail/pop_options.hpp"

#endif // ASIO_IMPL_REDIRECT_ERROR_HPP
