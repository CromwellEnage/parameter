// Copyright Daniel Wallin 2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_PP_IMPL_UNWRAP_PREDICATE_HPP
#define BOOST_PARAMETER_AUX_PP_IMPL_UNWRAP_PREDICATE_HPP

namespace boost { namespace parameter { namespace aux {

    // Given Match, which is "void x" where x is an argument matching
    // criterion, extract a corresponding MPL predicate.
    template <typename Match>
    struct unwrap_predicate;
}}} // namespace boost::parameter::aux

#include <boost/mpl/bool.hpp>
#include <boost/mpl/always.hpp>

namespace boost { namespace parameter { namespace aux {

    // Match anything
    template <>
    struct unwrap_predicate<void*>
    {
        typedef ::boost::mpl::always< ::boost::mpl::true_> type;
    };
}}} // namespace boost::parameter::aux

#include <boost/config/workaround.hpp>

#if BOOST_WORKAROUND(__SUNPRO_CC, BOOST_TESTED_AT(0x580))
#include <boost/parameter/aux_/void.hpp>
#endif

namespace boost { namespace parameter { namespace aux {

    // A matching predicate is explicitly specified.
#if BOOST_WORKAROUND(__SUNPRO_CC, BOOST_TESTED_AT(0x580))
    template <typename Predicate>
    struct unwrap_predicate< ::boost::parameter::aux::voidstar(Predicate)>
    {
        typedef Predicate type;
    };
#else
    template <typename Predicate>
    struct unwrap_predicate<void *(Predicate)>
    {
        typedef Predicate type;
    };
#endif   // SunProCC workarounds needed.
}}} // namespace boost::parameter::aux

#include <boost/parameter/config.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/if.hpp>

#if defined(BOOST_PARAMETER_USES_BOOST_VICE_CXX11_TYPE_TRAITS)
#include <boost/type_traits/is_convertible.hpp>
#else
#include <type_traits>
#endif

namespace boost { namespace parameter { namespace aux {

    // A type to which the argument is supposed to be convertible is
    // specified.
    template <typename Target>
    struct unwrap_predicate<void (Target)>
    {
        typedef ::boost::mpl::if_<
#if defined(BOOST_PARAMETER_USES_BOOST_VICE_CXX11_TYPE_TRAITS)
            ::boost::is_convertible< ::boost::mpl::_,Target>
#else
            ::std::is_convertible< ::boost::mpl::_,Target>
#endif
          , ::boost::mpl::true_
          , ::boost::mpl::false_
        > type;
    };
}}} // namespace boost::parameter::aux

#endif  // include guard
