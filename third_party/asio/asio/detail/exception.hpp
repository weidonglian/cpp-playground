//
// detail/exception.hpp
// ~~~~~~~~~~~~~~~~~~~~
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

#ifndef ASIO_DETAIL_EXCEPTION_HPP
#define ASIO_DETAIL_EXCEPTION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include "asio/detail/config.hpp"
<<<<<<< HEAD

#if defined(ASIO_HAS_STD_EXCEPTION_PTR)
# include <exception>
#else // defined(ASIO_HAS_STD_EXCEPTION_PTR)
# include <boost/exception_ptr.hpp>
#endif // defined(ASIO_HAS_STD_EXCEPTION_PTR)

namespace asio {

#if defined(ASIO_HAS_STD_EXCEPTION_PTR)
using std::exception_ptr;
using std::current_exception;
using std::rethrow_exception;
#else // defined(ASIO_HAS_STD_EXCEPTION_PTR)
using boost::exception_ptr;
using boost::current_exception;
using boost::rethrow_exception;
#endif // defined(ASIO_HAS_STD_EXCEPTION_PTR)
=======
#include <exception>

namespace asio {

using std::exception_ptr;
using std::current_exception;
using std::rethrow_exception;
>>>>>>> 142038d (add asio new version)

} // namespace asio

#endif // ASIO_DETAIL_EXCEPTION_HPP
