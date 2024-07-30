//
// cancellation_signal.hpp
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

#ifndef ASIO_CANCELLATION_SIGNAL_HPP
#define ASIO_CANCELLATION_SIGNAL_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include "asio/detail/config.hpp"
#include <cassert>
#include <new>
#include <utility>
#include "asio/cancellation_type.hpp"
#include "asio/detail/cstddef.hpp"
#include "asio/detail/type_traits.hpp"
<<<<<<< HEAD
#include "asio/detail/variadic_templates.hpp"
=======
>>>>>>> 142038d (add asio new version)

#include "asio/detail/push_options.hpp"

namespace asio {
namespace detail {

class cancellation_handler_base
{
public:
  virtual void call(cancellation_type_t) = 0;
<<<<<<< HEAD
  virtual std::pair<void*, std::size_t> destroy() ASIO_NOEXCEPT = 0;
=======
  virtual std::pair<void*, std::size_t> destroy() noexcept = 0;
>>>>>>> 142038d (add asio new version)

protected:
  ~cancellation_handler_base() {}
};

template <typename Handler>
class cancellation_handler
  : public cancellation_handler_base
{
public:
<<<<<<< HEAD
#if defined(ASIO_HAS_VARIADIC_TEMPLATES)
  template <typename... Args>
  cancellation_handler(std::size_t size, ASIO_MOVE_ARG(Args)... args)
    : handler_(ASIO_MOVE_CAST(Args)(args)...),
      size_(size)
  {
  }
#else // defined(ASIO_HAS_VARIADIC_TEMPLATES)
  cancellation_handler(std::size_t size)
    : handler_(),
      size_(size)
  {
  }

#define ASIO_PRIVATE_HANDLER_CTOR_DEF(n) \
  template <ASIO_VARIADIC_TPARAMS(n)> \
  cancellation_handler(std::size_t size, ASIO_VARIADIC_MOVE_PARAMS(n)) \
    : handler_(ASIO_VARIADIC_MOVE_ARGS(n)), \
      size_(size) \
  { \
  } \
  /**/
  ASIO_VARIADIC_GENERATE(ASIO_PRIVATE_HANDLER_CTOR_DEF)
#undef ASIO_PRIVATE_HANDLER_CTOR_DEF
#endif // defined(ASIO_HAS_VARIADIC_TEMPLATES)
=======
  template <typename... Args>
  cancellation_handler(std::size_t size, Args&&... args)
    : handler_(static_cast<Args&&>(args)...),
      size_(size)
  {
  }
>>>>>>> 142038d (add asio new version)

  void call(cancellation_type_t type)
  {
    handler_(type);
  }

<<<<<<< HEAD
  std::pair<void*, std::size_t> destroy() ASIO_NOEXCEPT
=======
  std::pair<void*, std::size_t> destroy() noexcept
>>>>>>> 142038d (add asio new version)
  {
    std::pair<void*, std::size_t> mem(this, size_);
    this->cancellation_handler::~cancellation_handler();
    return mem;
  }

<<<<<<< HEAD
  Handler& handler() ASIO_NOEXCEPT
=======
  Handler& handler() noexcept
>>>>>>> 142038d (add asio new version)
  {
    return handler_;
  }

private:
  ~cancellation_handler()
  {
  }

  Handler handler_;
  std::size_t size_;
};

} // namespace detail

class cancellation_slot;

/// A cancellation signal with a single slot.
class cancellation_signal
{
public:
<<<<<<< HEAD
  ASIO_CONSTEXPR cancellation_signal()
=======
  constexpr cancellation_signal()
>>>>>>> 142038d (add asio new version)
    : handler_(0)
  {
  }

  ASIO_DECL ~cancellation_signal();

  /// Emits the signal and causes invocation of the slot's handler, if any.
  void emit(cancellation_type_t type)
  {
    if (handler_)
      handler_->call(type);
  }

  /// Returns the single slot associated with the signal.
  /**
   * The signal object must remain valid for as long the slot may be used.
   * Destruction of the signal invalidates the slot.
   */
<<<<<<< HEAD
  cancellation_slot slot() ASIO_NOEXCEPT;

private:
  cancellation_signal(const cancellation_signal&) ASIO_DELETED;
  cancellation_signal& operator=(const cancellation_signal&) ASIO_DELETED;
=======
  cancellation_slot slot() noexcept;

private:
  cancellation_signal(const cancellation_signal&) = delete;
  cancellation_signal& operator=(const cancellation_signal&) = delete;
>>>>>>> 142038d (add asio new version)

  detail::cancellation_handler_base* handler_;
};

/// A slot associated with a cancellation signal.
class cancellation_slot
{
public:
  /// Creates a slot that is not connected to any cancellation signal.
<<<<<<< HEAD
  ASIO_CONSTEXPR cancellation_slot()
=======
  constexpr cancellation_slot()
>>>>>>> 142038d (add asio new version)
    : handler_(0)
  {
  }

<<<<<<< HEAD
#if defined(ASIO_HAS_VARIADIC_TEMPLATES) \
  || defined(GENERATING_DOCUMENTATION)
=======
>>>>>>> 142038d (add asio new version)
  /// Installs a handler into the slot, constructing the new object directly.
  /**
   * Destroys any existing handler in the slot, then installs the new handler,
   * constructing it with the supplied @c args.
   *
   * The handler is a function object to be called when the signal is emitted.
   * The signature of the handler must be
   * @code void handler(asio::cancellation_type_t); @endcode
   *
   * @param args Arguments to be passed to the @c CancellationHandler object's
   * constructor.
   *
   * @returns A reference to the newly installed handler.
   *
   * @note Handlers installed into the slot via @c emplace are not required to
   * be copy constructible or move constructible.
   */
  template <typename CancellationHandler, typename... Args>
<<<<<<< HEAD
  CancellationHandler& emplace(ASIO_MOVE_ARG(Args)... args)
=======
  CancellationHandler& emplace(Args&&... args)
>>>>>>> 142038d (add asio new version)
  {
    typedef detail::cancellation_handler<CancellationHandler>
      cancellation_handler_type;
    auto_delete_helper del = { prepare_memory(
        sizeof(cancellation_handler_type),
<<<<<<< HEAD
        ASIO_ALIGNOF(CancellationHandler)) };
    cancellation_handler_type* handler_obj =
      new (del.mem.first) cancellation_handler_type(
        del.mem.second, ASIO_MOVE_CAST(Args)(args)...);
=======
        alignof(CancellationHandler)) };
    cancellation_handler_type* handler_obj =
      new (del.mem.first) cancellation_handler_type(
        del.mem.second, static_cast<Args&&>(args)...);
>>>>>>> 142038d (add asio new version)
    del.mem.first = 0;
    *handler_ = handler_obj;
    return handler_obj->handler();
  }
<<<<<<< HEAD
#else // defined(ASIO_HAS_VARIADIC_TEMPLATES)
      //   || defined(GENERATING_DOCUMENTATION)
  template <typename CancellationHandler>
  CancellationHandler& emplace()
  {
    typedef detail::cancellation_handler<CancellationHandler>
      cancellation_handler_type;
    auto_delete_helper del = { prepare_memory(
        sizeof(cancellation_handler_type),
        ASIO_ALIGNOF(CancellationHandler)) };
    cancellation_handler_type* handler_obj =
      new (del.mem.first) cancellation_handler_type(del.mem.second);
    del.mem.first = 0;
    *handler_ = handler_obj;
    return handler_obj->handler();
  }

#define ASIO_PRIVATE_HANDLER_EMPLACE_DEF(n) \
  template <typename CancellationHandler, ASIO_VARIADIC_TPARAMS(n)> \
  CancellationHandler& emplace(ASIO_VARIADIC_MOVE_PARAMS(n)) \
  { \
    typedef detail::cancellation_handler<CancellationHandler> \
      cancellation_handler_type; \
    auto_delete_helper del = { prepare_memory( \
        sizeof(cancellation_handler_type), \
        ASIO_ALIGNOF(CancellationHandler)) }; \
    cancellation_handler_type* handler_obj = \
      new (del.mem.first) cancellation_handler_type( \
        del.mem.second, ASIO_VARIADIC_MOVE_ARGS(n)); \
    del.mem.first = 0; \
    *handler_ = handler_obj; \
    return handler_obj->handler(); \
  } \
  /**/
  ASIO_VARIADIC_GENERATE(ASIO_PRIVATE_HANDLER_EMPLACE_DEF)
#undef ASIO_PRIVATE_HANDLER_EMPLACE_DEF
#endif // defined(ASIO_HAS_VARIADIC_TEMPLATES)
=======
>>>>>>> 142038d (add asio new version)

  /// Installs a handler into the slot.
  /**
   * Destroys any existing handler in the slot, then installs the new handler,
   * constructing it as a decay-copy of the supplied handler.
   *
   * The handler is a function object to be called when the signal is emitted.
   * The signature of the handler must be
   * @code void handler(asio::cancellation_type_t); @endcode
   *
   * @param handler The handler to be installed.
   *
   * @returns A reference to the newly installed handler.
   */
  template <typename CancellationHandler>
<<<<<<< HEAD
  typename decay<CancellationHandler>::type& assign(
      ASIO_MOVE_ARG(CancellationHandler) handler)
  {
    return this->emplace<typename decay<CancellationHandler>::type>(
        ASIO_MOVE_CAST(CancellationHandler)(handler));
=======
  decay_t<CancellationHandler>& assign(CancellationHandler&& handler)
  {
    return this->emplace<decay_t<CancellationHandler>>(
        static_cast<CancellationHandler&&>(handler));
>>>>>>> 142038d (add asio new version)
  }

  /// Clears the slot.
  /**
   * Destroys any existing handler in the slot.
   */
  ASIO_DECL void clear();

  /// Returns whether the slot is connected to a signal.
<<<<<<< HEAD
  ASIO_CONSTEXPR bool is_connected() const ASIO_NOEXCEPT
=======
  constexpr bool is_connected() const noexcept
>>>>>>> 142038d (add asio new version)
  {
    return handler_ != 0;
  }

  /// Returns whether the slot is connected and has an installed handler.
<<<<<<< HEAD
  ASIO_CONSTEXPR bool has_handler() const ASIO_NOEXCEPT
=======
  constexpr bool has_handler() const noexcept
>>>>>>> 142038d (add asio new version)
  {
    return handler_ != 0 && *handler_ != 0;
  }

  /// Compare two slots for equality.
<<<<<<< HEAD
  friend ASIO_CONSTEXPR bool operator==(const cancellation_slot& lhs,
      const cancellation_slot& rhs) ASIO_NOEXCEPT
=======
  friend constexpr bool operator==(const cancellation_slot& lhs,
      const cancellation_slot& rhs) noexcept
>>>>>>> 142038d (add asio new version)
  {
    return lhs.handler_ == rhs.handler_;
  }

  /// Compare two slots for inequality.
<<<<<<< HEAD
  friend ASIO_CONSTEXPR bool operator!=(const cancellation_slot& lhs,
      const cancellation_slot& rhs) ASIO_NOEXCEPT
=======
  friend constexpr bool operator!=(const cancellation_slot& lhs,
      const cancellation_slot& rhs) noexcept
>>>>>>> 142038d (add asio new version)
  {
    return lhs.handler_ != rhs.handler_;
  }

private:
  friend class cancellation_signal;

<<<<<<< HEAD
  ASIO_CONSTEXPR cancellation_slot(int,
=======
  constexpr cancellation_slot(int,
>>>>>>> 142038d (add asio new version)
      detail::cancellation_handler_base** handler)
    : handler_(handler)
  {
  }

  ASIO_DECL std::pair<void*, std::size_t> prepare_memory(
      std::size_t size, std::size_t align);

  struct auto_delete_helper
  {
    std::pair<void*, std::size_t> mem;

    ASIO_DECL ~auto_delete_helper();
  };

  detail::cancellation_handler_base** handler_;
};

<<<<<<< HEAD
inline cancellation_slot cancellation_signal::slot() ASIO_NOEXCEPT
=======
inline cancellation_slot cancellation_signal::slot() noexcept
>>>>>>> 142038d (add asio new version)
{
  return cancellation_slot(0, &handler_);
}

} // namespace asio

#include "asio/detail/pop_options.hpp"

#if defined(ASIO_HEADER_ONLY)
# include "asio/impl/cancellation_signal.ipp"
#endif // defined(ASIO_HEADER_ONLY)

#endif // ASIO_CANCELLATION_SIGNAL_HPP
