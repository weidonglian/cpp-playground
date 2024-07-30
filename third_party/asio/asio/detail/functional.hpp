//
// detail/functional.hpp
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

#ifndef ASIO_DETAIL_FUNCTIONAL_HPP
#define ASIO_DETAIL_FUNCTIONAL_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include "asio/detail/config.hpp"
#include <functional>

namespace asio {
namespace detail {

using std::function;

} // namespace detail

<<<<<<< HEAD
#if defined(ASIO_HAS_STD_REFERENCE_WRAPPER)
using std::ref;
using std::reference_wrapper;
#endif // defined(ASIO_HAS_STD_REFERENCE_WRAPPER)
=======
using std::ref;
using std::reference_wrapper;
>>>>>>> 142038d (add asio new version)

} // namespace asio

#endif // ASIO_DETAIL_FUNCTIONAL_HPP
