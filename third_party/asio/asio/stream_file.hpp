//
// stream_file.hpp
// ~~~~~~~~~~~~~~~
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

#ifndef ASIO_STREAM_FILE_HPP
#define ASIO_STREAM_FILE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include "asio/detail/config.hpp"

#if defined(ASIO_HAS_FILE) \
  || defined(GENERATING_DOCUMENTATION)

#include "asio/basic_stream_file.hpp"

namespace asio {

/// Typedef for the typical usage of a stream-oriented file.
typedef basic_stream_file<> stream_file;

} // namespace asio

#endif // defined(ASIO_HAS_FILE)
       //   || defined(GENERATING_DOCUMENTATION)

#endif // ASIO_STREAM_FILE_HPP
