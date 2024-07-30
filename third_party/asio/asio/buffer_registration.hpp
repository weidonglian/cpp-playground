//
// buffer_registration.hpp
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

#ifndef ASIO_BUFFER_REGISTRATION_HPP
#define ASIO_BUFFER_REGISTRATION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include "asio/detail/config.hpp"
#include <iterator>
<<<<<<< HEAD
=======
#include <utility>
>>>>>>> 142038d (add asio new version)
#include <vector>
#include "asio/detail/memory.hpp"
#include "asio/execution/context.hpp"
#include "asio/execution/executor.hpp"
#include "asio/execution_context.hpp"
#include "asio/is_executor.hpp"
#include "asio/query.hpp"
#include "asio/registered_buffer.hpp"

#if defined(ASIO_HAS_IO_URING)
# include "asio/detail/scheduler.hpp"
# include "asio/detail/io_uring_service.hpp"
#endif // defined(ASIO_HAS_IO_URING)

<<<<<<< HEAD
#if defined(ASIO_HAS_MOVE)
# include <utility>
#endif // defined(ASIO_HAS_MOVE)

=======
>>>>>>> 142038d (add asio new version)
#include "asio/detail/push_options.hpp"

namespace asio {
namespace detail {

class buffer_registration_base
{
protected:
  static mutable_registered_buffer make_buffer(const mutable_buffer& b,
<<<<<<< HEAD
      const void* scope, int index) ASIO_NOEXCEPT
=======
      const void* scope, int index) noexcept
>>>>>>> 142038d (add asio new version)
  {
    return mutable_registered_buffer(b, registered_buffer_id(scope, index));
  }
};

} // namespace detail

/// Automatically registers and unregistered buffers with an execution context.
/**
 * For portability, applications should assume that only one registration is
 * permitted per execution context.
 */
template <typename MutableBufferSequence,
<<<<<<< HEAD
    typename Allocator = std::allocator<void> >
=======
    typename Allocator = std::allocator<void>>
>>>>>>> 142038d (add asio new version)
class buffer_registration
  : detail::buffer_registration_base
{
public:
  /// The allocator type used for allocating storage for the buffers container.
  typedef Allocator allocator_type;

#if defined(GENERATING_DOCUMENTATION)
  /// The type of an iterator over the registered buffers.
  typedef unspecified iterator;

  /// The type of a const iterator over the registered buffers.
  typedef unspecified const_iterator;
#else // defined(GENERATING_DOCUMENTATION)
  typedef std::vector<mutable_registered_buffer>::const_iterator iterator;
  typedef std::vector<mutable_registered_buffer>::const_iterator const_iterator;
#endif // defined(GENERATING_DOCUMENTATION)

  /// Register buffers with an executor's execution context.
  template <typename Executor>
  buffer_registration(const Executor& ex,
      const MutableBufferSequence& buffer_sequence,
      const allocator_type& alloc = allocator_type(),
<<<<<<< HEAD
      typename constraint<
        is_executor<Executor>::value || execution::is_executor<Executor>::value
      >::type = 0)
=======
      constraint_t<
        is_executor<Executor>::value || execution::is_executor<Executor>::value
      > = 0)
>>>>>>> 142038d (add asio new version)
    : buffer_sequence_(buffer_sequence),
      buffers_(
          ASIO_REBIND_ALLOC(allocator_type,
            mutable_registered_buffer)(alloc))
  {
    init_buffers(buffer_registration::get_context(ex),
        asio::buffer_sequence_begin(buffer_sequence_),
        asio::buffer_sequence_end(buffer_sequence_));
  }

  /// Register buffers with an execution context.
  template <typename ExecutionContext>
  buffer_registration(ExecutionContext& ctx,
      const MutableBufferSequence& buffer_sequence,
      const allocator_type& alloc = allocator_type(),
<<<<<<< HEAD
      typename constraint<
        is_convertible<ExecutionContext&, execution_context&>::value
      >::type = 0)
=======
      constraint_t<
        is_convertible<ExecutionContext&, execution_context&>::value
      > = 0)
>>>>>>> 142038d (add asio new version)
    : buffer_sequence_(buffer_sequence),
      buffers_(
          ASIO_REBIND_ALLOC(allocator_type,
            mutable_registered_buffer)(alloc))
  {
    init_buffers(ctx,
        asio::buffer_sequence_begin(buffer_sequence_),
        asio::buffer_sequence_end(buffer_sequence_));
  }

<<<<<<< HEAD
#if defined(ASIO_HAS_MOVE) || defined(GENERATING_DOCUMENTATION)
  /// Move constructor.
  buffer_registration(buffer_registration&& other) ASIO_NOEXCEPT
=======
  /// Move constructor.
  buffer_registration(buffer_registration&& other) noexcept
>>>>>>> 142038d (add asio new version)
    : buffer_sequence_(std::move(other.buffer_sequence_)),
      buffers_(std::move(other.buffers_))
  {
#if defined(ASIO_HAS_IO_URING)
    service_ = other.service_;
    other.service_ = 0;
#endif // defined(ASIO_HAS_IO_URING)
  }
<<<<<<< HEAD
#endif // defined(ASIO_HAS_MOVE) || defined(GENERATING_DOCUMENTATION)
=======
>>>>>>> 142038d (add asio new version)

  /// Unregisters the buffers.
  ~buffer_registration()
  {
#if defined(ASIO_HAS_IO_URING)
    if (service_)
      service_->unregister_buffers();
#endif // defined(ASIO_HAS_IO_URING)
  }
<<<<<<< HEAD
  
#if defined(ASIO_HAS_MOVE) || defined(GENERATING_DOCUMENTATION)
  /// Move assignment.
  buffer_registration& operator=(
      buffer_registration&& other) ASIO_NOEXCEPT
=======

  /// Move assignment.
  buffer_registration& operator=(buffer_registration&& other) noexcept
>>>>>>> 142038d (add asio new version)
  {
    if (this != &other)
    {
      buffer_sequence_ = std::move(other.buffer_sequence_);
      buffers_ = std::move(other.buffers_);
#if defined(ASIO_HAS_IO_URING)
      if (service_)
        service_->unregister_buffers();
      service_ = other.service_;
      other.service_ = 0;
#endif // defined(ASIO_HAS_IO_URING)
    }
    return *this;
  }
<<<<<<< HEAD
#endif // defined(ASIO_HAS_MOVE) || defined(GENERATING_DOCUMENTATION)

  /// Get the number of registered buffers.
  std::size_t size() const ASIO_NOEXCEPT
=======

  /// Get the number of registered buffers.
  std::size_t size() const noexcept
>>>>>>> 142038d (add asio new version)
  {
    return buffers_.size();
  }

  /// Get the begin iterator for the sequence of registered buffers.
<<<<<<< HEAD
  const_iterator begin() const ASIO_NOEXCEPT
=======
  const_iterator begin() const noexcept
>>>>>>> 142038d (add asio new version)
  {
    return buffers_.begin();
  }

  /// Get the begin iterator for the sequence of registered buffers.
<<<<<<< HEAD
  const_iterator cbegin() const ASIO_NOEXCEPT
=======
  const_iterator cbegin() const noexcept
>>>>>>> 142038d (add asio new version)
  {
    return buffers_.cbegin();
  }

  /// Get the end iterator for the sequence of registered buffers.
<<<<<<< HEAD
  const_iterator end() const ASIO_NOEXCEPT
=======
  const_iterator end() const noexcept
>>>>>>> 142038d (add asio new version)
  {
    return buffers_.end();
  }

  /// Get the end iterator for the sequence of registered buffers.
<<<<<<< HEAD
  const_iterator cend() const ASIO_NOEXCEPT
=======
  const_iterator cend() const noexcept
>>>>>>> 142038d (add asio new version)
  {
    return buffers_.cend();
  }

  /// Get the buffer at the specified index.
<<<<<<< HEAD
  const mutable_registered_buffer& operator[](std::size_t i) ASIO_NOEXCEPT
=======
  const mutable_registered_buffer& operator[](std::size_t i) noexcept
>>>>>>> 142038d (add asio new version)
  {
    return buffers_[i];
  }

  /// Get the buffer at the specified index.
<<<<<<< HEAD
  const mutable_registered_buffer& at(std::size_t i) ASIO_NOEXCEPT
=======
  const mutable_registered_buffer& at(std::size_t i) noexcept
>>>>>>> 142038d (add asio new version)
  {
    return buffers_.at(i);
  }

private:
  // Disallow copying and assignment.
<<<<<<< HEAD
  buffer_registration(const buffer_registration&) ASIO_DELETED;
  buffer_registration& operator=(const buffer_registration&) ASIO_DELETED;
=======
  buffer_registration(const buffer_registration&) = delete;
  buffer_registration& operator=(const buffer_registration&) = delete;
>>>>>>> 142038d (add asio new version)

  // Helper function to get an executor's context.
  template <typename T>
  static execution_context& get_context(const T& t,
<<<<<<< HEAD
      typename enable_if<execution::is_executor<T>::value>::type* = 0)
=======
      enable_if_t<execution::is_executor<T>::value>* = 0)
>>>>>>> 142038d (add asio new version)
  {
    return asio::query(t, execution::context);
  }

  // Helper function to get an executor's context.
  template <typename T>
  static execution_context& get_context(const T& t,
<<<<<<< HEAD
      typename enable_if<!execution::is_executor<T>::value>::type* = 0)
=======
      enable_if_t<!execution::is_executor<T>::value>* = 0)
>>>>>>> 142038d (add asio new version)
  {
    return t.context();
  }

  // Helper function to initialise the container of buffers.
  template <typename Iterator>
  void init_buffers(execution_context& ctx, Iterator begin, Iterator end)
  {
    std::size_t n = std::distance(begin, end);
    buffers_.resize(n);

#if defined(ASIO_HAS_IO_URING)
    service_ = &use_service<detail::io_uring_service>(ctx);
    std::vector<iovec,
      ASIO_REBIND_ALLOC(allocator_type, iovec)> iovecs(n,
          ASIO_REBIND_ALLOC(allocator_type, iovec)(
            buffers_.get_allocator()));
#endif // defined(ASIO_HAS_IO_URING)

    Iterator iter = begin;
    for (int index = 0; iter != end; ++index, ++iter)
    {
      mutable_buffer b(*iter);
      std::size_t i = static_cast<std::size_t>(index);
      buffers_[i] = this->make_buffer(b, &ctx, index);

#if defined(ASIO_HAS_IO_URING)
      iovecs[i].iov_base = buffers_[i].data();
      iovecs[i].iov_len = buffers_[i].size();
#endif // defined(ASIO_HAS_IO_URING)
    }

#if defined(ASIO_HAS_IO_URING)
    if (n > 0)
    {
      service_->register_buffers(&iovecs[0],
          static_cast<unsigned>(iovecs.size()));
    }
#endif // defined(ASIO_HAS_IO_URING)
  }

  MutableBufferSequence buffer_sequence_;
  std::vector<mutable_registered_buffer,
    ASIO_REBIND_ALLOC(allocator_type,
      mutable_registered_buffer)> buffers_;
#if defined(ASIO_HAS_IO_URING)
  detail::io_uring_service* service_;
#endif // defined(ASIO_HAS_IO_URING)
};

<<<<<<< HEAD
#if defined(ASIO_HAS_MOVE) || defined(GENERATING_DOCUMENTATION)
=======
>>>>>>> 142038d (add asio new version)
/// Register buffers with an execution context.
template <typename Executor, typename MutableBufferSequence>
ASIO_NODISCARD inline
buffer_registration<MutableBufferSequence>
register_buffers(const Executor& ex,
    const MutableBufferSequence& buffer_sequence,
<<<<<<< HEAD
    typename constraint<
      is_executor<Executor>::value || execution::is_executor<Executor>::value
    >::type = 0)
=======
    constraint_t<
      is_executor<Executor>::value || execution::is_executor<Executor>::value
    > = 0)
>>>>>>> 142038d (add asio new version)
{
  return buffer_registration<MutableBufferSequence>(ex, buffer_sequence);
}

/// Register buffers with an execution context.
template <typename Executor, typename MutableBufferSequence, typename Allocator>
ASIO_NODISCARD inline
buffer_registration<MutableBufferSequence, Allocator>
register_buffers(const Executor& ex,
    const MutableBufferSequence& buffer_sequence, const Allocator& alloc,
<<<<<<< HEAD
    typename constraint<
      is_executor<Executor>::value || execution::is_executor<Executor>::value
    >::type = 0)
=======
    constraint_t<
      is_executor<Executor>::value || execution::is_executor<Executor>::value
    > = 0)
>>>>>>> 142038d (add asio new version)
{
  return buffer_registration<MutableBufferSequence, Allocator>(
      ex, buffer_sequence, alloc);
}

/// Register buffers with an execution context.
template <typename ExecutionContext, typename MutableBufferSequence>
ASIO_NODISCARD inline
buffer_registration<MutableBufferSequence>
register_buffers(ExecutionContext& ctx,
    const MutableBufferSequence& buffer_sequence,
<<<<<<< HEAD
    typename constraint<
      is_convertible<ExecutionContext&, execution_context&>::value
    >::type = 0)
=======
    constraint_t<
      is_convertible<ExecutionContext&, execution_context&>::value
    > = 0)
>>>>>>> 142038d (add asio new version)
{
  return buffer_registration<MutableBufferSequence>(ctx, buffer_sequence);
}

/// Register buffers with an execution context.
template <typename ExecutionContext,
    typename MutableBufferSequence, typename Allocator>
ASIO_NODISCARD inline
buffer_registration<MutableBufferSequence, Allocator>
register_buffers(ExecutionContext& ctx,
    const MutableBufferSequence& buffer_sequence, const Allocator& alloc,
<<<<<<< HEAD
    typename constraint<
      is_convertible<ExecutionContext&, execution_context&>::value
    >::type = 0)
=======
    constraint_t<
      is_convertible<ExecutionContext&, execution_context&>::value
    > = 0)
>>>>>>> 142038d (add asio new version)
{
  return buffer_registration<MutableBufferSequence, Allocator>(
      ctx, buffer_sequence, alloc);
}
<<<<<<< HEAD
#endif // defined(ASIO_HAS_MOVE) || defined(GENERATING_DOCUMENTATION)
=======
>>>>>>> 142038d (add asio new version)

} // namespace asio

#include "asio/detail/pop_options.hpp"

#endif // ASIO_BUFFER_REGISTRATION_HPP
