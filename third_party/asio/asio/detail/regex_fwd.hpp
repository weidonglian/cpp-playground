//
// detail/regex_fwd.hpp
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

#ifndef ASIO_DETAIL_REGEX_FWD_HPP
#define ASIO_DETAIL_REGEX_FWD_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#if defined(ASIO_HAS_BOOST_REGEX)

<<<<<<< HEAD
#include <boost/regex_fwd.hpp>
#include <boost/version.hpp>
#if BOOST_VERSION >= 107600
# if defined(BOOST_REGEX_CXX03)
#  include <boost/regex/v4/match_flags.hpp>
# else // defined(BOOST_REGEX_CXX03)
#  include <boost/regex/v5/match_flags.hpp>
# endif // defined(BOOST_REGEX_CXX03)
#else // BOOST_VERSION >= 107600
# include <boost/regex/v4/match_flags.hpp>
#endif // BOOST_VERSION >= 107600

=======
>>>>>>> 142038d (add asio new version)
namespace boost {

template <class BidiIterator>
struct sub_match;

template <class BidiIterator, class Allocator>
class match_results;

template <class CharT, class Traits>
class basic_regex;

} // namespace boost

#endif // defined(ASIO_HAS_BOOST_REGEX)

#endif // ASIO_DETAIL_REGEX_FWD_HPP
