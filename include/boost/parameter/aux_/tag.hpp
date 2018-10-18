// Copyright David Abrahams 2005.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_TAG_DWA2005610_HPP
#define BOOST_PARAMETER_AUX_TAG_DWA2005610_HPP

#include <boost/parameter/aux_/unwrap_cv_reference.hpp>
#include <boost/parameter/aux_/tagged_argument.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/config.hpp>
#include <boost/config/workaround.hpp>

namespace boost { namespace parameter { namespace aux { 

    template <
        typename Keyword
      , typename ActualArg
#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564))
      , typename = typename ::boost::parameter::aux
        ::is_cv_reference_wrapper<ActualArg>::type
#endif
    >
    struct tag
    {
#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564))
        typedef ::boost::parameter::aux::tagged_argument<
            Keyword
          , typename ::boost::parameter::aux
            ::unwrap_cv_reference<ActualArg>::type
        > type;
#endif  // Borland workarounds needed.
    };
}}} // namespace boost::parameter::aux_

#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564))
#include <boost/type_traits/remove_reference.hpp>

namespace boost { namespace parameter { namespace aux { 

    template <typename Keyword, typename ActualArg>
    struct tag<Keyword,ActualArg,::boost::mpl::false_>
    {
        typedef ::boost::parameter::aux::tagged_argument<
            Keyword
          , typename ::boost::remove_reference<ActualArg>::type
        > type;
    };
}}} // namespace boost::parameter::aux_

#endif  // Borland workarounds needed.
#endif  // include guard

