// Copyright Cromwell D. Enage 2019.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_IS_MPL_PLACEHOLDER_HPP
#define BOOST_PARAMETER_AUX_IS_MPL_PLACEHOLDER_HPP

#include <boost/parameter/config.hpp>

#if defined(BOOST_PARAMETER_HAS_PERFECT_FORWARDING)
#include <boost/mp11/integral.hpp>
#else
#include <boost/mpl/bool.hpp>
#endif

namespace boost { namespace parameter { namespace aux {

    template <typename T>
    struct is_mpl_placeholder
#if defined(BOOST_PARAMETER_HAS_PERFECT_FORWARDING)
      : ::boost::mp11::mp_false
#else
      : ::boost::mpl::false_
#endif
    {
    };
}}} // namespace boost::parameter::aux

#include <boost/mpl/arg_fwd.hpp>

namespace boost { namespace parameter { namespace aux {

    template <int I>
    struct is_mpl_placeholder< ::boost::mpl::arg<I> >
#if defined(BOOST_PARAMETER_HAS_PERFECT_FORWARDING)
      : ::boost::mp11::mp_true
#else
      : ::boost::mpl::true_
#endif
    {
    };
}}} // namespace boost::parameter::aux

#endif  // include guard

