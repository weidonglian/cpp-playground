//
// detail/cstdint.hpp
// ~~~~~~~~~~~~~~~~~~
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

#ifndef ASIO_DETAIL_CSTDINT_HPP
#define ASIO_DETAIL_CSTDINT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include "asio/detail/config.hpp"
#include <cstdint>

namespace asio {

using std::int16_t;
using std::int_least16_t;
using std::uint16_t;
using std::uint_least16_t;
using std::int32_t;
using std::int_least32_t;
using std::uint32_t;
using std::uint_least32_t;
using std::int64_t;
using std::int_least64_t;
using std::uint64_t;
using std::uint_least64_t;
using std::uintptr_t;
using std::uintmax_t;
<<<<<<< HEAD
#else // defined(ASIO_HAS_CSTDINT)
using boost::int16_t;
using boost::int_least16_t;
using boost::uint16_t;
using boost::uint_least16_t;
using boost::int32_t;
using boost::int_least32_t;
using boost::uint32_t;
using boost::uint_least32_t;
using boost::int64_t;
using boost::int_least64_t;
using boost::uint64_t;
using boost::uint_least64_t;
using boost::uintptr_t;
using boost::uintmax_t;
#endif // defined(ASIO_HAS_CSTDINT)
=======
>>>>>>> 142038d (add asio new version)

} // namespace asio

#endif // ASIO_DETAIL_CSTDINT_HPP
