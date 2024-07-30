//
// prepend.hpp
// ~~~~~~~~~~~
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

#ifndef ASIO_PREPEND_HPP
#define ASIO_PREPEND_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include "asio/detail/config.hpp"
<<<<<<< HEAD

#if (defined(ASIO_HAS_STD_TUPLE) \
    && defined(ASIO_HAS_VARIADIC_TEMPLATES)) \
  || defined(GENERATING_DOCUMENTATION)

=======
>>>>>>> 142038d (add asio new version)
#include <tuple>
#include "asio/detail/type_traits.hpp"

#include "asio/detail/push_options.hpp"

namespace asio {

/// Completion token type used to specify that the completion handler
/// arguments should be passed additional values before the results of the
/// operation.
template <typename CompletionToken, typename... Values>
class prepend_t
{
public:
  /// Constructor.
  template <typename T, typename... V>
<<<<<<< HEAD
  ASIO_CONSTEXPR explicit prepend_t(
      ASIO_MOVE_ARG(T) completion_token,
      ASIO_MOVE_ARG(V)... values)
    : token_(ASIO_MOVE_CAST(T)(completion_token)),
      values_(ASIO_MOVE_CAST(V)(values)...)
=======
  constexpr explicit prepend_t(T&& completion_token, V&&... values)
    : token_(static_cast<T&&>(completion_token)),
      values_(static_cast<V&&>(values)...)
>>>>>>> 142038d (add asio new version)
  {
  }

//private:
  CompletionToken token_;
  std::tuple<Values...> values_;
};

/// Completion token type used to specify that the completion handler
/// arguments should be passed additional values before the results of the
/// operation.
template <typename CompletionToken, typename... Values>
<<<<<<< HEAD
ASIO_NODISCARD inline ASIO_CONSTEXPR prepend_t<
  typename decay<CompletionToken>::type, typename decay<Values>::type...>
prepend(ASIO_MOVE_ARG(CompletionToken) completion_token,
    ASIO_MOVE_ARG(Values)... values)
{
  return prepend_t<
    typename decay<CompletionToken>::type, typename decay<Values>::type...>(
      ASIO_MOVE_CAST(CompletionToken)(completion_token),
      ASIO_MOVE_CAST(Values)(values)...);
=======
ASIO_NODISCARD inline constexpr
prepend_t<decay_t<CompletionToken>, decay_t<Values>...>
prepend(CompletionToken&& completion_token,
    Values&&... values)
{
  return prepend_t<decay_t<CompletionToken>, decay_t<Values>...>(
      static_cast<CompletionToken&&>(completion_token),
      static_cast<Values&&>(values)...);
>>>>>>> 142038d (add asio new version)
}

} // namespace asio

#include "asio/detail/pop_options.hpp"

#include "asio/impl/prepend.hpp"

<<<<<<< HEAD
#endif // (defined(ASIO_HAS_STD_TUPLE)
       //     && defined(ASIO_HAS_VARIADIC_TEMPLATES))
       //   || defined(GENERATING_DOCUMENTATION)

=======
>>>>>>> 142038d (add asio new version)
#endif // ASIO_PREPEND_HPP
