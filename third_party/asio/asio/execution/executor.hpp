//
// execution/executor.hpp
// ~~~~~~~~~~~~~~~~~~~~~~
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

#ifndef ASIO_EXECUTION_EXECUTOR_HPP
#define ASIO_EXECUTION_EXECUTOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include "asio/detail/config.hpp"
#include "asio/detail/type_traits.hpp"
#include "asio/execution/invocable_archetype.hpp"
#include "asio/traits/equality_comparable.hpp"
#include "asio/traits/execute_member.hpp"

#if defined(ASIO_HAS_DEDUCED_EXECUTE_MEMBER_TRAIT) \
  && defined(ASIO_HAS_DEDUCED_EQUALITY_COMPARABLE_TRAIT)
# define ASIO_HAS_DEDUCED_EXECUTION_IS_EXECUTOR_TRAIT 1
#endif // defined(ASIO_HAS_DEDUCED_EXECUTE_MEMBER_TRAIT)
       //   && defined(ASIO_HAS_DEDUCED_EQUALITY_COMPARABLE_TRAIT)

#include "asio/detail/push_options.hpp"

namespace asio {
namespace execution {
namespace detail {

template <typename T, typename F,
    typename = void, typename = void, typename = void, typename = void,
    typename = void, typename = void, typename = void, typename = void>
struct is_executor_of_impl : false_type
{
};

template <typename T, typename F>
struct is_executor_of_impl<T, F,
<<<<<<< HEAD
  typename enable_if<
    can_execute<typename add_const<T>::type, F>::value
  >::type,
  typename void_type<
    typename result_of<typename decay<F>::type&()>::type
  >::type,
  typename enable_if<
    is_constructible<typename decay<F>::type, F>::value
  >::type,
  typename enable_if<
    is_move_constructible<typename decay<F>::type>::value
  >::type,
#if defined(ASIO_HAS_NOEXCEPT)
  typename enable_if<
    is_nothrow_copy_constructible<T>::value
  >::type,
  typename enable_if<
    is_nothrow_destructible<T>::value
  >::type,
#else // defined(ASIO_HAS_NOEXCEPT)
  typename enable_if<
    is_copy_constructible<T>::value
  >::type,
  typename enable_if<
    is_destructible<T>::value
  >::type,
#endif // defined(ASIO_HAS_NOEXCEPT)
  typename enable_if<
    traits::equality_comparable<T>::is_valid
  >::type,
  typename enable_if<
    traits::equality_comparable<T>::is_noexcept
  >::type> : true_type
=======
  enable_if_t<
    traits::execute_member<add_const_t<T>, F>::is_valid
  >,
  void_t<
    result_of_t<decay_t<F>&()>
  >,
  enable_if_t<
    is_constructible<decay_t<F>, F>::value
  >,
  enable_if_t<
    is_move_constructible<decay_t<F>>::value
  >,
  enable_if_t<
    is_nothrow_copy_constructible<T>::value
  >,
  enable_if_t<
    is_nothrow_destructible<T>::value
  >,
  enable_if_t<
    traits::equality_comparable<T>::is_valid
  >,
  enable_if_t<
    traits::equality_comparable<T>::is_noexcept
  >> : true_type
>>>>>>> 142038d (add asio new version)
{
};

} // namespace detail

/// The is_executor trait detects whether a type T satisfies the
/// execution::executor concept.
/**
 * Class template @c is_executor is a UnaryTypeTrait that is derived from @c
 * true_type if the type @c T meets the concept definition for an executor,
 * otherwise @c false_type.
 */
template <typename T>
struct is_executor :
#if defined(GENERATING_DOCUMENTATION)
  integral_constant<bool, automatically_determined>
#else // defined(GENERATING_DOCUMENTATION)
  detail::is_executor_of_impl<T, invocable_archetype>
#endif // defined(GENERATING_DOCUMENTATION)
{
};

#if defined(ASIO_HAS_VARIABLE_TEMPLATES)

template <typename T>
constexpr const bool is_executor_v = is_executor<T>::value;

#endif // defined(ASIO_HAS_VARIABLE_TEMPLATES)

#if defined(ASIO_HAS_CONCEPTS)

template <typename T>
ASIO_CONCEPT executor = is_executor<T>::value;

#define ASIO_EXECUTION_EXECUTOR ::asio::execution::executor

#else // defined(ASIO_HAS_CONCEPTS)

#define ASIO_EXECUTION_EXECUTOR typename

#endif // defined(ASIO_HAS_CONCEPTS)

} // namespace execution
} // namespace asio

#include "asio/detail/pop_options.hpp"

#endif // ASIO_EXECUTION_EXECUTOR_HPP
