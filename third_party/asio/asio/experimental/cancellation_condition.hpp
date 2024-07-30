//
// experimental/cancellation_condition.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
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

#ifndef ASIO_EXPERIMENTAL_CANCELLATION_CONDITION_HPP
#define ASIO_EXPERIMENTAL_CANCELLATION_CONDITION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include "asio/detail/config.hpp"
#include <exception>
#include "asio/cancellation_type.hpp"
#include "asio/error_code.hpp"
#include "asio/detail/type_traits.hpp"

#include "asio/detail/push_options.hpp"

namespace asio {
namespace experimental {

/// Wait for all operations to complete.
class wait_for_all
{
public:
  template <typename... Args>
<<<<<<< HEAD
  ASIO_CONSTEXPR cancellation_type_t operator()(
      Args&&...) const ASIO_NOEXCEPT
=======
  constexpr cancellation_type_t operator()(Args&&...) const noexcept
>>>>>>> 142038d (add asio new version)
  {
    return cancellation_type::none;
  }
};

/// Wait until an operation completes, then cancel the others.
class wait_for_one
{
public:
<<<<<<< HEAD
  ASIO_CONSTEXPR explicit wait_for_one(
=======
  constexpr explicit wait_for_one(
>>>>>>> 142038d (add asio new version)
      cancellation_type_t cancel_type = cancellation_type::all)
    : cancel_type_(cancel_type)
  {
  }

  template <typename... Args>
<<<<<<< HEAD
  ASIO_CONSTEXPR cancellation_type_t operator()(
      Args&&...) const ASIO_NOEXCEPT
=======
  constexpr cancellation_type_t operator()(Args&&...) const noexcept
>>>>>>> 142038d (add asio new version)
  {
    return cancel_type_;
  }

private:
  cancellation_type_t cancel_type_;
};

/// Wait until an operation completes without an error, then cancel the others.
/**
 * If no operation completes without an error, waits for completion of all
 * operations.
 */
class wait_for_one_success
{
public:
<<<<<<< HEAD
  ASIO_CONSTEXPR explicit wait_for_one_success(
=======
  constexpr explicit wait_for_one_success(
>>>>>>> 142038d (add asio new version)
      cancellation_type_t cancel_type = cancellation_type::all)
    : cancel_type_(cancel_type)
  {
  }

<<<<<<< HEAD
  ASIO_CONSTEXPR cancellation_type_t
  operator()() const ASIO_NOEXCEPT
=======
  constexpr cancellation_type_t
  operator()() const noexcept
>>>>>>> 142038d (add asio new version)
  {
    return cancel_type_;
  }

  template <typename E, typename... Args>
<<<<<<< HEAD
  ASIO_CONSTEXPR typename constraint<
    !is_same<typename decay<E>::type, asio::error_code>::value
      && !is_same<typename decay<E>::type, std::exception_ptr>::value,
    cancellation_type_t
  >::type operator()(const E&, Args&&...) const ASIO_NOEXCEPT
=======
  constexpr constraint_t<
    !is_same<decay_t<E>, asio::error_code>::value
      && !is_same<decay_t<E>, std::exception_ptr>::value,
    cancellation_type_t
  > operator()(const E&, Args&&...) const noexcept
>>>>>>> 142038d (add asio new version)
  {
    return cancel_type_;
  }

  template <typename E, typename... Args>
<<<<<<< HEAD
  ASIO_CONSTEXPR typename constraint<
      is_same<typename decay<E>::type, asio::error_code>::value
        || is_same<typename decay<E>::type, std::exception_ptr>::value,
      cancellation_type_t
  >::type operator()(const E& e, Args&&...) const ASIO_NOEXCEPT
=======
  constexpr constraint_t<
      is_same<decay_t<E>, asio::error_code>::value
        || is_same<decay_t<E>, std::exception_ptr>::value,
      cancellation_type_t
  > operator()(const E& e, Args&&...) const noexcept
>>>>>>> 142038d (add asio new version)
  {
    return !!e ? cancellation_type::none : cancel_type_;
  }

private:
  cancellation_type_t cancel_type_;
};

/// Wait until an operation completes with an error, then cancel the others.
/**
 * If no operation completes with an error, waits for completion of all
 * operations.
 */
class wait_for_one_error
{
public:
<<<<<<< HEAD
  ASIO_CONSTEXPR explicit wait_for_one_error(
=======
  constexpr explicit wait_for_one_error(
>>>>>>> 142038d (add asio new version)
      cancellation_type_t cancel_type = cancellation_type::all)
    : cancel_type_(cancel_type)
  {
  }

<<<<<<< HEAD
  ASIO_CONSTEXPR cancellation_type_t
  operator()() const ASIO_NOEXCEPT
=======
  constexpr cancellation_type_t operator()() const noexcept
>>>>>>> 142038d (add asio new version)
  {
    return cancellation_type::none;
  }

  template <typename E, typename... Args>
<<<<<<< HEAD
  ASIO_CONSTEXPR typename constraint<
    !is_same<typename decay<E>::type, asio::error_code>::value
      && !is_same<typename decay<E>::type, std::exception_ptr>::value,
    cancellation_type_t
  >::type operator()(const E&, Args&&...) const ASIO_NOEXCEPT
=======
  constexpr constraint_t<
    !is_same<decay_t<E>, asio::error_code>::value
      && !is_same<decay_t<E>, std::exception_ptr>::value,
    cancellation_type_t
  > operator()(const E&, Args&&...) const noexcept
>>>>>>> 142038d (add asio new version)
  {
    return cancellation_type::none;
  }

  template <typename E, typename... Args>
<<<<<<< HEAD
  ASIO_CONSTEXPR typename constraint<
      is_same<typename decay<E>::type, asio::error_code>::value
        || is_same<typename decay<E>::type, std::exception_ptr>::value,
      cancellation_type_t
  >::type operator()(const E& e, Args&&...) const ASIO_NOEXCEPT
=======
  constexpr constraint_t<
      is_same<decay_t<E>, asio::error_code>::value
        || is_same<decay_t<E>, std::exception_ptr>::value,
      cancellation_type_t
  > operator()(const E& e, Args&&...) const noexcept
>>>>>>> 142038d (add asio new version)
  {
    return !!e ? cancel_type_ : cancellation_type::none;
  }

private:
  cancellation_type_t cancel_type_;
};

} // namespace experimental
} // namespace asio

#include "asio/detail/pop_options.hpp"

#endif // ASIO_EXPERIMENTAL_CANCELLATION_CONDITION_HPP
