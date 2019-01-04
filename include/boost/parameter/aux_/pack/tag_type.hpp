// Copyright David Abrahams, Daniel Wallin 2003.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_PACK_TAG_TYPE_HPP
#define BOOST_PARAMETER_AUX_PACK_TAG_TYPE_HPP

namespace boost { namespace parameter { namespace aux {

    // helper for tag_type<...>, below.
    template <typename T>
    struct get_tag_type0
    {
        typedef typename T::key_type type;
    };
}}} // namespace boost::parameter::aux

#include <boost/parameter/deduced.hpp>
#include <boost/parameter/config.hpp>

#if defined(BOOST_PARAMETER_CAN_USE_MP11)
#include <boost/mp11/utility.hpp>

namespace boost { namespace parameter { namespace aux {

    template <typename T>
    using get_tag_type = ::boost::mp11::mp_if<
        ::boost::parameter::aux::is_deduced1<T>
      , ::boost::parameter::aux::get_tag_type0<typename T::key_type>
      , ::boost::mp11::mp_identity<typename T::key_type>
    >;
}}} // namespace boost::parameter::aux

#else   // !defined(BOOST_PARAMETER_CAN_USE_MP11)
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>

namespace boost { namespace parameter { namespace aux {

    template <typename T>
    struct get_tag_type
      : ::boost::mpl::eval_if<
            ::boost::parameter::aux::is_deduced_aux<typename T::key_type>
          , ::boost::parameter::aux::get_tag_type0<typename T::key_type>
          , ::boost::mpl::identity<typename T::key_type>
        >
    {
    };
}}} // namespace boost::parameter::aux

#endif  // BOOST_PARAMETER_CAN_USE_MP11

#include <boost/parameter/required.hpp>
#include <boost/parameter/optional.hpp>

#if defined(BOOST_PARAMETER_CAN_USE_MP11)
#include <boost/mp11/integral.hpp>

namespace boost { namespace parameter { namespace aux {

    template <typename T>
    using tag_type = ::boost::mp11::mp_if<
        ::boost::mp11::mp_if<
            ::boost::parameter::aux::is_optional_mp11<T>
          , ::boost::mp11::mp_true
          , ::boost::parameter::aux::is_required_mp11<T>
        >
      , ::boost::parameter::aux::get_tag_type<T>
      , ::boost::mp11::mp_identity<T>
    >;
}}} // namespace boost::parameter::aux

#else   // !defined(BOOST_PARAMETER_CAN_USE_MP11)
#include <boost/mpl/bool.hpp>
#include <boost/mpl/if.hpp>

namespace boost { namespace parameter { namespace aux {

    template <typename T>
    struct tag_type
      : ::boost::mpl::eval_if<
            typename ::boost::mpl::if_<
                ::boost::parameter::aux::is_optional<T>
              , ::boost::mpl::true_
              , ::boost::parameter::aux::is_required<T>
            >::type
          , ::boost::parameter::aux::get_tag_type<T>
          , ::boost::mpl::identity<T>
        >
    {
    };
}}} // namespace boost::parameter::aux

#endif  // BOOST_PARAMETER_CAN_USE_MP11
#endif  // include guard

