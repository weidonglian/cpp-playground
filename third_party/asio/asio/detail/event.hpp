//
// detail/event.hpp
// ~~~~~~~~~~~~~~~~
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

#ifndef ASIO_DETAIL_EVENT_HPP
#define ASIO_DETAIL_EVENT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include "asio/detail/config.hpp"

#if !defined(ASIO_HAS_THREADS)
# include "asio/detail/null_event.hpp"
#elif defined(ASIO_WINDOWS)
# include "asio/detail/win_event.hpp"
#elif defined(ASIO_HAS_PTHREADS)
# include "asio/detail/posix_event.hpp"
#else
# include "asio/detail/std_event.hpp"
#endif

namespace asio {
namespace detail {

#if !defined(ASIO_HAS_THREADS)
typedef null_event event;
#elif defined(ASIO_WINDOWS)
typedef win_event event;
#elif defined(ASIO_HAS_PTHREADS)
typedef posix_event event;
#else
typedef std_event event;
#endif

} // namespace detail
} // namespace asio

#endif // ASIO_DETAIL_EVENT_HPP
