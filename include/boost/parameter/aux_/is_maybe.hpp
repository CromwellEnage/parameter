// Copyright Daniel Wallin, David Abrahams 2010.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_IS_MAYBE_050329_HPP
#define BOOST_PARAMETER_IS_MAYBE_050329_HPP

namespace boost { namespace parameter { namespace aux {

    struct maybe_base
    {
    };
}}} // namespace boost::parameter::aux

#include <boost/parameter/config.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/if.hpp>

#if defined(BOOST_PARAMETER_USES_BOOST_VICE_CXX11_TYPE_TRAITS)
#include <boost/type_traits/is_base_of.hpp>
#include <boost/type_traits/remove_const.hpp>
#else
#include <type_traits>
#endif

namespace boost { namespace parameter { namespace aux {

    template <typename T>
    struct is_maybe
      : ::boost::mpl::if_<
#if defined(BOOST_PARAMETER_USES_BOOST_VICE_CXX11_TYPE_TRAITS)
            ::boost::is_base_of<
#else
            ::std::is_base_of<
#endif
                ::boost::parameter::aux::maybe_base
#if defined(BOOST_PARAMETER_USES_BOOST_VICE_CXX11_TYPE_TRAITS)
              , typename ::boost::remove_const<T>::type
#else
              , typename ::std::remove_const<T>::type
#endif
            >
          , ::boost::mpl::true_
          , ::boost::mpl::false_
        >::type
    {
    };
}}} // namespace boost::parameter::aux

#endif  // include guard

