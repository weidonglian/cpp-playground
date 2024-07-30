//
// cancellation_type.hpp
// ~~~~~~~~~~~~~~~~~~~~~
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

#ifndef ASIO_CANCELLATION_TYPE_HPP
#define ASIO_CANCELLATION_TYPE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include "asio/detail/config.hpp"

#include "asio/detail/push_options.hpp"

namespace asio {

# if defined(GENERATING_DOCUMENTATION)

/// Enumeration representing the different types of cancellation that may
/// be requested from or implemented by an asynchronous operation.
enum cancellation_type
{
  /// Bitmask representing no types of cancellation.
  none = 0,

  /// Requests cancellation where, following a successful cancellation, the only
  /// safe operations on the I/O object are closure or destruction.
  terminal = 1,

  /// Requests cancellation where a successful cancellation may result in
  /// partial side effects or no side effects. Following cancellation, the I/O
  /// object is in a well-known state, and may be used for further operations.
  partial = 2,

  /// Requests cancellation where a successful cancellation results in no
  /// apparent side effects. Following cancellation, the I/O object is in the
  /// same observable state as it was prior to the operation.
  total = 4,

  /// Bitmask representing all types of cancellation.
  all = 0xFFFFFFFF
};

/// Portability typedef.
typedef cancellation_type cancellation_type_t;

<<<<<<< HEAD
#elif defined(ASIO_HAS_ENUM_CLASS)
=======
#else // defined(GENERATING_DOCUMENTATION)
>>>>>>> 142038d (add asio new version)

enum class cancellation_type : unsigned int
{
  none = 0,
  terminal = 1,
  partial = 2,
  total = 4,
  all = 0xFFFFFFFF
};

typedef cancellation_type cancellation_type_t;

<<<<<<< HEAD
#else // defined(ASIO_HAS_ENUM_CLASS)

namespace cancellation_type {

enum cancellation_type_t
{
  none = 0,
  terminal = 1,
  partial = 2,
  total = 4,
  all = 0xFFFFFFFF
};

} // namespace cancellation_type

typedef cancellation_type::cancellation_type_t cancellation_type_t;

#endif // defined(ASIO_HAS_ENUM_CLASS)
=======
#endif // defined(GENERATING_DOCUMENTATION)
>>>>>>> 142038d (add asio new version)

/// Negation operator.
/**
 * @relates cancellation_type
 */
<<<<<<< HEAD
inline ASIO_CONSTEXPR bool operator!(cancellation_type_t x)
=======
inline constexpr bool operator!(cancellation_type_t x)
>>>>>>> 142038d (add asio new version)
{
  return static_cast<unsigned int>(x) == 0;
}

/// Bitwise and operator.
/**
 * @relates cancellation_type
 */
<<<<<<< HEAD
inline ASIO_CONSTEXPR cancellation_type_t operator&(
=======
inline constexpr cancellation_type_t operator&(
>>>>>>> 142038d (add asio new version)
    cancellation_type_t x, cancellation_type_t y)
{
  return static_cast<cancellation_type_t>(
      static_cast<unsigned int>(x) & static_cast<unsigned int>(y));
}

/// Bitwise or operator.
/**
 * @relates cancellation_type
 */
<<<<<<< HEAD
inline ASIO_CONSTEXPR cancellation_type_t operator|(
=======
inline constexpr cancellation_type_t operator|(
>>>>>>> 142038d (add asio new version)
    cancellation_type_t x, cancellation_type_t y)
{
  return static_cast<cancellation_type_t>(
      static_cast<unsigned int>(x) | static_cast<unsigned int>(y));
}

/// Bitwise xor operator.
/**
 * @relates cancellation_type
 */
<<<<<<< HEAD
inline ASIO_CONSTEXPR cancellation_type_t operator^(
=======
inline constexpr cancellation_type_t operator^(
>>>>>>> 142038d (add asio new version)
    cancellation_type_t x, cancellation_type_t y)
{
  return static_cast<cancellation_type_t>(
      static_cast<unsigned int>(x) ^ static_cast<unsigned int>(y));
}

/// Bitwise negation operator.
/**
 * @relates cancellation_type
 */
<<<<<<< HEAD
inline ASIO_CONSTEXPR cancellation_type_t operator~(cancellation_type_t x)
=======
inline constexpr cancellation_type_t operator~(cancellation_type_t x)
>>>>>>> 142038d (add asio new version)
{
  return static_cast<cancellation_type_t>(~static_cast<unsigned int>(x));
}

/// Bitwise and-assignment operator.
/**
 * @relates cancellation_type
 */
inline cancellation_type_t& operator&=(
    cancellation_type_t& x, cancellation_type_t y)
{
  x = x & y;
  return x;
}

/// Bitwise or-assignment operator.
/**
 * @relates cancellation_type
 */
inline cancellation_type_t& operator|=(
    cancellation_type_t& x, cancellation_type_t y)
{
  x = x | y;
  return x;
}

/// Bitwise xor-assignment operator.
/**
 * @relates cancellation_type
 */
inline cancellation_type_t& operator^=(
    cancellation_type_t& x, cancellation_type_t y)
{
  x = x ^ y;
  return x;
}

} // namespace asio

#include "asio/detail/pop_options.hpp"

#endif // ASIO_CANCELLATION_TYPE_HPP
