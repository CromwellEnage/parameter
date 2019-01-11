// Copyright Daniel Wallin, David Abrahams 2005.
// Copyright Cromwell D. Enage 2017.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_TAGGED_ARGUMENT_FWD_HPP
#define BOOST_PARAMETER_TAGGED_ARGUMENT_FWD_HPP

#include <boost/parameter/config.hpp>

namespace boost { namespace parameter { namespace aux {

#if defined(BOOST_PARAMETER_CAN_USE_MP11) && \
    BOOST_WORKAROUND(BOOST_MSVC, >= 1910)
// For MSVC-14.1+, more than one partial template specialization matches the
// template argument list of boost::mp11::detail::mp_find_impl.
    template <typename Keyword, typename Arg, typename Dummy = void>
#else
    template <typename Keyword, typename Arg>
#endif
    class tagged_argument;
}}} // namespace boost::parameter::aux

#if defined(BOOST_PARAMETER_HAS_PERFECT_FORWARDING)

namespace boost { namespace parameter { namespace aux {

#if defined(BOOST_PARAMETER_CAN_USE_MP11) && \
    BOOST_WORKAROUND(BOOST_MSVC, >= 1910)
// For MSVC-14.1+, more than one partial template specialization matches the
// template argument list of boost::mp11::detail::mp_find_impl.
    template <typename Keyword, typename Arg, typename Dummy = void>
#else
    template <typename Keyword, typename Arg>
#endif
    struct tagged_argument_rref;
}}} // namespace boost::parameter::aux

#endif
#endif  // include guard

