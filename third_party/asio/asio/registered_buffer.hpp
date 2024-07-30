//
// registered_buffer.hpp
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

#ifndef ASIO_REGISTERED_BUFFER_HPP
#define ASIO_REGISTERED_BUFFER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include "asio/detail/config.hpp"
#include "asio/buffer.hpp"

#include "asio/detail/push_options.hpp"

namespace asio {
namespace detail {

class buffer_registration_base;

} // namespace detail

class const_registered_buffer;

/// Type used to identify a registered buffer.
class registered_buffer_id
{
public:
  /// The native buffer identifier type.
  typedef int native_handle_type;

  /// Default constructor creates an invalid registered buffer identifier.
<<<<<<< HEAD
  registered_buffer_id() ASIO_NOEXCEPT
=======
  registered_buffer_id() noexcept
>>>>>>> 142038d (add asio new version)
    : scope_(0),
      index_(-1)
  {
  }

  /// Get the native buffer identifier type.
<<<<<<< HEAD
  native_handle_type native_handle() const ASIO_NOEXCEPT
=======
  native_handle_type native_handle() const noexcept
>>>>>>> 142038d (add asio new version)
  {
    return index_;
  }

  /// Compare two IDs for equality.
  friend bool operator==(const registered_buffer_id& lhs,
<<<<<<< HEAD
      const registered_buffer_id& rhs) ASIO_NOEXCEPT
=======
      const registered_buffer_id& rhs) noexcept
>>>>>>> 142038d (add asio new version)
  {
    return lhs.scope_ == rhs.scope_ && lhs.index_ == rhs.index_;
  }

  /// Compare two IDs for equality.
  friend bool operator!=(const registered_buffer_id& lhs,
<<<<<<< HEAD
      const registered_buffer_id& rhs) ASIO_NOEXCEPT
=======
      const registered_buffer_id& rhs) noexcept
>>>>>>> 142038d (add asio new version)
  {
    return lhs.scope_ != rhs.scope_ || lhs.index_ != rhs.index_;
  }

private:
  friend class detail::buffer_registration_base;

  // Hidden constructor used by buffer registration.
<<<<<<< HEAD
  registered_buffer_id(const void* scope, int index) ASIO_NOEXCEPT
=======
  registered_buffer_id(const void* scope, int index) noexcept
>>>>>>> 142038d (add asio new version)
    : scope_(scope),
      index_(index)
  {
  }

  const void* scope_;
  int index_;
};

/// Holds a registered buffer over modifiable data.
<<<<<<< HEAD
/** 
=======
/**
>>>>>>> 142038d (add asio new version)
 * Satisfies the @c MutableBufferSequence type requirements.
 */
class mutable_registered_buffer
{
public:
<<<<<<< HEAD
#if !defined(ASIO_HAS_DECLTYPE) \
  && !defined(GENERATING_DOCUMENTATION)
  typedef mutable_buffer value_type;
#endif // !defined(ASIO_HAS_DECLTYPE)
       //   && !defined(GENERATING_DOCUMENTATION)

  /// Default constructor creates an invalid registered buffer.
  mutable_registered_buffer() ASIO_NOEXCEPT
=======
  /// Default constructor creates an invalid registered buffer.
  mutable_registered_buffer() noexcept
>>>>>>> 142038d (add asio new version)
    : buffer_(),
      id_()
  {
  }

  /// Get the underlying mutable buffer.
<<<<<<< HEAD
  const mutable_buffer& buffer() const ASIO_NOEXCEPT
=======
  const mutable_buffer& buffer() const noexcept
>>>>>>> 142038d (add asio new version)
  {
    return buffer_;
  }

  /// Get a pointer to the beginning of the memory range.
  /**
   * @returns <tt>buffer().data()</tt>.
   */
<<<<<<< HEAD
  void* data() const ASIO_NOEXCEPT
=======
  void* data() const noexcept
>>>>>>> 142038d (add asio new version)
  {
    return buffer_.data();
  }

  /// Get the size of the memory range.
  /**
   * @returns <tt>buffer().size()</tt>.
   */
<<<<<<< HEAD
  std::size_t size() const ASIO_NOEXCEPT
=======
  std::size_t size() const noexcept
>>>>>>> 142038d (add asio new version)
  {
    return buffer_.size();
  }

  /// Get the registered buffer identifier.
<<<<<<< HEAD
  const registered_buffer_id& id() const ASIO_NOEXCEPT
=======
  const registered_buffer_id& id() const noexcept
>>>>>>> 142038d (add asio new version)
  {
    return id_;
  }

  /// Move the start of the buffer by the specified number of bytes.
<<<<<<< HEAD
  mutable_registered_buffer& operator+=(std::size_t n) ASIO_NOEXCEPT
=======
  mutable_registered_buffer& operator+=(std::size_t n) noexcept
>>>>>>> 142038d (add asio new version)
  {
    buffer_ += n;
    return *this;
  }

private:
  friend class detail::buffer_registration_base;

  // Hidden constructor used by buffer registration and operators.
  mutable_registered_buffer(const mutable_buffer& b,
<<<<<<< HEAD
      const registered_buffer_id& i) ASIO_NOEXCEPT
=======
      const registered_buffer_id& i) noexcept
>>>>>>> 142038d (add asio new version)
    : buffer_(b),
      id_(i)
  {
  }

#if !defined(GENERATING_DOCUMENTATION)
  friend mutable_registered_buffer buffer(
<<<<<<< HEAD
      const mutable_registered_buffer& b, std::size_t n) ASIO_NOEXCEPT;
=======
      const mutable_registered_buffer& b, std::size_t n) noexcept;
>>>>>>> 142038d (add asio new version)
#endif // !defined(GENERATING_DOCUMENTATION)

  mutable_buffer buffer_;
  registered_buffer_id id_;
};

/// Holds a registered buffer over non-modifiable data.
<<<<<<< HEAD
/** 
=======
/**
>>>>>>> 142038d (add asio new version)
 * Satisfies the @c ConstBufferSequence type requirements.
 */
class const_registered_buffer
{
public:
<<<<<<< HEAD
#if !defined(ASIO_HAS_DECLTYPE) \
  && !defined(GENERATING_DOCUMENTATION)
  typedef const_buffer value_type;
#endif // !defined(ASIO_HAS_DECLTYPE)
       //   && !defined(GENERATING_DOCUMENTATION)

  /// Default constructor creates an invalid registered buffer.
  const_registered_buffer() ASIO_NOEXCEPT
=======
  /// Default constructor creates an invalid registered buffer.
  const_registered_buffer() noexcept
>>>>>>> 142038d (add asio new version)
    : buffer_(),
      id_()
  {
  }

  /// Construct a non-modifiable buffer from a modifiable one.
  const_registered_buffer(
<<<<<<< HEAD
      const mutable_registered_buffer& b) ASIO_NOEXCEPT
=======
      const mutable_registered_buffer& b) noexcept
>>>>>>> 142038d (add asio new version)
    : buffer_(b.buffer()),
      id_(b.id())
  {
  }

  /// Get the underlying constant buffer.
<<<<<<< HEAD
  const const_buffer& buffer() const ASIO_NOEXCEPT
=======
  const const_buffer& buffer() const noexcept
>>>>>>> 142038d (add asio new version)
  {
    return buffer_;
  }

  /// Get a pointer to the beginning of the memory range.
  /**
   * @returns <tt>buffer().data()</tt>.
   */
<<<<<<< HEAD
  const void* data() const ASIO_NOEXCEPT
=======
  const void* data() const noexcept
>>>>>>> 142038d (add asio new version)
  {
    return buffer_.data();
  }

  /// Get the size of the memory range.
  /**
   * @returns <tt>buffer().size()</tt>.
   */
<<<<<<< HEAD
  std::size_t size() const ASIO_NOEXCEPT
=======
  std::size_t size() const noexcept
>>>>>>> 142038d (add asio new version)
  {
    return buffer_.size();
  }

  /// Get the registered buffer identifier.
<<<<<<< HEAD
  const registered_buffer_id& id() const ASIO_NOEXCEPT
=======
  const registered_buffer_id& id() const noexcept
>>>>>>> 142038d (add asio new version)
  {
    return id_;
  }

  /// Move the start of the buffer by the specified number of bytes.
<<<<<<< HEAD
  const_registered_buffer& operator+=(std::size_t n) ASIO_NOEXCEPT
=======
  const_registered_buffer& operator+=(std::size_t n) noexcept
>>>>>>> 142038d (add asio new version)
  {
    buffer_ += n;
    return *this;
  }

private:
  // Hidden constructor used by operators.
  const_registered_buffer(const const_buffer& b,
<<<<<<< HEAD
      const registered_buffer_id& i) ASIO_NOEXCEPT
=======
      const registered_buffer_id& i) noexcept
>>>>>>> 142038d (add asio new version)
    : buffer_(b),
      id_(i)
  {
  }

#if !defined(GENERATING_DOCUMENTATION)
  friend const_registered_buffer buffer(
<<<<<<< HEAD
      const const_registered_buffer& b, std::size_t n) ASIO_NOEXCEPT;
=======
      const const_registered_buffer& b, std::size_t n) noexcept;
>>>>>>> 142038d (add asio new version)
#endif // !defined(GENERATING_DOCUMENTATION)

  const_buffer buffer_;
  registered_buffer_id id_;
};

/** @addtogroup buffer_sequence_begin */

/// Get an iterator to the first element in a buffer sequence.
inline const mutable_buffer* buffer_sequence_begin(
<<<<<<< HEAD
    const mutable_registered_buffer& b) ASIO_NOEXCEPT
=======
    const mutable_registered_buffer& b) noexcept
>>>>>>> 142038d (add asio new version)
{
  return &b.buffer();
}

/// Get an iterator to the first element in a buffer sequence.
inline const const_buffer* buffer_sequence_begin(
<<<<<<< HEAD
    const const_registered_buffer& b) ASIO_NOEXCEPT
=======
    const const_registered_buffer& b) noexcept
>>>>>>> 142038d (add asio new version)
{
  return &b.buffer();
}

/** @} */
/** @addtogroup buffer_sequence_end */

/// Get an iterator to one past the end element in a buffer sequence.
inline const mutable_buffer* buffer_sequence_end(
<<<<<<< HEAD
    const mutable_registered_buffer& b) ASIO_NOEXCEPT
=======
    const mutable_registered_buffer& b) noexcept
>>>>>>> 142038d (add asio new version)
{
  return &b.buffer() + 1;
}

/// Get an iterator to one past the end element in a buffer sequence.
inline const const_buffer* buffer_sequence_end(
<<<<<<< HEAD
    const const_registered_buffer& b) ASIO_NOEXCEPT
=======
    const const_registered_buffer& b) noexcept
>>>>>>> 142038d (add asio new version)
{
  return &b.buffer() + 1;
}

/** @} */
/** @addtogroup buffer */

/// Obtain a buffer representing the entire registered buffer.
inline mutable_registered_buffer buffer(
<<<<<<< HEAD
    const mutable_registered_buffer& b) ASIO_NOEXCEPT
=======
    const mutable_registered_buffer& b) noexcept
>>>>>>> 142038d (add asio new version)
{
  return b;
}

/// Obtain a buffer representing the entire registered buffer.
inline const_registered_buffer buffer(
<<<<<<< HEAD
    const const_registered_buffer& b) ASIO_NOEXCEPT
=======
    const const_registered_buffer& b) noexcept
>>>>>>> 142038d (add asio new version)
{
  return b;
}

/// Obtain a buffer representing part of a registered buffer.
inline mutable_registered_buffer buffer(
<<<<<<< HEAD
    const mutable_registered_buffer& b, std::size_t n) ASIO_NOEXCEPT
=======
    const mutable_registered_buffer& b, std::size_t n) noexcept
>>>>>>> 142038d (add asio new version)
{
  return mutable_registered_buffer(buffer(b.buffer_, n), b.id_);
}

/// Obtain a buffer representing part of a registered buffer.
inline const_registered_buffer buffer(
<<<<<<< HEAD
    const const_registered_buffer& b, std::size_t n) ASIO_NOEXCEPT
=======
    const const_registered_buffer& b, std::size_t n) noexcept
>>>>>>> 142038d (add asio new version)
{
  return const_registered_buffer(buffer(b.buffer_, n), b.id_);
}

/** @} */

/// Create a new modifiable registered buffer that is offset from the start of
/// another.
/**
 * @relates mutable_registered_buffer
 */
inline mutable_registered_buffer operator+(
<<<<<<< HEAD
    const mutable_registered_buffer& b, std::size_t n) ASIO_NOEXCEPT
=======
    const mutable_registered_buffer& b, std::size_t n) noexcept
>>>>>>> 142038d (add asio new version)
{
  mutable_registered_buffer tmp(b);
  tmp += n;
  return tmp;
}

/// Create a new modifiable buffer that is offset from the start of another.
/**
 * @relates mutable_registered_buffer
 */
inline mutable_registered_buffer operator+(std::size_t n,
<<<<<<< HEAD
    const mutable_registered_buffer& b) ASIO_NOEXCEPT
=======
    const mutable_registered_buffer& b) noexcept
>>>>>>> 142038d (add asio new version)
{
  return b + n;
}

/// Create a new non-modifiable registered buffer that is offset from the start
/// of another.
/**
 * @relates const_registered_buffer
 */
inline const_registered_buffer operator+(const const_registered_buffer& b,
<<<<<<< HEAD
    std::size_t n) ASIO_NOEXCEPT
=======
    std::size_t n) noexcept
>>>>>>> 142038d (add asio new version)
{
  const_registered_buffer tmp(b);
  tmp += n;
  return tmp;
}

/// Create a new non-modifiable buffer that is offset from the start of another.
/**
 * @relates const_registered_buffer
 */
inline const_registered_buffer operator+(std::size_t n,
<<<<<<< HEAD
    const const_registered_buffer& b) ASIO_NOEXCEPT
=======
    const const_registered_buffer& b) noexcept
>>>>>>> 142038d (add asio new version)
{
  return b + n;
}

} // namespace asio

#include "asio/detail/pop_options.hpp"

#endif // ASIO_REGISTERED_BUFFER_HPP
